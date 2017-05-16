using UnityEngine;
using System.Collections;
using System.Collections.Generic;	// リスト使用のため

public class MainLoop : MonoBehaviour {
	// メインループで管理するスクリプト
	PuzzleMain			PuzzleMain_cs;
	public List<Player>	Player_csList;		// 配列
	playerspown			Playerspown_cs;
	public List<Enemy>	Enemy_csList;		// 配列
	EnemySpown_S1		Enemyspown_1_cs;
	EnemySpown_S2		Enemyspown_2_cs;
	EnemySpown_S3		Enemyspown_3_cs;
	EnemySpown_S4		Enemyspown_4_cs;
	EnemySpown_S5		Enemyspown_5_cs;
	SpeedUp				SpeedUp_cs;

	public int DethCnt = 0;
	public GameObject GameCamera;
	public GameObject CatIncamera;
	public GameObject Par;

	Pause				Pause_cs;			// ポーズ用
	public bool pauseF;

	static int StageNumber;
	int EnemyCnt = 0;
	float EndTime = 0;
	public bool EnemyEndFlg = false;
	public bool PlayerEndFlg = false;
	
	bool bGameStart;	// スタートの文字が走り終わって, ゲームの処理を開始してもいいかどうか

	public GameObject Kamihubuki;
	bool bKami;

	public bool CameraChangeFlg = false;
	float CameraCnt = 0;

