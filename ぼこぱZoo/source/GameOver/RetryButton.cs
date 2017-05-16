using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RetryButton : MonoBehaviour {
	Image img;
	bool m_bStart;					// 処理を開始してよいかどうか(trueなら処理していい)

	float m_fAlpha;					// 現在のアルファ値
	float m_fAddAlpha;				// 1ループあたりのアルファ値の増加量
	[SerializeField] float m_fFadeInTime;		// ボタンがフェードインしてくる時間(秒)

	static Fade.NEXTSCENE LoseStage;// どのステージで負けたのか

	bool m_bFirstTouch;				// 最初のタッチかどうか(実機でのボタン処理に不具合が発生するため)
									// フェードインスキップのつもりでボタンのある箇所をタップして
									// 指を離したら、そのままボタンが押されてしまうため
	
	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 0.0f;								// アルファ値初期化
		m_fAddAlpha = (1.0f / m_fFadeInTime) / 30.0f;	// 1ループあたりのアルファ値の増加量を計算
		m_bStart = false;								// 最初処理してはダメ
		
		
		img = GetComponent<Image>();
		img.color = new Color (img.color.r, img.color.g, img.color.b, 0.0f);	// 最初は描画しない
		img.enabled = false;

		m_bFirstTouch = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		// スキップ関係の処理
		Skip();
		
		// まだ処理開始してはダメならreturn
		if (!m_bStart)
			return;
		
		m_fAlpha += m_fAddAlpha;	// アルファ値加算
		if (m_fAlpha >= 1.0f)
			m_fAlpha = 1.0f;

		img.color = new Color (img.color.r, img.color.g, img.color.b, m_fAlpha);	// アルファ値反映
	}

	// ボタンがタップされたときの処理
	public void OnTapButton()
	{
		// アルファ値が1でなければタップは無効
		if (m_fAlpha != 1.0f)
			return;
		
		// フェード中ならタップは無効
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;

		// 1回目のタッチだった場合は無効
		if (m_bFirstTouch)
			return;
		
		// ボタンがタップされた音を鳴らす
		Sound.PlaySe ("SE_Enter");

		Sound.StopBgm ();

		// 負けたステージに遷移
		GameObject.Find("Fade").GetComponent<Fade>().FadeStart(LoseStage);
	}
	
	
	// 処理が開始されるときに呼ばれる関数
	public void StartProcess()
	{
		m_bStart = true;
		img.enabled = true;
	}

	public static void SetLoseStage(Fade.NEXTSCENE losestage)
	{
		LoseStage = losestage;
	}

	// スキップ関係の処理
	private void Skip()
	{
		// 1回目のタッチが終わったかどうかの判定
		if (Input.touchCount == 1)
		{
			if (Input.GetTouch(0).phase == TouchPhase.Ended)
			{
				m_bFirstTouch = false;	// 1回目のタッチ終了
			}
		}

		// アルファ値が1になっていたらreturn
		if (m_fAlpha == 1.0f)
			return;

		// タップされたらアルファ値を1にする
		if (Input.touchCount == 1)
		{
			if (Input.GetTouch(0).phase == TouchPhase.Began)
			{
				// フェード中だったら無効
				if (!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
				{
					m_bStart = true;
					m_fAlpha = 1.0f;
					img.enabled = true;

					m_bFirstTouch = true;	// 1回目のタッチ開始
				}
			}
		}

		// マウスでクリックされたらアルファ値を1にする
		if (Input.GetMouseButtonDown(0))
		{
			// フェード中だったら無効
			if (!GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
			{
				m_bStart = true;
				m_fAlpha = 1.0f;
			}
		}
	}
}
