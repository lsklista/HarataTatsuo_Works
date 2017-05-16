using UnityEngine;
using System.Collections;

public class ResultHamuti : MonoBehaviour {
	GameObject Omedetou;
	GameObject Himo;

	[SerializeField] Vector2 StartPos;				// はむちの初期座標
	[SerializeField] Vector2 OmedetouDifference;	// 「おめでとう」との相対距離
	[SerializeField] Vector2 HimoDifference;		// 「ひも」との相対距離

	[SerializeField] float fSpeedX;					// X方向の移動速度
	float fRadian;									// 今のラジアン値
	[SerializeField] float fOneLoopTime;			// 1波長動くのにかかる時間
	float fAddradian;								// 1ループで加算されるラジアン値
	[SerializeField] float fAmplitude;				// 振幅 
	[SerializeField] float fStopPosX;				// 移動中にどこで止まるか
	float fHeni;									// 変位(計算用)
	bool bUpMove;									// 上移動開始の判定をしてもいいかのフラグ
	[SerializeField] float fSpeedY;					// 上移動時の移動速度
	[SerializeField] float fReleasePosY;			// はむちとおめでとうを切り離す座標
	[SerializeField] float fGravity;				// 重力加速度
	float fSpeed;									// 速度(計算用)
	[SerializeField] float fGroundPosY;				// どこを地面とするかのY座標
	[SerializeField] float fCoefficient;			// 地面の反発係数
	[SerializeField] float fLeftMoveWait;			// 着地してから横移動開始するまでの時間
	[SerializeField] float fLeftMoveSpeed;			// 横移動するときのスピード
	[SerializeField] float fLeftMoveAccele;			// 横移動するときの加速度
	[SerializeField] float fStartFadePosX;			// フェードを開始する座標X
	Fade.NEXTSCENE NextScene;						// 次に遷移するシーン

	float fTime;				// タイマー
	float fSixtyFPSTime;		// 60fpsのときの1フレームの時間
	int nStates;	// 0 ・・・ はむち移動中
					// 1 ・・・ 移動完了, 上下移動して待機中
					// 2 ・・・ 上に移動中
					// 3 ・・・ 落下中
					// 4 ・・・ バウンド中
					// 5 ・・・ 移動待ち状態
					// 6 ・・・ 横移動(画面から消える少し前にフェードイン(シーン遷移)開始)
					// 7 ・・・ なにもしない

	bool m_bFirstTouch;

	[SerializeField] float fEyeCatchingTime;		// 上移動を開始してから, アイキャッチ音が鳴るまでの時間
	bool bEyeCatching;								// アイキャッチ音が鳴ったかどうかのフラグ

	float fSETime;	// ぷかぷか音を鳴らすタイマー