	// Use this for initialization
	void Start ()
	{
		bGameStart = false;	// 最初は処理しない
		bKami = false;
		CameraChangeFlg = false;

		// スクリプトの取得
		PuzzleMain_cs	= GameObject.Find ("PuzzleMain").GetComponent<PuzzleMain>();
		Playerspown_cs	= GameObject.Find ("Playerspown").GetComponent<playerspown>();
		switch(StageNumber)
		{
		case 1:
			Enemyspown_1_cs	= GameObject.Find ("EnemySpown").GetComponent<EnemySpown_S1>();
			EnemyCnt = 5;
			break;
		case 2:
			Enemyspown_2_cs	= GameObject.Find ("EnemySpown").GetComponent<EnemySpown_S2>();
			EnemyCnt = 6;
			break;
		case 3:
			Enemyspown_3_cs	= GameObject.Find ("EnemySpown").GetComponent<EnemySpown_S3>();
			EnemyCnt = 10;
			break;
		case 4:
			Enemyspown_4_cs	= GameObject.Find ("EnemySpown").GetComponent<EnemySpown_S4>();
			EnemyCnt = 3;
			break;
		case 5:
			Enemyspown_5_cs	= GameObject.Find ("EnemySpown").GetComponent<EnemySpown_S5>();
			EnemyCnt = 6;
			break;
		}
		Pause_cs		= GameObject.Find ("Pause").GetComponent<Pause> ();
		SpeedUp_cs		= GameObject.Find ("SpeedUp").GetComponent<SpeedUp> ();

		// リスト作成
		Player_csList	= new List<Player>();
		Enemy_csList	= new List<Enemy>();


		//音のロード
		Sound.LoadSe("SE_Mis","Mis_SE");
		Sound.LoadSe("SE_Hit","Hit_SE");
		Sound.LoadSe("loose","SE_Lose");
		Sound.LoadSe ("SlideMove", "SE_PuzzleMove");
		Sound.LoadBgm("Stage_BGM","GAME_BGM");
		Sound.LoadSe ("Clear", "SE_clear");
		Sound.LoadSe ("Attention", "SE_Attention");
		Sound.LoadSe ("Signal", "SE_Signal");
		Sound.LoadSe ("Start", "SE_Start");
		Sound.LoadSe ("Boko", "SE_Boko");
		Sound.LoadSe ("tetele", "SE_tetele");
		Sound.LoadSe ("MeFly", "SE_MeFly");
		//Sound.PlaySe ("Fly");]

		EnemyEndFlg = false;
		PlayerEndFlg = false;
	}

	
	// Update is called once per frame
	void Update ()
	{
		if (!bGameStart)
			return;

		if (Input.GetKeyDown (KeyCode.Q)) {
			CameraChange();
		}

		if (CameraChangeFlg) {
			CameraCnt += Time.deltaTime;
			if(CameraCnt >= 1){
				CameraCnt = 0;
				CameraChangeFlg = false;
				CatIncamera.SetActive(false);
				GameCamera.SetActive (true);
				Par.SetActive(false);
			}
		}

		pauseF = Pause_cs.m_bPause;

		if (!Pause_cs.m_bPause)
		{
			PuzzleMain_cs.Up ();
			Playerspown_cs.Up ();
			SpeedUp_cs.Up();
			switch(StageNumber)
			{
			case 1:
				Enemyspown_1_cs.Up ();
				break;
			case 2:
				Enemyspown_2_cs.Up ();
				break;
			case 3:
				Enemyspown_3_cs.Up ();
				break;
			case 4:
				Enemyspown_4_cs.Up ();
				break;
			case 5:
				Enemyspown_5_cs.Up ();
				break;
			}

			if(PlayerEndFlg == true){
				// 花吹雪作成
				if(!bKami)
				{
					bKami = true;
					Instantiate(Kamihubuki);
				}

				EndTime += Time.deltaTime;
				if(EndTime >= 3.0f){
					switch (StageNumber) {
					case 1:
						ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_1);
						EnemyCatapult.SetClearStage (Fade.NEXTSCENE.STAGE_1);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.RESULR);
					break;
					case 2:
						ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_2);
						EnemyCatapult.SetClearStage (Fade.NEXTSCENE.STAGE_2);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.RESULR);
						break;
					case 3:
						ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_3);
						EnemyCatapult.SetClearStage (Fade.NEXTSCENE.STAGE_3);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.RESULR);
						break;
					case 4:
						ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_4);
						EnemyCatapult.SetClearStage (Fade.NEXTSCENE.STAGE_4);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.RESULR);
						break;
					case 5:
						ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_5);
						EnemyCatapult.SetClearStage (Fade.NEXTSCENE.STAGE_5);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.RESULR);
						break;
					}
				}
			}

			if(EnemyEndFlg == true){
				EndTime += Time.deltaTime;
				if(EndTime >= 2.0f){
					EnemyEndFlg = false;
					switch (StageNumber) {
					case 1:
						RetryButton.SetLoseStage (Fade.NEXTSCENE.STAGE_1);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.GAMEOVER);
						break;
					case 2:
						RetryButton.SetLoseStage  (Fade.NEXTSCENE.STAGE_2);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.GAMEOVER);
						break;
					case 3:
						RetryButton.SetLoseStage (Fade.NEXTSCENE.STAGE_3);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.GAMEOVER);
						break;
					case 4:
						RetryButton.SetLoseStage  (Fade.NEXTSCENE.STAGE_4);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.GAMEOVER);
						break;
					case 5:
						RetryButton.SetLoseStage  (Fade.NEXTSCENE.STAGE_5);
						Sound.StopBgm ();
						GameObject.Find ("Fade").GetComponent<Fade> ().FadeStart (Fade.NEXTSCENE.GAMEOVER);
						break;
					}
				}
			}

			//for (int i = 0; i < Player_csList.Count; i ++)
			//	Player_csList [i].Up ();
			//for (int i = 0; i < Enemy_csList.Count; i ++)
			//	Enemy_csList [i].Up ();
		}
		else
		{
			Pause_cs.Up();
		}
	}

	public void EnemyEnd(){
		EnemyCnt -= 1;
		if (EnemyCnt == 0) {
			Sound.PlaySe ("Clear");
			PlayerEndFlg = true;
		}
	}



	// ポーズの変更により、スクリプトを操作する
	public void ChangePause()
	{
		if (Pause_cs.m_bPause)
		{// ポーズ開始
			// Collider2D無効
		//for (int i = 0; i < Player_csList.Count; i ++)
		//	Player_csList [i].StopCollider ();
		//for (int i = 0; i < Enemy_csList.Count; i ++)
		//	Enemy_csList [i].StopCollider ();
		}
		else
		{// ポーズ終了
			// Collider2D有効
		//for (int i = 0; i < Player_csList.Count; i ++)
		//	Player_csList [i].AwakeCollider ();
		//for (int i = 0; i < Enemy_csList.Count; i ++)
		//	Enemy_csList [i].AwakeCollider ();
		}

	}
	
	
	// 新たに生成されたプレイヤー(Clone)の持つスクリプトをリストにセットする
	public int AddPlayer_csList(Player player_cs)
	{
		Player_csList.Add (player_cs);
		return Player_csList.Count - 1;	// 追加したスクリプトがリストの何番目に入っているかを返す
	}

	// 新たに生成された敵Clone)の持つスクリプトをのリストにセットする
	public int AddEnemy_csList(Enemy enemy_cs)
	{
		Enemy_csList.Add (enemy_cs);
		return Enemy_csList.Count - 1;	// 追加したスクリプトがリストの何番目に入っているかを返す
	}
	
	// プレイヤー(Clone)が削除されたときにスクリプトをリストから削除する
	public void DeletePlayer_csList(int index)
	{
		Player_csList.RemoveAt (index);
		
		// 削除したものから後ろのリストのIndex番号がずれたので、それを修正する
		//for (int i = index ; i < Player_csList.Count ; i ++)
		//	Player_csList [i].SubListIndex ();
	}
	
	// 敵(Clone)が削除されたときにスクリプトをリストから削除する
	public void DeleteEnemy_csList(int index)
	{
		Enemy_csList.RemoveAt (index);
		
		// 削除したものから後ろのリストのIndex番号がずれたので、それを修正する
		//for (int i = index ; i < Enemy_csList.Count ; i ++)
		//	Enemy_csList [i].SubListIndex ();
	}

	public static void SetStage(int num){
		StageNumber = num;
	}
	public int GetStage() {
		return StageNumber;
	}

	public void CameraChange(){
		CatIncamera.SetActive(true);
		GameCamera.SetActive (false);
		Par.SetActive (true);
		CameraChangeFlg = true;
	}
	
	// スタートが走り終わって, ゲーム開始できるようになったら呼ばれる
	public void GameStart()
	{
		bGameStart = true;

		if (StageNumber == 1 ||
			StageNumber == 2 ||
			StageNumber == 3 ||
			StageNumber == 4) {
			Sound.PlayBgm ("Stage_BGM");
		} else {
			Sound.PlayBgm ("Stage_BOSS");
		}
	}
	
	// スタートが走り終わって, ゲーム開始できるようになったら呼ばれる
	public bool GetGameStart()
	{
		return bGameStart;
	}
}
