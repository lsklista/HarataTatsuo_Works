using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class StartButton : MonoBehaviour {
	[SerializeField] float m_fFadeInTime;		// ボタンがフェードインしてくる時間(秒)
	[SerializeField] float m_fMaxRGB;			// 点滅時のRGBの最大値
	[SerializeField] float m_fFlashTime;		// 1回の点滅にかかる時間(光ってから, 消えるまでで1回)

	Image Img;
	float m_fAlpha;					// 現在のアルファ値
	float m_fAddAlpha;				// 1ループあたりのアルファ値の増加量

	float m_fRGB;					// 現在のRGB
	float m_fChangeRGB;				// 1ループあたりのRGBの変化量

	int m_nStates;	// 0 ・・・ フェードイン中
					// 1 ・・・ フェードインが完了して何も処理をしていない
					// 2 ・・・ 点滅

	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeInTime) / 30.0f;

		m_fRGB = 0.5f;	// 最初は元の色
		m_fChangeRGB = ((m_fMaxRGB - 0.5f) / m_fFlashTime) / 30.0f * 2.0f;

		m_nStates = -1;	// 最初処理はしない

		Img = GetComponent<Image>();
		Img.enabled = false;
		Img.color = new Color (0.5f, 0.5f, 0.5f, 0.0f);

		Sound.LoadSe ("SE_Enter", "SE_Enter");		// 決定音
	}
	
	// Update is called once per frame
	void Update ()
	{
		// スキップ処理
		Skip();

		State();
	}

	public void onTapButton()
	{
		// アルファ値が1でなければタップは無効
		if (m_fAlpha != 1.0f)
			return;
		
		// フェード中ならタップは無効
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;

		// クリック音を鳴らす
		Sound.PlaySe ("SE_Enter");

		// ステセレシーンに, BGMは再生しなくていいように設定する
		Main_SS.SetPlayBGM (false);

		GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STORY_MAE);
	}
	
	// 処理を開始してよくなったら呼ばれる
	public void StartProcess()
	{
		m_nStates = 0;	// 処理開始
		Img.enabled = true;
	}

	// ボタンが点滅してよくなったら呼ばれる
	public void StartFlash()
	{
		m_nStates = 2;	// 点滅開始
	}

	private void Skip()
	{
		// タップ
		if (m_nStates != 2 && GameObject.Find("Fade").GetComponent<Fade>().GetTouch() &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			Img.enabled = true;
			m_fAlpha = 1.0f;
			Img.color = new Color(0.5f, 0.5f, 0.5f, 1.0f);

			m_nStates = 2;
		}
		// マウス
		if (m_nStates != 2 && Input.GetMouseButtonDown(0) &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			Img.enabled = true;
			m_fAlpha = 1.0f;
			Img.color = new Color(0.5f, 0.5f, 0.5f, 1.0f);

			m_nStates = 2;
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

					// 背景と旗と雲の処理開始
					GameObject.Find("BackGround").GetComponent<BackGround>().StartProcess();
					GameObject.Find("Cloud").GetComponent<Cloud>().StartProcess();
					GameObject.Find("Hata").GetComponent<Hata>().StartProcess();
				}
				Img.color = new Color(0.5f, 0.5f, 0.5f, m_fAlpha);
				break;

			case 1:		// フェードインが完了して何も処理をしていない
				break;

			case 2:		// 点滅
				m_fRGB += m_fChangeRGB;
				if (m_fRGB >= m_fMaxRGB)
					m_fChangeRGB = -m_fChangeRGB;
				if (m_fRGB <= 0.5f)
					m_fChangeRGB = -m_fChangeRGB;
				Img.color = new Color(m_fRGB, m_fRGB, m_fRGB, 1.0f);
				break;
		}
	}
}
