using UnityEngine;
using System.Collections;

public class Fade : MonoBehaviour {
	// 次にどこのシーンに遷移するかの列挙型
	public enum NEXTSCENE
	{
		NONE,			// なし
		TITLE,			// タイトル
		STORY_MAE,		// ストーリー(前)
		STAGESELECT,	// ステージセレクト
		STAGE_1,		// ステージ1
		STAGE_2,		// ステージ2
		STAGE_3,		// ステージ3
		STAGE_4,		// ステージ4
		STAGE_5,		// ステージ5
		RESULR,			// リザルト(クリア)
		GAMEOVER,		// ゲームオーバー(失敗)
		STORY_ATO		// ストーリー(後)
	};

	public bool m_bFade;			// フェード(publicなのはポーズバックとポーズステセレで使うから)
	public bool m_bFadeIn;			// フェードイン(publicなのはgameoverやresultで使うから)
	bool m_bFadeOut;				// フェードアウト
	bool m_bFadeInterval;			// フェードインとフェードアウトの間

	public int 	m_nFadeFrame;		// フェードにかかる時間(フレーム数)
	public int 	m_nIntervalFrame;	// フェードインとフェードアウトの間(フレーム数)
	
	float m_fAlpha;					// 現在のアルファ値
	float m_fChangeAlpha;			// １フレームあたりのアルファ値の変化量
	public int m_nInterval;			// 現在のインターバルのフレーム数

	NEXTSCENE m_NextScene;			// 次に遷移するシーン
	bool m_bSceneMove;				// シーン遷移が開始していたらtrue
	bool m_bOneFrame;				// フェードが開始して1フレーム目かどうかのフラグ(1フレーム目ならtrue)


	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 1.0f;
		m_fChangeAlpha = 1.0f / m_nFadeFrame;
		m_nInterval = 0;

		m_bFade = true;
		m_bFadeIn = true;
		m_bFadeOut = false;
		m_bFadeInterval = false;

		m_NextScene = NEXTSCENE.NONE;

		m_bSceneMove = true;
		m_bOneFrame = true;		// trueでもfalseでも正直かわならい
		GetComponent<SpriteRenderer> ().enabled = true;		// フェード用画像を描画する
	}
	
	// Update is called once per frame
	void Update ()
	{
		// バックボタンでアプリ終了
		Quit();

		// フェードしていたら処理
		FadeProgress();
	}


	// この関数を呼んで、フェード＆シーン遷移する。
	// GameObject FadeObj = GameObject.Find("Fade");
	// Fade Fade_cs = FadeObj.GetComponent<Fade> ();
	// Fade_cs.FadeStart(Fade.NEXTSCENE.RESULR);
	// この３行をコピペして、３行目の引数を変える
	public void FadeStart(NEXTSCENE nextscene)
	{
		// シーン遷移が開始していたら、無効
		if (m_bSceneMove)
			return;

		m_bFade = true;				// フェード開始
		m_bFadeOut = true;			// フェードアウト開始
		m_nInterval = 0;			// 現在のインターバル時間初期化
		m_NextScene = nextscene;	// 次に遷移するシーンをセット
		m_bSceneMove = true;		// シーン遷移開始
		m_bOneFrame = true;			// 1フレーム目の情報は受け取らない
		GetComponent<SpriteRenderer> ().enabled = true;;	// フェード用を画像する
	}

	public bool GetTouch()
	{
		if (Input.touchCount == 1)
		{
			if (Input.GetTouch (0).phase == TouchPhase.Began)
			{
				return true;
			}
		}
		return false;
	}

	/// シーン遷移
	void SceneMove()
	{
		switch(m_NextScene)
		{
		case NEXTSCENE.TITLE:
			Application.LoadLevel ("Title");
			break;
			
		case NEXTSCENE.STORY_MAE:
			Application.LoadLevel ("Story_mae");
			break;
			
		case NEXTSCENE.STAGESELECT:
			Application.LoadLevel ("StageSelect");
			break;
			
		case NEXTSCENE.STAGE_1:
			MainLoop.SetStage(1);
			Application.LoadLevel ("Stage_1");
			break;
			
		case NEXTSCENE.STAGE_2:
			MainLoop.SetStage(2);
			Application.LoadLevel ("Stage_2");
			break;
			
		case NEXTSCENE.STAGE_3:
			MainLoop.SetStage(3);
			Application.LoadLevel ("Stage_3");
			break;
			
		case NEXTSCENE.STAGE_4:
			MainLoop.SetStage(4);
			Application.LoadLevel ("Stage_4");
			break;
			
		case NEXTSCENE.STAGE_5:
			MainLoop.SetStage(5);
			Application.LoadLevel ("Stage_5");
			break;
			
		case NEXTSCENE.RESULR:
			Application.LoadLevel ("Result");
			break;
			
		case NEXTSCENE.GAMEOVER:
			Application.LoadLevel ("GameOver");
			break;
			
		case NEXTSCENE.STORY_ATO:
			Application.LoadLevel ("Story_ato");
			break;
			
		case NEXTSCENE.NONE:
			break;
		}
	}

	// アプリケーション終了
	private void Quit()
	{
		// エスケープキー取得
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			// プラットフォームがアンドロイドかチェック
			if (Application.platform == RuntimePlatform.Android)
			{
				// ゲームメイン中だったら終了しない
				if (Application.loadedLevelName == "Title" ||
				   Application.loadedLevelName == "STORY_MAE" ||
				   Application.loadedLevelName == "StageSelect" ||
				   Application.loadedLevelName == "Result" ||
				   Application.loadedLevelName == "GAMEOVER" ||
				   Application.loadedLevelName == "STORY_ATO")
				{
					// アプリケーション終了
					Application.Quit();
					return;
				}
			}
		}
	}

	// フェード処理
	private void FadeProgress()
	{
		if (m_bFade)
		{
			// フェードイン処理
			if (m_bFadeIn)
			{
				m_fAlpha -= m_fChangeAlpha;
				if (m_fAlpha < 0.0f)
				{
					m_fAlpha = 0.0f;
					m_bFadeIn = false;
					m_bFade = false;
					m_bSceneMove = false;	// シーン遷移完了
					GetComponent<SpriteRenderer>().enabled = false;	// フェード用を画像しない
				}

				//色変更
				GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, m_fAlpha);
			}

			// フェードアウト処理
			if (m_bFadeOut)
			{
				m_fAlpha += m_fChangeAlpha;
				if (m_fAlpha > 1.0f)
				{
					m_fAlpha = 1.0f;
					m_bFadeOut = false;
					m_bFadeInterval = true;
				}

				//色変更
				GetComponent<SpriteRenderer>().color = new Color(0.0f, 0.0f, 0.0f, m_fAlpha);
				m_bOneFrame = false;	// フェードが開始してから1フレーム目は終わり
			}

			// インターバル
			if (m_bFadeInterval)
			{
				m_nInterval++;
				if (m_nInterval >= m_nIntervalFrame)
				{
					m_nInterval = 0;
					m_bFadeInterval = false;
					m_bFade = false;

					// bgmとめる
					Sound.StopBgm();

					// シーン遷移
					SceneMove();
				}
			}
		}
	}
}
