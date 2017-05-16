using UnityEngine;
using System.Collections;

public class HamuMgr : MonoBehaviour {
	SpriteRenderer[] HamutiAndEnemy;	// はむちと敵のゲームオブジェクト

	bool m_bFront;					// 手前と奥どっちを走っているか(trueなら手前)
	bool m_bOffScreen;				// 走り抜けて画面外に消えていたらtrue
	[SerializeField] float m_fIntervalTime;	// 横切って画面外に消えてから再度現れるまでの時間
	float m_fTime;					// 時間
	[SerializeField] float m_FrontSpeed;		// 手前を走るスピード
	[SerializeField] float m_fBackSpeed;		// 奥を走るスピード
	[SerializeField] float m_fStartPos_Front;	// 手前の走り始める座標
	[SerializeField] float m_fStartPos_Back;	// 奥の走り始める座標
	[SerializeField] float m_fFrontPosY;		// 手前を走るときのY座標
	[SerializeField] float m_fBackPosY;			// 奥を走るときのY座標
	[SerializeField] float m_fFrontScale;		// 手前を走るときの拡大率
	[SerializeField] float m_fBackScale;		// 奥を走るときの拡大率

	bool m_bButtonProcess;			// ボタンの処理を開始したかどうか


	// Use this for initialization
	void Start ()
	{
		m_bFront = true;		// 最初は手前を横切る
		m_bOffScreen = false;	// 走り抜けていない
		transform.position = new Vector3 (m_fStartPos_Front, m_fFrontPosY, 0.0f);	// 初期座標にセット
		transform.localScale = new Vector3 (m_fFrontScale, m_fFrontScale, 0.0f);	// 手前用の拡大率にセット

		HamutiAndEnemy = new SpriteRenderer[4];
		HamutiAndEnemy [0] = GameObject.Find ("hamu_mikata").GetComponent<SpriteRenderer>();
		HamutiAndEnemy [1] = GameObject.Find ("hamu_enemy_0").GetComponent<SpriteRenderer>();
		HamutiAndEnemy [2] = GameObject.Find ("hamu_enemy_1").GetComponent<SpriteRenderer>();
		HamutiAndEnemy [3] = GameObject.Find ("hamu_enemy_2").GetComponent<SpriteRenderer>();
		SetLayer (true);	// 描画順を手前用にする

		m_bButtonProcess = false;	// まだボタンの処理は開始していない
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードイン中なら処理はしない
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFadeIn)
			return;


		if (!m_bOffScreen)
		{// 画面外に出ていないとき
			if (m_bFront)
			{// 手前を走っているとき
				// 座標更新(右へ移動)
				transform.position = new Vector3 (transform.position.x + m_FrontSpeed, m_fFrontPosY, 0.0f);

				// 画面外判定
				if (transform.position.x >= -m_fStartPos_Front)
				{
					m_bOffScreen = true;

					// まだボタンの処理が開始されていなければ処理開始
					if(!m_bButtonProcess)
					{
						GameObject.Find("RetryButton").GetComponent<RetryButton>().StartProcess();
						GameObject.Find("StageSelectButton").GetComponent<StageSelectButton>().StartProcess();
					}
				}
			}
			else
			{// 奥を走っているとき
				// 座標更新(左へ移動)
				transform.position = new Vector3 (transform.position.x - m_fBackSpeed, m_fBackPosY, 0.0f);

				// 画面外判定
				if (transform.position.x <= -m_fStartPos_Back)
				{
					m_bOffScreen = true;
				}
			}
		}
		else
		{// 画面外に出ているとき
			m_fTime += 1.0f / 30.0f;

			if(m_fTime >= m_fIntervalTime)
			{
				m_fTime = 0.0f;			// 時間初期化
				m_bOffScreen = false;	// 画面外処理を終了

				if(m_bFront)
				{// 手前から奥に切り替える
					m_bFront = false;
					transform.position = new Vector3 (m_fStartPos_Back, m_fBackPosY, 0.0f);		// 座標
					transform.localScale = new Vector3 (-m_fBackScale, m_fBackScale, 0.0f);		// 拡大率
					SetLayer(false);	// 描画順を奥用に切り替える
				}
				else
				{// 奥から手前に切り替える
					m_bFront = true;
					transform.position = new Vector3 (m_fStartPos_Front, m_fBackPosY, 0.0f);	// 座標
					transform.localScale = new Vector3 (m_fFrontScale, m_fFrontScale, 0.0f);	// 拡大率
					SetLayer(true);	// 描画順を手前用に切り替える
				}
			}
		}
	}

	// はむちたちの描画順を変更する
	void SetLayer(bool bFront)
	{
		if (bFront)
		{// 手前
			HamutiAndEnemy[0].sortingOrder = 5;
			HamutiAndEnemy[1].sortingOrder = 5;
			HamutiAndEnemy[2].sortingOrder = 4;
			HamutiAndEnemy[3].sortingOrder = 5;
		}
		else
		{// 奥
			HamutiAndEnemy[0].sortingOrder = 2;
			HamutiAndEnemy[1].sortingOrder = 2;
			HamutiAndEnemy[2].sortingOrder = 1;
			HamutiAndEnemy[3].sortingOrder = 2;

		}
	}
}
