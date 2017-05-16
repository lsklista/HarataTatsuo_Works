using UnityEngine;
using System.Collections;
using System.Collections.Generic;	// リスト使用のため

public class EnemyCatapult : MonoBehaviour {
	[SerializeField] Vector2 CatapultPos;		// 敵の発射座標

	[SerializeField] GameObject[]	EnemyArray = new GameObject[14];	// 雑魚敵の配列
	[SerializeField] GameObject[] BossArray = new GameObject[4];		// ボスの配列
	List<GameObject>	CatapultList;						// 射出する敵のリスト
	List<GameObject> CatapultBossList;						// 射出するボスのリスト

	int[,] EnemyIndex =
	{
		{ 0,  0,  2,  2,  2},	// ステージ1で出てくる敵のインデックス番号
		{ 6,  4,  7,  5, -1},	// ステージ2で出てくる敵のインデックス番号
		{ 8, 10,  3,  9, 11},	// ステージ3で出てくる敵のインデックス番号
		{-1, -1, -1, -1, -1},	// ステージ4で出てくる敵のインデックス番号
		{ 1, 12, 13, -1, -1} 	// ステージ5で出てくる敵のインデックス番号
	};
	int nInjectionNum;		// 現在何番目の敵まで打ち出したか
	int[,] BossIndex =
	{
		{-1, -1, -1},	// ステージ1で出てくるボスのインデックス番号
		{-1, -1, -1},	// ステージ2で出てくるボスのインデックス番号
		{-1, -1, -1},	// ステージ3で出てくるボスのインデックス番号
		{ 1,  2,  0},	// ステージ4で出てくるボスのインデックス番号
		{ 3, -1, -1}	// ステージ5で出てくるボスのインデックス番号
	};
	int nInjectionBossNum;	// 現在何番目のボスまで打ち出したか
	static int nClearStage;	// EnemyIndexの左側の添字(クリアしたステージの番号 - 1)

	[SerializeField] float fInjectionInterval;		// 敵の射出間隔
	[SerializeField] float fInjectionBossInterval;	// ボスの発射間隔
	int[] nSameDirection;							// 現在何回同じ方向に連続で射出したか(3回連続はまずい気がする)
	float fTime;
	
	[SerializeField] Vector2 EnemyMinSpeed;			// 敵の最小移動速度
	[SerializeField] Vector2 EnemyMaxSpeed;			// 敵の最大移動速度
	[SerializeField] float EnemyGravity;			// 敵の下方向にかかる加速度
	[SerializeField] float EnemyMinAngle;			// 1秒間に回転する最小の角度
	[SerializeField] float EnemyMaxAngle;			// 1秒間に回転する最大の角度

	[SerializeField] Vector2 BossStartSpeed;		// ボスの初速度
	[SerializeField] float BossSpeedX4;				// ステージ4のボスを打ち出す時のX方向の移動速度(他の2体は, プラマイ逆と0)
	[SerializeField] float BossGravity;				// ボスの下方向にかかる加速度
	[SerializeField] float BossStartScale;			// ボスの最初の拡大率
	[SerializeField] float BossFinScale;			// ボスが爆発するときの拡大率
	[SerializeField] float BossBombTime;			// ボスが発射されてから爆発するまでの時間

	static int nStates;		// 0 ・・・ 初期化処理
							// (0.5) ・・・ 雑魚敵発射前の待ち時間
							// 1 ・・・ 雑魚敵射出中
							// 2 ・・・ ボス発射までの待ち時間
							// 3 ・・・ ボス射出中
							// 4 ・・・ ボス後の待ち時間
							// 5 ・・・ 何もしない

	[SerializeField] float fBossWaitTime;			// ボス発射までの待ち時間
	[SerializeField] float fFinBossWaitTime;		// ボス発射後の待ち時間(この後にステージクリアとかの演出に続く)

	int nChannel;	// SEのチャンネル

	// Use this for initialization
	void Start ()
	{
		fTime = 0.0f;			// タイマー初期化
		nInjectionNum = 0;		// 打ち出した敵の数を初期化
		nInjectionBossNum = 0;	// 打ち出したボスの初期化
		nSameDirection = new int[3]{-1, -1, -1}; 	// 方向配列を初期化(3回連続は避けたいので, 要素数は3)

		// リスト作成
		CatapultList = new List<GameObject>();
		CatapultBossList = new List<GameObject>();

		// 自身の座標を, 敵の発射座標にしておく
		transform.position = new Vector3 (CatapultPos.x, CatapultPos.y, 0.0f);

		// 音をロード, 再生する
		InitSound();
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードイン中なら処理はしない
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFadeIn)
			return;

		// スキップ処理
		Skip();

