using UnityEngine;
using System.Collections;

public class GameOver : MonoBehaviour {
	[SerializeField] float fWaitTime;		// 落下し始める前の待ち時間
	[SerializeField] float fStartPos;		// 落下し始める座標
	[SerializeField] float fStartSpeed;		// 落下させるときの初速度
	[SerializeField] float fGravity;		// 重力加速度
	[SerializeField] float fBoundPos;		// どこを跳ね返り地点とするかのY座標
	[SerializeField] float fCoefficient;	// 跳ね返る時の反発係数
	[SerializeField] float fLastSpeed;		// 跳ね返りを終了と判定するときの, 跳ね返った後のスピード(この値より小さいと終了)
	[SerializeField] float fSpeed;			// 現在の速度
	float fTime;					// タイマー
	float fPosY;					// 座標計算用
	[SerializeField] float fStayTime;		// バウンドし終わってSpeedが0になっている時間
	[SerializeField] float fReBoundSpeed;	// 再びバウンドし始める時の初速度
	bool bFirstCase1;				// case1(落下＆バウンド状態)の時に, 1ループ目だけはバウンド判定しないフラグ

	int nStates;	// 0 ・・・ 落下待ち状態
					// 1 ・・・ 落下中＆バウンド中
					// 2 ・・・ 何もしない(それか横揺れ)


	// Use this for initialization
	void Start ()
	{
		fSpeed = fStartSpeed;	// スピード初期化
		fTime = 0.0f;			// タイマー初期化
		nStates = 0;			// ステータス初期化
		bFirstCase1 = true;		// 1ループ目

		transform.position = new Vector3 (0.0f, fStartPos, 0.0f);	// 座標初期化

		// ゲームオーバーシーンで流すBGMをロードする
		Sound.LoadBgm ("BGM_GameOver", "BGM_GameOver");

		Sound.PlayBgm ("BGM_GameOver");
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードイン中なら処理はしない
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFadeIn)
			return;

		State();
	}

	private void State()
	{
		switch (nStates)
		{
			case 0:		// 落下待ち状態
				fTime += 1.0f / 30.0f;
				if (fTime >= fWaitTime)
				{
					fTime = 0.0f;
					nStates = 1;
				}
				break;

			case 1:		// 落下中＆バウンド中
				fSpeed += fGravity;
				fPosY = transform.position.y + fSpeed;

				// 1回目だけは判定しない
				if (!bFirstCase1)
				{
					// 跳ね返り時判定
					if (fPosY <= fBoundPos)
					{
						fSpeed *= -fCoefficient;	// スピード跳ね返り
						fPosY = fBoundPos;			// 座標をバウンドする座標にする

						// 跳ね返り終了判定
						if (fSpeed <= fLastSpeed)
						{
							fSpeed = 0.0f;
							nStates = 2;
						}
					}
				}
				else
					bFirstCase1 = false;

				// 座標変更
				transform.position = new Vector3(transform.position.x, fPosY, transform.position.z);
				break;

			case 2:		// 再びバウンドするまでの待ち時間
				fTime += 1.0f / 30.0f;
				if (fTime >= fStayTime)
				{
					fTime = 0.0f;
					nStates = 1;
					fSpeed = fReBoundSpeed;
					bFirstCase1 = true;
				}
				break;
		}
	}
}
