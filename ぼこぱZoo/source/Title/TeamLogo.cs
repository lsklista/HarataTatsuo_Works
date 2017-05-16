using UnityEngine;
using System.Collections;

public class TeamLogo : MonoBehaviour {
	public float m_fStartWaitTime;		// ゲームが始まってからチームロゴがフェードインしてくるまでの時間
	public float m_fFadeIOTime;			// フェードイン / アウトにかける時間
	public float m_fFadeInterval;		// フェードインが完了してからフェードアウトを開始するまでの時間
	public float m_fNextCallTime;		// フェードアウトが終了してからタイトルロゴがフェードインしてくるまでの時間

	float m_fTime;						// タイマー
	float m_fAlpha;						// 現在のアルファ値
	float m_fAddAlpha;					// 1フレームあたりのアルファ値の増加量

	int m_nStates;	// 0 ・・・ フェードイン前
					// 1 ・・・ フェードイン中
					// 2 ・・・ フェードインとフェードアウトの間
					// 3 ・・・ フェードアウト中
					// 4 ・・・ フェードアウト後
					// 5 ・・・ 全て終了


	// Use this for initialization
	void Start ()
	{
		m_fTime = 0.0f;
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeIOTime) / 30.0f;

		m_nStates = 0;

		GetComponent<SpriteRenderer> ().color = new Color (1.0f, 1.0f, 1.0f, 0.0f);
		GetComponent<SpriteRenderer> ().enabled = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードイン中ならタップは無効
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;

		// スキップ処理
		Skip();

		State();
	}

	private void Skip()
	{
		// タップ
		if (m_nStates != 5 && GameObject.Find ("Fade").GetComponent<Fade> ().GetTouch ())
		{
			GetComponent<SpriteRenderer> ().enabled = false;
			m_nStates = 5;
		}
		// マウス
		if (m_nStates != 5 && Input.GetMouseButtonDown(0))
		{
			GetComponent<SpriteRenderer> ().enabled = false;
			m_nStates = 5;
		}
	}

	private void State()
	{
		m_fTime += 1.0f / 30.0f;

		switch (m_nStates)
		{
			case 0:		// フェードイン前
				if (m_fTime >= m_fStartWaitTime)
				{
					m_fTime = 0.0f;			// 時間初期化
					m_nStates = 1;			// ステータス変化

					GetComponent<SpriteRenderer>().enabled = true;
				}
				break;

			case 1:		// フェードイン中
				m_fAlpha += m_fAddAlpha;	// アルファ値加算
				if (m_fAlpha >= 1.0f)
				{
					m_fTime = 0.0f;			// 時間初期化
					m_fAlpha = 1.0f;		// アルファ値を最大に
					m_nStates = 2;			// ステータス変化
				}
				GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 2:		// フェードインとフェードアウトの間
				if (m_fTime >= m_fFadeInterval)
				{
					m_fTime = 0.0f;			// 時間初期化
					m_nStates = 3;			// ステータス変化
				}
				break;

			case 3:		// フェードアウト中
				m_fAlpha -= m_fAddAlpha;	// アルファ値減算
				if (m_fAlpha <= 0.0f)
				{
					m_fTime = 0.0f;			// 時間初期化
					m_fAlpha = 0.0f;		// アルファ値を最小に
					m_nStates = 4;			// ステータス変化

					GetComponent<SpriteRenderer>().enabled = false;
				}
				GetComponent<SpriteRenderer>().color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 4:		// フェードアウト後
				if (m_fTime >= m_fNextCallTime)
				{
					// タイトルロゴを描画開始
					GameObject.Find("TitleLogo").GetComponent<TitleLogo>().StartProcess();

					// ここでスタートボタンを表示開始すると
					// タイトルロゴとボタンが重なるので
					// タイトルロゴが移動中のときに呼ぶのがいいかも
					//GameObject.Find("StartButton").GetComponent<StartButton>().StartProcess();

					m_nStates = 5;			// ステータス変化
				}
				break;

			case 5:		// 全て終了
				break;
		}
	}
}
