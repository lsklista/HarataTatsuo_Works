using UnityEngine;
using System.Collections;

public class tocyuuFade : MonoBehaviour {
	public bool m_bFade;			// フェード(publicなのはポーズバックとポーズステセレで使うから)
	public bool m_bFadeIn;			// フェードイン(publicなのはgameoverやresultで使うから)
	bool m_bFadeOut;				// フェードアウト
	bool m_bFadeInterval;			// フェードインとフェードアウトの間
	
	public int 	m_nFadeFrame;		// フェードにかかる時間(フレーム数)
	public int 	m_nIntervalFrame;	// フェードインとフェードアウトの間(フレーム数)
	
	float m_fAlpha;					// 現在のアルファ値
	float m_fChangeAlpha;			// １フレームあたりのアルファ値の変化量
	public int m_nInterval;			// 現在のインターバルのフレーム数

	public GameObject Setumei;
	
	
	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 0.0f;
		m_fChangeAlpha = 1.0f / m_nFadeFrame;
		m_nInterval = 0;
		
		m_bFade = false;
		m_bFadeIn = false;
		m_bFadeOut = false;
		m_bFadeInterval = false;

		GetComponent<SpriteRenderer> ().enabled = false;		// フェード用画像を描画する

		//Setumei.GetComponent<Canvas>().worldCamera = GameObject.Find("Main Camera").camera;
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードしていたら処理
		if(m_bFade)
		{
			// フェードイン処理
			if(m_bFadeIn)
			{
				m_fAlpha -= m_fChangeAlpha;
				if(m_fAlpha < 0.0f)
				{
					m_fAlpha = 0.0f;
					m_bFadeIn = false;
					m_bFade = false;
					GetComponent<SpriteRenderer>().enabled = false;	// フェード用を画像しない

					Destroy(this.gameObject);
				}
				
				//色変更
				GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, m_fAlpha);
			}
			
			// フェードアウト処理
			if(m_bFadeOut)
			{
				m_fAlpha += m_fChangeAlpha;
				if(m_fAlpha > 1.0f)
				{
					m_fAlpha = 1.0f;
					m_bFadeOut = false;
					m_bFadeInterval = true;

					Sound.StopBgm();

					Instantiate(Setumei);
					Destroy(GameObject.Find("STORY"));
				}
				
				//色変更
				GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, m_fAlpha);
			}
			
			// インターバル
			if(m_bFadeInterval)
			{
				m_nInterval ++;
				if(m_nInterval >= m_nIntervalFrame)
				{
					m_nInterval = 0;
					m_bFadeInterval = false;
					m_bFadeIn = true;
				}
			}
		}
	}
	
	
	// この関数を呼んで、フェード＆シーン遷移する
	public void FadeStart()
	{
		m_bFade = true;				// フェード開始
		m_bFadeOut = true;			// フェードアウト開始
		GetComponent<SpriteRenderer> ().enabled = true;;	// フェード用を画像する
	}
}