		switch (nStates)
		{
		case 0:		// 発射の初期化処理
			InitCatapult();
			break;

		case 1:		// 雑魚敵射出
			FireEnemy();
			break;
			
		case 2:		// ボス発射までの待ち時間
			WaitFireBoss();
			break;
			
		case 3:		// ボス発射中(ここにきたということは, 打ち出すボスが1体以上いる)
			FireBoss();
			break;

		case 4:		// はむち起動までの待ち時間
			WaitHamuti();
			break;
			
		default:		// 何もしない
			break;
		}
	}

	// クリアしたステージ番号をセット
	// ゲームをクリアした場合にこの関数を呼んでください。
	public static void SetClearStage(Fade.NEXTSCENE clearstage)
	{
		switch (clearstage)
		{
		case Fade.NEXTSCENE.STAGE_1:
			nClearStage = 0;	// ステ1が, 配列[0, X]なので-1しておく
			break;
			
		case Fade.NEXTSCENE.STAGE_2:
			nClearStage = 1;
			break;
			
		case Fade.NEXTSCENE.STAGE_3:
			nClearStage = 2;
			break;
			
		case Fade.NEXTSCENE.STAGE_4:
			nClearStage = 3;
			break;
			
		case Fade.NEXTSCENE.STAGE_5:
			nClearStage = 4;
			break;
		}

		nStates = 0;				// 処理開始
	}

	// 音関係初期化
	private void InitSound()
	{
		Sound.LoadBgm("BGM_Clear", "BGM_Clear");
		Sound.LoadSe("SE_Fly", "SE_Fly");

		Sound.PlayBgm("BGM_Clear");
		nChannel = 1;	// 最初, チャンネルは1にする
	}

	// スキップ処理
	private void Skip()
	{
		// タップ
		if (nStates != 5 && // ステータスが5じゃなくて,
			Input.touchCount == 1 && // タッチされてて,
			Input.GetTouch(0).phase == TouchPhase.Began)	// フェーズがbeginだったら, スキップ
		{
			// 発射して, まだ消えていない敵を消す
			GameObject[] tagobjs = GameObject.FindGameObjectsWithTag("Enemy");
			foreach (GameObject obj in tagobjs)
				Destroy(obj);

			nStates = 5;	// 何もしない状態にしておく
		}

		// マウス
		if (nStates != 5 && Input.GetMouseButtonDown(0))
		{
			// 発射して, まだ消えていない敵を消す
			GameObject[] tagobjs = GameObject.FindGameObjectsWithTag("Enemy");
			foreach (GameObject obj in tagobjs)
				Destroy(obj);

			nStates = 5;	// 何もしない状態にしておく
		}
	}

	// 発射の初期化処理
	private void InitCatapult()
	{
		// クリアしたステージに対応する敵オブジェクトを射出する敵のリストにセット
		int nSuffix;	// 敵配列, ボス配列の添え字

		// 雑魚敵をセット
		for (int i = 0; i < EnemyIndex.GetLength(1); i++)
		{
			nSuffix = EnemyIndex[nClearStage, i];	// 格納する敵の添え字を取得

			// 格納すべき敵がいなくなったら抜ける
			if (nSuffix == -1)
				break;

			CatapultList.Add(EnemyArray[nSuffix]);		// 雑魚敵を射出リストにセット
		}

		// ボスをセット
		for (int i = 0; i < BossIndex.GetLength(1); i++)
		{
			nSuffix = BossIndex[nClearStage, i];	// 格納する敵の添字を取得

			// 格納すべき敵がいなくなったら抜ける
			if (nSuffix == -1)
				break;

			// ボスを射出リストにセット
			CatapultBossList.Add(BossArray[nSuffix]);
		}

		// 打ち出す雑魚敵がいるかどうかで場合わけ
		if (CatapultList.Count == 0)
			nStates = 3;		// 打ち出す雑魚敵がいないので, いきなりボスへ
		else
			nStates++;			// 打ち出す雑魚敵がいるので, 次へ
	}

	// 雑魚敵発射
	private void FireEnemy()
	{
		fTime += 1.0f / 30.0f;
		if (fTime >= fInjectionInterval)
		{// 敵射出
			GameObject Obj;			// インスタンス化したオブジェクトのスクリプトの関数を実行するのに使う
			Vector2 Speed;			// 敵の移動速度
			Quaternion quaterniaon;	// 敵の初期角度
			float fAddAngle;		// 敵の1秒あたりの回転角度


			// 移動速度を計算
			// Xを設定
			// 方向配列を更新
			nSameDirection[0] = nSameDirection[1];
			nSameDirection[1] = nSameDirection[2];

			Speed.x = Random.Range(EnemyMinSpeed.x, EnemyMaxSpeed.x);
			if (Random.Range(0, 2) == 0)
			{// マイナス方向
				// 連続同じ方向の判定
				if (!(nSameDirection[0] == 0 && nSameDirection[1] == 0))
				{// 3回連続左方向でなければ, そのまま
					Speed.x = -Speed.x;		// 移動方向は左で
					nSameDirection[2] = 0;	// 方向配列に0(左)をセット
				}
				else
				{// 3回連続左方向なので, 方向を変える
					// マイナス1倍しないので向きは右のまま
					nSameDirection[2] = 1;	// 方向配列に1(右)をセット
				}
			}
			else
			{// プラス方向
				// 連続同じ方向の判定
				if (!(nSameDirection[0] == 1 && nSameDirection[1] == 1))
				{// 3回連続右方向でなければ, そのまま
					// マイナス1倍しないので向きは右のまま
					nSameDirection[2] = 1;	// 方向配列に1(右)をセット
				}
				else
				{// 3回連続右方向なので, 方向を変える
					Speed.x = -Speed.x;		// 移動方向は左で
					nSameDirection[2] = 0;	// 方向配列に0(左)をセット
				}
			}

			// Yを設定
			Speed.y = Random.Range(EnemyMinSpeed.y, EnemyMaxSpeed.y);

			// 敵の初期角度を計算
			quaterniaon = Quaternion.Euler(0.0f, 0.0f, Random.Range(0, 360));

			// 1秒あたりの回転角度を計算
			fAddAngle = Random.Range(EnemyMinAngle, EnemyMaxAngle);

			// オブジェクト化
			Obj = Instantiate(CatapultList[nInjectionNum],
							   transform.position,
							   quaterniaon) as GameObject;
			// 敵の移動速度などを設定
			Obj.GetComponent<ResultEnemy>().SetSpeed(Speed, EnemyGravity, fAddAngle);

			// もし打ち出した敵に「ボススクリプト」があれば, 無効にしていおく
			if (Obj.GetComponent<ResultBoss>())
			{
				Obj.GetComponent<ResultBoss>().enabled = false;
			}

			fTime = 0.0f;			// タイマー初期化
			nInjectionNum++;		// 射出した敵の数プラス

			// 敵の打ち出し音を鳴らす
			nChannel++;	// チャンネル変更
			if (nChannel == 5)
				nChannel = 1;
			Sound.PlaySe("SE_Fly", nChannel);

			if (nInjectionNum == CatapultList.Count)
			{// 全ての雑魚敵を打ち出した
				fTime = 0.0f;		// タイマー初期化

				// ステータス変化
				// 打ち出すボスがいるかどうかで場合わけ
				if (CatapultBossList.Count != 0)
					nStates++;			// 普通に次へ
				else
					nStates = 4;		// 打ち出すボスがいないので, ボス発射後の待ち時間へ
			}
		}
	}

	// ボス発射までの待ち時間
	private void WaitFireBoss()
	{
		fTime += 1.0f / 30.0f;
		if (fTime >= fBossWaitTime)
		{
			fTime = fInjectionBossInterval;	// 次の1ループ目で1体目は即発射
			nStates++;						// ステータス変化
		}
	}

	// ボス発射
	private void FireBoss()
	{
		fTime += 1.0f / 30.0f;
		if (fTime >= fInjectionBossInterval)
		{// ボス発射
			GameObject Obj;			// インスタンス化したオブジェクトのスクリプトの関数を実行するのに使う

			Obj = Instantiate(CatapultBossList[nInjectionBossNum],
							  transform.position,
							  Quaternion.identity
							  ) as GameObject;
			// ボスの移動速度などを設定
			// ステージ4のボスだけ, 横方向のスピードを与える
			if (nClearStage == 3)
			{
				if (nInjectionBossNum == 0)
					BossStartSpeed.x = BossSpeedX4;
				if (nInjectionBossNum == 1)
					BossStartSpeed.x = 0.0f;
				if (nInjectionBossNum == 2)
					BossStartSpeed.x = -BossSpeedX4;
			}
			Obj.GetComponent<ResultBoss>().SetSpeed(BossStartSpeed,		// Y方向の初速度
													BossGravity,		// 下方向の加速度
													BossStartScale,		// 初期拡大率
													BossFinScale,		// 爆発時の拡大率
													BossBombTime);		// 爆発するまでの時間

			fTime = 0.0f;			// タイマー初期化
			nInjectionBossNum++;	// 射出したボスの数プラス

			// 敵の打ち出し音を鳴らす
			nChannel++;	// チャンネル変更
			if (nChannel == 5)
				nChannel = 1;
			Sound.PlaySe("SE_Fly", nChannel);

			if (nInjectionBossNum == CatapultBossList.Count)
			{// 全てのボスを打ち出した
				fTime = 0.0f;		// タイマー初期化
				nStates++;			// ステータス変化
			}
		}
	}

	// はむち起動までの待ち時間
	private void WaitHamuti()
	{
		fTime += 1.0f / 30.0f;
		if (fTime >= fFinBossWaitTime)
		{
			// はむち起動
			GameObject.Find("Hamuti").GetComponent<ResultHamuti>().StartHamuti();

			fTime = 0.0f;		// タイマー初期化
			nStates++;			// ステータス変化
		}
	}
}
