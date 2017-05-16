//////////////////////////////////////////////
//ＨＥＷ作品
//納期・・・　２月２８日まで
//仮納期・・　２月１９日まで
//
//プログラム名：ＨＥＷＧＡＭＥ
//ファイル名　：main.cpp
//制作者　　　：原田達夫
//
//概要　　　　：ゲームの流れ・制御に関するcppファイル
//
//////////////////////////////////////////////

//====================インクルード部
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CScreen.h"
#include "Player_T.h"		//プレイヤー
#include "Enemy_T.h"		//敵
#include "Buffer_T.h"		//バッファー
#include "Field_T.h"		//地形
#include "Main_T.h"			//メイン
#include "Title_T.h"		//タイトル
#include "Result_T.h"		//リザルト
#include "Rank_T.h"			//ランク
#include "Sound_T.h"		//音


//====================マクロ定義
#define DIPS_INTERVAL_T (1000)
#define DIPS_POS_X_T       (1)
#define DIPS_POS_Y_T		 (1)

const int RATE = 1000 / 60;


//====================プロトタイプ宣言
void Continue_T(void);


//====================グローバル宣言
unsigned int nFrame_T;
state_T g_eGameState_T;
bool bGameContinue_T = true;	//ゲームをもう一回やるかどうかのフラグ
bool bGameEnd_T;		//ゲームをもう一回やるかどうかのフラグ







//==============================================
//メイン関数
//関数名：main
//引数　：なし
//戻り値：なし
//-----概要-------------------------------------
//プログラムの流れ
//==============================================
void main(void)
{
	bGameEnd_T = false;
		InitBuffer_T();



	while(!bGameEnd_T)
	{
		//-----変数宣言-----
		int nExecTime;			//実行時刻
		int nDipsFPSTime;		//FPS値の表示時刻
		int nCurrentTime;		//現在の時刻
		int nFPS;				//デバッグ用のFPS値
		int nFrame_TCount;		//デバッグ用のFPS値のカウンター
		
		TPlayer_T PlayerData;



		//----- 初期化処理 -----
		nExecTime = nDipsFPSTime = timeGetTime();
		nFrame_TCount = 0;
		nFPS = 0;
		bGameContinue_T = true;
		g_eGameState_T = STATE_TITLE_T;
	

		InitTitle_T();
		InitField_T();
		InitPlayer_T();
		InitEnemy_T();
		InitResult_T();
		InitRank_T();
		InitSound_T();
	
		//----- 事前処理 -----
		timeBeginPeriod(1);			//分解能
		CUROFF();					//カーソル消去
		StartSound_T(BGM_T,REPEAT_T);



		//----- ゲームメインループ -----
		while(bGameContinue_T)
		{

		
			nCurrentTime = timeGetTime();		//今の時間をとる

			if(nCurrentTime - nDipsFPSTime >=DIPS_INTERVAL_T)
			{
				nDipsFPSTime = nCurrentTime;
				nFPS = nFrame_TCount;
				nFrame_TCount = 0;
			}

			if(nCurrentTime - nExecTime >= RATE)
			{
				//----- 更新処理 -----
				nExecTime = nCurrentTime;
				nFrame_TCount ++;
				nFrame_T ++;
				if(nFrame_T > 1900)		//敵とかを全部出して、少ししたら、敵をリセット
				{
					nFrame_T = 0;
					InitEnemy_T();
				}
				switch(g_eGameState_T)
				{
					//-----タイトル
					case STATE_TITLE_T:
						UpdateTitle_T();
						DrawTitle_T();
						DrawBuffer_T();
						nFrame_T = 0;
						break;
					
					//-----ゲーム
					case STATE_GAME_T:
						UpdatePlayer_T();
						UpdateField_T();
						UpdateEnemy_T();
						UpdateBuffer_T();
			
						//----- 描画処理 -----
						PlayerData = *GetPlayerData_T();		//プレイヤーの情報を取得（描画する順番に関係する）
						DrawBackField_T();					//道路の白線や奥のガードレール
						if(PlayerData.fPosY < 12)
						{
							DrawPlayer_T();
							DrawBackEnemy_T();
							DrawMiddleEnemy_T();
							DrawFrontEnemy_T();
						}
						else if(PlayerData.fPosY < 20)
						{
							DrawBackEnemy_T();
							DrawPlayer_T();
							DrawMiddleEnemy_T();
							DrawFrontEnemy_T();
						}
						else if(PlayerData.fPosY < 30)
						{
							DrawBackEnemy_T();
							DrawMiddleEnemy_T();
							DrawPlayer_T();
							DrawFrontEnemy_T();
						}
						else
						{
							DrawBackEnemy_T();
							DrawMiddleEnemy_T();
							DrawFrontEnemy_T();
							DrawPlayer_T();
						}
						DrawFrontField_T();			//手前のガードレール
						DrawBuffer_T();				//バッファの情報を画面に出す（ここで実際に描画）
						break;

					//-----リザルト
					case STATE_RESULT_T:		//プレイヤーのＨＰが０になったらリザルト
						UpdateResult_T();
						DrawResult_T();
						DrawBuffer_T();
						while(1)									//入力待ち
							if(INP(PK_ENTER) || GPBTN3() != 0)
							{
								INPCLEAR();
								break;
							}
						UpdateRank_T();
						DrawRank_T();
						DrawBuffer_T();
						Continue_T();
						break;
				}
			}
		}
		CloseSound_T();
	}
}


void Continue_T(void)
{
	
	LOCATE(88, 40);
	COLOR(WHITE,BLACK);
	printf("もう一度プレイしますか？");
	LOCATE(80, 42);
	printf("はい　　　　　　　　　　　　　　　いいえ");
	LOCATE(80,42);
	COLOR(WHITE, SKYBLUE);
	printf("はい");

	while(1)
	{
		if(INP(PK_LEFT) || GPLEFT() != 0)
		{
			LOCATE(80,42);
			COLOR(BLACK, SKYBLUE);
			printf("はい");

			LOCATE(114,42);
			COLOR(WHITE,BLACK);
			printf("いいえ");

			bGameEnd_T = false;
			

			INPCLEAR();
		}

		if(INP(PK_RIGHT) || GPRIGHT() != 0)
		{
			LOCATE(80,42);
			COLOR(WHITE, BLACK);
			printf("はい");

			LOCATE(114,42);
			COLOR(BLACK,SKYBLUE);
			printf("いいえ");

			bGameEnd_T = true;
			INPCLEAR();
		}


		if(INP(PK_ENTER) || GPBTN3() != 0)
		{
			INPCLEAR();
			break;
		}
	}
	COLOR(DARK,DARK);
	LOCATE(88, 39);
	printf("aaaaaaaaaaaaaaaaaaaaaaaa");
	LOCATE(80, 40);
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	LOCATE(80, 41);
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	LOCATE(80, 42);
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	LOCATE(80, 43);
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	


	
	bGameContinue_T = false; 

}




int GetFrameData_T(void)
{
	return nFrame_T;
}

void SetFrameData_T(int nLisetFrame)
{
	nFrame_T = nLisetFrame;
}


state_T GetState_T(void)
{
	return g_eGameState_T;
}


void SetState_T(state_T eState)
{
	g_eGameState_T = eState;
}

