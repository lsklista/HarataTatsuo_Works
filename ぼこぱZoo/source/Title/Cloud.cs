using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Cloud : MonoBehaviour {
	[SerializeField] float m_fFadeInTime;		// 背景がフェードインしてくる時間(秒)
	[SerializeField] float m_fOneLoopTime;		// 雲が1ループするのにかかる時間
	
	float m_fAlpha;					// 現在のアルファ値
	float m_fAddAlpha;				// 1ループあたりのアルファ値の増加量

	RawImage m_RawImage;
	float m_fAddU;					// UV座標のUの1ループあたりの変化量
	float m_fU;						// 代入するU座標
	
	int m_nStates;	// 0 ・・・ フェードイン中
					// 1 ・・・ スクロール中
					// 2 ・・・ 全て終了
	
	
	void Start()
	{
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeInTime) / 30.0f;

		m_RawImage = GetComponent<RawImage>();
		m_RawImage.uvRect = new Rect(0.0f, 0.0f, 1.0f, 1.0f);	// UV座標初期化
		m_RawImage.enabled = false;
		m_RawImage.color = new Color (1.0f, 1.0f, 1.0f, 0.0f);
		m_fAddU = (1.0f / m_fOneLoopTime) / 30.0f;
	
		m_nStates = -1;	// 最初処理はしない
	}
	
	void Update()
	{
		// スキップ処理
		Skip();

		State();
	}

	
	
	// 処理を開始してよくなったら呼ばれる
	public void StartProcess()
	{
		m_nStates = 0;	// 処理開始
		GetComponent<RawImage>().enabled = true;
	}

	private void Skip()
	{
		// タップ
		if (m_nStates != 1 && GameObject.Find("Fade").GetComponent<Fade>().GetTouch() &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			m_RawImage.enabled = true;
			m_RawImage.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			m_nStates = 1;
		}
		// マウス
		if (m_nStates != 1 && Input.GetMouseButtonDown(0) &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			m_RawImage.enabled = true;
			m_RawImage.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			m_nStates = 1;
		}
	}

	private void State()
	{
		switch (m_nStates)
		{
			case -1:	// フェードイン前
				break;

			case 0:		// フェードイン
				m_fAlpha += m_fAddAlpha;
				if (m_fAlpha >= 1.0f)
				{
					m_fAlpha = 1.0f;	// アルファ値加算
					m_nStates = 1;		// ステータス変化
				}
				m_RawImage.color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				m_RawImage.uvRect = new Rect(m_RawImage.uvRect.x + m_fAddU, 0.0f, 1.0f, 1.0f);
				break;

			case 1:		// スクロール
				m_fU = m_RawImage.uvRect.x + m_fAddU;
				if (m_fU >= 1.0f)
					m_fU -= 1.0f;
				m_RawImage.uvRect = new Rect(m_fU, 0.0f, 1.0f, 1.0f);
				break;

			case 2:		// 何もしない
				break;
		}
	}
}