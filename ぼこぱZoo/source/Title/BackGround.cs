using UnityEngine;
using System.Collections;

public class BackGround : MonoBehaviour {
	[SerializeField] float m_fFadeInTime;		// 背景がフェードインしてくる時間(秒)

	float m_fAlpha;					// 現在のアルファ値
	float m_fAddAlpha;				// 1ループあたりのアルファ値の増加量
	
	int m_nStates;	// 0 ・・・ フェードイン中
					// 1 ・・・ 全て終了
	
	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeInTime) / 30.0f;
		m_nStates = -1;	// 最初処理はしない

		GetComponent<SpriteRenderer>().enabled = false;
		GetComponent<SpriteRenderer>().color = new Color (1.0f, 1.0f, 1.0f, 0.0f);

		Sound.LoadBgm ("BGM_Title","BGM_Title");	// BGM
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
		GetComponent<SpriteRenderer>().enabled = true;

		// タイトルBGMを流し始める
		Sound.PlayBgm ("BGM_Title");
	}

	// スキップ処理
	private void Skip()
	{
		// タップ
		if (m_nStates != 1 && GameObject.Find("Fade").GetComponent<Fade>().GetTouch() &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			GetComponent<SpriteRenderer>().enabled = true;
			GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			// タイトルBGMを流し始める
			Sound.PlayBgm("BGM_Title");

			m_nStates = 1;
		}
		// マウス
		if (m_nStates != 1 && Input.GetMouseButtonDown(0) &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			GetComponent<SpriteRenderer>().enabled = true;
			GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			// タイトルBGMを流し始める
			Sound.PlayBgm("BGM_Title");

			m_nStates = 1;
		}
	}

	private void State()
	{
		switch (m_nStates)
		{
			case -1:	// フェードイン前
				break;

			case 0:		//フェードイン中
				m_fAlpha += m_fAddAlpha;
				if (m_fAlpha >= 1.0f)
				{
					m_fAlpha = 1.0f;	// アルファ値加算
					m_nStates = 1;		// ステータス変化

					// スタートボタンを点滅させる
					GameObject.Find("StartButton").GetComponent<StartButton>().StartFlash();
				}
				GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 1:		// 処理しない
				break;
		}
	}
}