	// Use this for initialization
	void Start ()
	{
		Omedetou = GameObject.Find ("Omedetou");
		Himo = GameObject.Find ("Himo");

		fRadian = 0.0f;			// ラジアン値初期化
		fAddradian = (Mathf.PI * 2.0f / fOneLoopTime) / 30.0f;	// 1ループで加算されるラジアン値の計算

		fTime = 0.0f;			// タイマー初期化
		fSixtyFPSTime = 1.0f / 30.0f;	// 60fpsのときの1フレームの時間
		bUpMove = false;		// 最初は上移動開始の判定はしない
		fSpeed = 0.0f;			// 落下時の初速度は0
		nStates = 7;			// 最初は何もしない
		NextScene = Fade.NEXTSCENE.NONE;	// 遷移するシーンは「なし」にしておく

		// 自身と, 「おめでとう」の座標初期化
		transform.position = new Vector3 (StartPos.x, StartPos.y, 0.0f);
		Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
		                                          transform.position.y - OmedetouDifference.y,
		                                          transform.position.z);
		Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
		                                      transform.position.y - HimoDifference.y,
		                                      transform.position.z);

		GetComponent<SpriteRenderer>().enabled = false;

		GetComponent<Animator>().enabled = false;	// 最初アニメーションはしない

		// アイキャッチ音をロード
		Sound.LoadSe ("SE_EyeCatching", "SE_EyeCatching");
		bEyeCatching = false;	// まだ鳴っていない

		Sound.LoadSe ("SE_Huusen", "SE_Huusen");
	}
	
	// Update is called once per frame
	void Update ()
	{
		// スキップ処理
		Skip1 ();		// 移動開始前か, 移動中の時のスキップ
		Skip2 ();		// ボタンが押された後のスキップ

		switch (nStates)
		{
		case 0:		// 移動中(おめでとうも一緒に移動させる)
			Move();
			break;

		case 1:		// 移動完了, 上下移動して待機中
			UpDown();
			break;
		case 2:		// 上に移動中(おめでとうも一緒に移動させる)
			MoveUp();
			break;
			
		case 3:		// 落下中
			Fall();
			break;
			
		case 4:		// バウンド中
			Bound();
			break;
			
		case 5:		// 移動待ち状態
			fTime += fSixtyFPSTime;
			if(fTime >= fLeftMoveWait)
			{
				nStates ++;
				GetComponent<Animator>().enabled = true;	// アニメーション開始
			}
			break;
			
		case 6:		// 横移動(画面から消える少し前にフェードイン(シーン遷移)開始)
			MoveLeft();
			break;

		case 7:		// 何もしない
			break;
		}
	}

	// はむちの移動を開始する
	public void StartHamuti()
	{
		nStates = 0;	// 処理開始
		GetComponent<SpriteRenderer>().enabled = true;	// 描画開始
		Omedetou.GetComponent<SpriteRenderer> ().enabled = true;	// 描画開始
		Himo.GetComponent<SpriteRenderer> ().enabled = true;	// 描画開始
	}

	// はむちの上移動を開始する
	public void StartUpMove()
	{
		//nStates = 2;		// 上移動開始
		bUpMove = true;		// 上移動開始判定開始

		// アイキャッチ音を鳴らす
		//Sound.PlaySe ("SE_EyeCatching");
	}

	// 遷移するシーンを設定する
	public void SetNextScene(Fade.NEXTSCENE nextscene)
	{
		NextScene = nextscene;
	}

	// 移動開始前か, 移動中の時のスキップ処理
	void Skip1()
	{
		// フェード中は処理しない
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;

		// タップ
		if ((nStates == 0 || nStates == 7) &&				// 移動前か, 移動中で,
		    Input.touchCount == 1 && 						// タッチされてて,
		    Input.GetTouch (0).phase == TouchPhase.Began)	// フェーズがbeginだったら, スキップ
		{
			// 描画開始
			GetComponent<SpriteRenderer>().enabled = true;
			Omedetou.GetComponent<SpriteRenderer> ().enabled = true;
			Himo.GetComponent<SpriteRenderer> ().enabled = true;
			
			// 瞬間移動
			transform.position = new Vector3(fStopPosX, transform.position.y, transform.position.z);
			Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
			                                          transform.position.y - OmedetouDifference.y,
			                                          transform.position.z);
			Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
			                                      transform.position.y - HimoDifference.y,
			                                      transform.position.z);
			
			nStates = 1;	// 移動完了状態にしておく
		}
		
		// マウス
		if ((nStates == 0 || nStates == 7) && Input.GetMouseButtonDown(0))
		{
			// 描画開始
			GetComponent<SpriteRenderer>().enabled = true;
			Omedetou.GetComponent<SpriteRenderer> ().enabled = true;
			Himo.GetComponent<SpriteRenderer> ().enabled = true;
			
			// 瞬間移動
			transform.position = new Vector3(fStopPosX, transform.position.y, transform.position.z);
			Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
			                                          transform.position.y - OmedetouDifference.y,
			                                          transform.position.z);
			Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
			                                      transform.position.y - HimoDifference.y,
			                                      transform.position.z);
			
			nStates = 1;	// 移動完了状態にしておく
		}
	}

	// ボタンが押された後のスキップ処理
	// すぐにシーン遷移を開始する
	void Skip2()
	{
		// 遷移先が「なし」なら処理しない
		if (NextScene == Fade.NEXTSCENE.NONE)
			return;

		// タップ
		if (Input.touchCount == 1 && Input.GetTouch (0).phase == TouchPhase.Began)
		{
			GameObject.Find("Fade").GetComponent<Fade>().FadeStart(NextScene);
		}

		// マウス
		if (Input.GetMouseButtonDown (0))
		{
			GameObject.Find("Fade").GetComponent<Fade>().FadeStart(NextScene);
		}

		// BGM停止
		Sound.StopBgm ();
	}

	// 移動
	private void Move()
	{
		fRadian += fAddradian;						// 角度加算
		if (fRadian >= Mathf.PI * 2.0f)
		{
			fRadian -= Mathf.PI * 2.0f;
			Sound.PlaySe("SE_Huusen");
		}
		fHeni = Mathf.Sin(fRadian) * fAmplitude;	// 変位計算

		transform.position = new Vector3(transform.position.x - fSpeedX,
										 transform.position.y + fHeni,
										 transform.position.z);
		Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
												  transform.position.y - OmedetouDifference.y,
												  transform.position.z);
		Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
											  transform.position.y - HimoDifference.y,
											  transform.position.z);

		// 移動完了判定
		if (transform.position.x <= fStopPosX)
		{
			transform.position = new Vector3(fStopPosX, transform.position.y, transform.position.z);
			Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
													  transform.position.y - OmedetouDifference.y,
													  transform.position.z);
			Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
												  transform.position.y - HimoDifference.y,
												  transform.position.z);

			// ボタンの処理を開始する
			GameObject.Find("NextButton").GetComponent<ResultNextButton>().StartProgress();
			GameObject.Find("StageSelectButton").GetComponent<ResultStageSelectButton>().StartProgress();

			nStates++;		// ステータス変化
		}
	}

	// 上下移動して待機
	private void UpDown()
	{
		fRadian += fAddradian;						// 角度加算
		if (fRadian >= Mathf.PI * 2.0f)
		{
			fRadian -= Mathf.PI * 2.0f;
			Sound.PlaySe("SE_Huusen");

			// 上移動開始判定
			if (bUpMove)
				nStates++;		// ステータス変化
		}
		fHeni = Mathf.Sin(fRadian) * fAmplitude;	// 変位計算

		transform.position = new Vector3(fStopPosX,
										 transform.position.y + fHeni,
										 transform.position.z);
		Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
												  transform.position.y - OmedetouDifference.y,
												  transform.position.z);
		Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
											  transform.position.y - HimoDifference.y,
											  transform.position.z);
	}

	// 上へ移動
	private void MoveUp()
	{
		transform.position = new Vector3(transform.position.x,
											 transform.position.y + fSpeedY,
											 transform.position.z);
		Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
												  transform.position.y - OmedetouDifference.y,
												  transform.position.z);
		Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
											  transform.position.y - HimoDifference.y,
											  transform.position.z);

		// アイキャッチ音を鳴らす
		fTime += 1.0f / 30.0f;
		if (fTime >= fEyeCatchingTime && !bEyeCatching)
		{
			fTime = 0.0f;
			bEyeCatching = true;
			Sound.PlaySe("SE_EyeCatching");
		}

		// 切り離し判定
		if (transform.position.y >= fReleasePosY)
		{
			// おめでとうにスピードを与えて, 分かれる
			transform.position = new Vector3(transform.position.x,
											 fReleasePosY,
											 transform.position.z);
			Omedetou.transform.position = new Vector3(transform.position.x - OmedetouDifference.x,
													  transform.position.y - OmedetouDifference.y,
													  transform.position.z);
			Himo.transform.position = new Vector3(transform.position.x - HimoDifference.x,
												  transform.position.y - HimoDifference.y,
												  transform.position.z);
			Omedetou.GetComponent<Omedetou>().SetSpeed(fSpeedY);
			Himo.GetComponent<Himo>().SetSpeed(fSpeedY);

			nStates++;		// ステータス変化
		}
	}

	// 落下
	private void Fall()
	{
		fSpeed -= fGravity;
		transform.position = new Vector3(transform.position.x,
										 transform.position.y + fSpeed,
										 transform.position.z);

		// 地面判定
		if (transform.position.y <= fGroundPosY)
		{
			transform.position = new Vector3(transform.position.x,
											 fGroundPosY,
											 transform.position.z);

			// はねるように移動速度を調整する
			fSpeed *= -fCoefficient;

			nStates++;
		}
	}

	// バウンド
	private void Bound()
	{
		fSpeed -= fGravity;
		transform.position = new Vector3(transform.position.x,
										 transform.position.y + fSpeed,
										 transform.position.z);

		// 地面判定
		if (transform.position.y <= fGroundPosY)
		{
			transform.position = new Vector3(transform.position.x,
											 fGroundPosY,
											 transform.position.z);

			nStates++;
		}
	}

	// 横移動
	private void MoveLeft()
	{
		fLeftMoveSpeed += fLeftMoveAccele;
		transform.position = new Vector3(transform.position.x - fLeftMoveSpeed,
										 transform.position.y,
										 transform.position.z);

		// シーン遷移(フェード開始)
		if (!GameObject.Find("Fade").GetComponent<Fade>().m_bFade &&
			transform.position.x <= fStartFadePosX)
		{
			switch (NextScene)
			{
				case Fade.NEXTSCENE.STAGE_1:
					MainLoop.SetStage(1);
					break;

				case Fade.NEXTSCENE.STAGE_2:
					MainLoop.SetStage(2);
					break;

				case Fade.NEXTSCENE.STAGE_3:
					MainLoop.SetStage(3);
					break;

				case Fade.NEXTSCENE.STAGE_4:
					MainLoop.SetStage(4);
					break;

				case Fade.NEXTSCENE.STAGE_5:
					MainLoop.SetStage(5);
					break;
			}
			GameObject.Find("Fade").GetComponent<Fade>().FadeStart(NextScene);

			// BGM停止
			Sound.StopBgm();
		}
	}
}
