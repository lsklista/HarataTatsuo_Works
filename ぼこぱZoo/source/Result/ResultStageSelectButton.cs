using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ResultStageSelectButton : MonoBehaviour {
	[SerializeField] float m_fFadeIOTime;		// ボタンがフェードインしてくる時間(秒)
	
	Image Img;
	float m_fAlpha;								// 現在のアルファ値
	float m_fAddAlpha;							// 1ループあたりのアルファ値の増加量
	
	int m_nStates;	// -1・・・ フェードイン中の何もしない
					// 0 ・・・ フェードイン中
					// 1 ・・・ フェードインが完了して入力待ち
					// 2 ・・・ フェードアウト中
					// 3 ・・・ フェードアウト後の何もしない
	
	bool m_bFirstTouch;
	
	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 0.0f;
		m_fAddAlpha = (1.0f / m_fFadeIOTime) / 30.0f;
		
		m_nStates = -1;		// 最初は何もしない
		
		m_bFirstTouch = false;
		
		Img = GetComponent<Image> ();
		Img.color = new Color (1.0f, 1.0f, 1.0f, 0.0f);
		Img.enabled = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		// スキップ処理
		Skip();

		// ステート処理
		State();
	}
	
	public void StartProgress()
	{
		m_nStates = 0;	// 処理開始
		Img.enabled = true;
	}
	
	// 「次へ」ボタンが押されたら呼ばれる
	public void OnTapButton()
	{
		if (Img.color.a != 1.0f)
			return;
		
		if (m_bFirstTouch)
			return;

		// フェードアウト処理開始
		StartFadeOut ();
		GameObject.Find ("NextButton").GetComponent<ResultNextButton>().StartFadeOut();
		
		// はむち上移動開始
		GameObject.Find ("Hamuti").GetComponent<ResultHamuti>().StartUpMove();

		// はむちに, 次に遷移するシーンをわたす
		GameObject.Find ("Hamuti").GetComponent<ResultHamuti> ().SetNextScene (Fade.NEXTSCENE.STAGESELECT);
		
		// ボタンがタップされた音を鳴らす
		Sound.PlaySe ("SE_Enter");
		
		// ステセレシーンに, BGMは再生するように設定する
		Main_SS.SetPlayBGM (true);
		
		// ボタンがクリックされたので花火を止める
		GameObject.Find ("Hanabi").GetComponent<ResultHanabi> ().StopHanabi();
	}

	// フェードアウト処理開始
	public void StartFadeOut()
	{
		m_nStates = 2;	// フェードアウト開始
	}

	// スキップ処理
	private void Skip()
	{
		// タップ
		if ((m_nStates == -1 || m_nStates == 0) &&
			Input.touchCount == 1 &&
			Input.GetTouch(0).phase == TouchPhase.Began &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			Img.enabled = true;

			m_fAlpha = 1.0f;	// アルファ値加算
			Img.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			m_bFirstTouch = true;
			m_nStates = 1;
		}
		// 1タップ目が終わったかどうかの判定
		if (m_bFirstTouch &&
			Input.touchCount == 1 &&
			Input.GetTouch(0).phase == TouchPhase.Ended)
		{
			m_bFirstTouch = false;	// 1タップ目終了
		}

		// マウス
		if ((m_nStates == -1 || m_nStates == 0) && Input.GetMouseButtonDown(0) &&
			!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
		{
			Img.enabled = true;

			m_fAlpha = 1.0f;	// アルファ値加算
			Img.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);

			m_nStates = 1;
		}
	}

	// ステート処理
	private void State()
	{
		switch (m_nStates)
		{
			case -1:	// フェードイン前の何もしない
				break;

			case 0:		//フェードイン中
				m_fAlpha += m_fAddAlpha;
				if (m_fAlpha >= 1.0f)
				{
					m_fAlpha = 1.0f;	// アルファ値加算
					m_nStates++;		// ステータス変化
				}
				Img.color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 1:		// フェードインが完了して何も処理をしていない
				break;

			case 2:		// フェードアウト中
				m_fAlpha -= m_fAddAlpha;
				if (m_fAlpha <= 0.0f)
				{
					m_fAlpha = 0.0f;	// アルファ値加算
					m_nStates++;		// ステータス変化
				}
				Img.color = new Color(1.0f, 1.0f, 1.0f, m_fAlpha);
				break;

			case 3:		// フェードアウト後の何もしない
				break;
		}
	}
}
