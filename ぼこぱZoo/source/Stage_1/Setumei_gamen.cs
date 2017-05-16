using UnityEngine;
using System.Collections;

public class Setumei_gamen : MonoBehaviour {
	bool m_bMove;				// 移動中フラグ(移動中ならtrue)
	bool m_bUp;					// 上にあがってくるときtrue
	bool m_bHarf;				// さがりの前半ならtrue, さがりの後半ならfalse

	public float m_fStartPos;	// 移動開始地点
	public float m_fReturnPos;	// 折り返し地点
	public float m_fGoTime;		// 移動開始から、折り返し地点までの時間
	public float m_fBackTime;	// 折り返し地点から、真ん中に来て止まるまでの時間
	float m_fStartSpeed;		// デバッグ用の初速度
	float m_fAccele;			// デバッグ用の加速度
	float m_fTime;				// 移動が始まってからの時間
	float m_fHeni;				// 現在の変位
	float m_fPosY;				// 代入するY座標
	float m_KijunPos;			// 変位の基準となる座標

	bool bStart;

	// Use this for initialization
	void Start ()
	{
		m_fStartSpeed = 0.0f;		// 上がりの初速度は0
		m_fAccele = (m_fReturnPos / (m_fBackTime / 2)) / (m_fBackTime / 2); // 上がりの加速度を計算
		
		m_fTime = 0.0f;

		m_bMove = false;	// 移動開始
		m_bUp = true;		// 上にあがる
		m_bHarf = true;		// 上がりの前半
		m_KijunPos = 0.0f;	// 基準座標は真ん中にする

		GetComponent<SpriteRenderer> ().enabled = true;

		bStart = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Input.touchCount == 1 && Input.GetTouch (0).phase == TouchPhase.Began)
		{
			if(bStart && !m_bMove)
			{
				Sound.PlaySe("SE_Enter");

				m_bMove = true;
				Destroy(GameObject.Find("touchplease"));
			}
		}
		
		// マウス
		if (Input.GetMouseButtonDown(0))
		{
			if(bStart && !m_bMove)
			{
				m_bMove = true;
				Destroy(GameObject.Find("touchplease"));
			}
		}

		if (!m_bMove)
			return;

		m_fTime += Time.deltaTime;	// 時間
		
		m_fHeni = (m_fStartSpeed * m_fTime) + (0.5f * m_fAccele * m_fTime * m_fTime);	// 変位の計算
		m_fPosY = m_KijunPos + m_fHeni;		// 座標の計算

		if(m_bUp)
		{// 上がり
			if(m_bHarf)
			{// 上がりの前半
				if(m_fTime >= m_fBackTime / 2)
				{
					m_fTime = 0.0f;			// タイマーの初期化
					m_bHarf = false;		// 上がりの後半
					
					m_fStartSpeed = m_fReturnPos / (m_fBackTime / 2);	// 初速度の計算
					m_fAccele = -m_fAccele;			// 加速度の計算
					m_KijunPos = m_fReturnPos / 2;	// 基準座標を真ん中と折り返し地点との中間にする
				}
			}
			else
			{// 上がりの後半
				if(m_fTime >= m_fBackTime / 2)
				{
					m_fTime = 0.0f;			// タイマーの初期化
					m_bUp = false;			// 下がり
					
					m_fStartSpeed = 0.0f;	// 下がりの初速度は0
					m_fAccele = (-(m_fReturnPos - m_fStartPos) * 2 / m_fGoTime) / m_fGoTime; // 加速度の計算
					m_KijunPos = m_fReturnPos;	// 基準座標を折り返し地点にする
				}
			}
		}
		else
		{// 下がり
			if (m_fTime >= m_fGoTime)
			{// スライドアウト完了
				// bgのフェードアウト開始
				GameObject.Find("bg").GetComponent<bg>().StartProgress();

				Destroy(this.gameObject);
			}
		}

		// 座標移動
		transform.position = new Vector3 (0.0f, m_fPosY, 0.0f);
	}

	public void StartSetumeigamen()
	{
		bStart = true;
	}
}
