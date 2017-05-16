using UnityEngine;
using System.Collections;

public class TitleLogo : MonoBehaviour {
	[SerializeField] float m_fFadeInTime;	// フェードインにかかる時間
	[SerializeField] float m_fStopTime;		// フェードインが完了して止まっている時間
	[SerializeField] float m_fStartScale;	// 登場時の拡大率
	[SerializeField] float m_fEndScale;		// 縮小した後の拡大率
	[SerializeField] float m_fReductionTime;// 縮小にかける時間
	[SerializeField] float m_fStopTime2;	// 縮小が完了して止まっている時間
	[SerializeField] float m_fEndPos;		// タイトル画像の移動先の座標(Y)
	[SerializeField] float m_fMoveTime;		// 移動にかかる時間
	[SerializeField] float m_fButtonInTime;	// 移動開始してから, スタートボタンと背景がフェードインし始めるまでの時間
	
	float m_fTime;					// タイマー
	float m_fAlpha;					// 現在のアルファ値
	float m_fAddAlpha;				// 1フレームあたりのアルファ値の増加量
	float m_fSpeed;					// 1フレームあたりの移動量
	float m_fChangeScale;			// 1フレームあたりの拡大率の変化量
	bool  m_bStartButton;			// スタートボタンと背景の処理を開始させたかどうかのフラグ


	int m_nStates;	// 0 ・・・ フェードイン中
					// 1 ・・・ フェードイン完了して、止まっている
					// 2 ・・・ 縮小中
					// 3 ・・・ 縮小が完了して止まっている
					// 4 ・・・ 移動中
					// 5 ・・・ 全て終了


	// Use this for initialization
	void Start ()
	{
		m_fTime = 0.0f;
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeInTime) / 30.0f;
		m_fSpeed = (m_fEndPos / m_fMoveTime) / 30.0f;	// 出現位置のY座標は0.0fなのが前提
		m_fChangeScale = ((m_fStartScale - m_fEndScale) / m_fReductionTime)/30.0f;//登場時の拡大率のほうが大きい
		m_bStartButton = false;		// スタートボタンと背景の処理は開始しない

		m_nStates = -1;		// 最初は何もしない

		GetComponent<SpriteRenderer> ().color = new Color (1.0f, 1.0f, 1.0f, 0.0f);
		GetComponent<SpriteRenderer> ().enabled = false;
		transform.position = new Vector3 (0.0f, 0.0f, 0.0f);	// 初期座標は真ん中
		transform.localScale = new Vector3 (m_fStartScale, m_fStartScale, 1.0f);
	}
	
	// Update is called once per frame
	void Update ()
	{
		// スキップ処理
		Skip();
		
		State();
	}

	// 処理を開始してよくなったら呼ばれる
	public void StartProcess()
	{
		m_nStates = 0;	// 処理開始
		GetComponent<SpriteRenderer> ().enabled = true;
	}

	public void Skip()
	{
		// タップ
		if (m_nStates != 5 && GameObject.Find("Fade").GetComponent<Fade>().GetTouch() &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			GetComponent<SpriteRenderer>().enabled = true;
			GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
			transform.localScale = new Vector3(m_fEndScale, m_fEndScale, transform.localScale.z);
			transform.position = new Vector3(transform.position.x, m_fEndPos, transform.position.z);
			m_nStates = 5;
		}
		// マウス
		if (m_nStates != 5 && Input.GetMouseButtonDown(0) &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			GetComponent<SpriteRenderer>().enabled = true;
			GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
			transform.localScale = new Vector3(m_fEndScale, m_fEndScale, transform.localScale.z);
			transform.position = new Vector3(transform.position.x, m_fEndPos, transform.position.z);
			m_nStates = 5;
		}
	}

	public void State()
	{
		m_fTime += 1.0f / 30.0f;

		switch (m_nStates)
		{
			case -1:	// フェードイン前
				break;

			case 0:		// フェードイン中
				m_fAlpha += m_fAddAlpha;	// アルファ値加算
				if (m_fAlpha >= 1.0f)
				{
					m_fTime = 0.0f;			// タイマー初期化
					m_fAlpha = 1.0f;		// アルファ値を最大に
					m_nStates++;			// ステータス変化
				}
				GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 1:		// フェードインが完了して停止中
				if (m_fTime >= m_fStopTime)
				{
					m_fTime = 0.0f;			// タイマー初期化
					m_nStates++;			// ステータス変化
				}
				break;

			case 2:		// 縮小中
				transform.localScale = new Vector3(transform.localScale.x - m_fChangeScale,
												   transform.localScale.y - m_fChangeScale,
												   transform.localScale.z);
				if (m_fTime >= m_fReductionTime)
				{
					transform.localScale = new Vector3(m_fEndScale, m_fEndScale, transform.localScale.z);

					m_fTime = 0.0f;		// タイマー初期化
					m_nStates++;		// ステータス変化
				}
				break;

			case 3:		// 縮小が完了して止まっている
				if (m_fTime >= m_fStopTime2)
				{
					m_fTime = 0.0f;		// タイマー初期化
					m_nStates++;		// ステータス変化
				}
				break;

			case 4:		// 移動中
				transform.position = new Vector3(transform.position.x,
												 transform.position.y + m_fSpeed,
												 transform.position.z);
				if (m_fTime >= m_fMoveTime)
				{
					transform.position = new Vector3(transform.position.x, m_fEndPos, transform.position.z);

					m_fTime = 0.0f;			// タイマー初期化
					m_nStates++;			// ステータス変化
				}

				// スタートボタンと背景のフェードイン処理開始
				if (!m_bStartButton && m_fTime >= m_fButtonInTime)
				{
					m_bStartButton = true;		// 処理開始済み

					// スタートボタンの処理開始
					GameObject.Find("StartButton").GetComponent<StartButton>().StartProcess();
				}
				break;

			case 5:		// 全て終了
				break;
		}
	}
}
