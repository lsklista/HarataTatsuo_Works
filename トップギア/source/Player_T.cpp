//////////////////////////////////////////////
//ファイル名　：Player.cpp
//制作者　　　：原田達夫
//
//概要　　　　：プレイヤーのcppファイル
//////////////////////////////////////////////



//====================インクルード部
#include "CScreen.h"
#include "Buffer_T.h"
#include "Enemy_T.h"
#include "Player_T.h"
#include "Main_T.h"
#include "Sound_T.h"




//====================マクロ定義
#define MY_POS_X_T			   (  0.0f)		//プレイヤーの初期位置のＸ座標
#define MY_POS_Y_T			   ( 30.0f)		//プレイヤーの初期位置のＹ座標

#define LIMIT_LEFT_T			   (  0.0f)		//プレイヤーが移動できる右方向の移動限界
#define LIMIT_RIGHT_T			   (176.0f)		//プレイヤーが移動できる左方向の移動限界
#define LIMIT_UP_T			   (  6.0f)		//プレイヤーが移動できる上方向の移動限界	6
#define LIMIT_BOTTOM_T		   ( 34.0f)		//プレイヤーが移動できる下方向の移動限界


#define PLAYER_LIFE_T			   (     3)		//プレイヤーのＨＰ（何回まであたっていいか）	※これを変えるときは、初期化の数をかえておくこと
#define NO_HIT_INTERVAL_T		   (  1300)		//敵に当たった後の、無敵時間


#define MOVE_SIZE_T			   (  2.0f)		//ダッシュしてない時のデフォルトの移動量
#define SPEEDUP_SIZE_T		   ( 0.07f)		//ダッシュによる移動量の加速量	0.05f
#define SPEEDDOWN_SIZE_T		   ( 0.10f)		//ダッシュしてない時による加速量の減速量
#define LIMIT_SPEEDUP_T		   (17.00f)		//加速量の限界値
#define HIGHFRICTION_SIZE_T	   (0.015f)		//移動量が大きいときの摩擦係数
#define SLOWFRICTION_SIZE_T	   (0.060f)		//移動量が小さいときの摩擦係数

#define LIMIT_ACCELERATOR_T	   ( 30.0f)		//加速床を踏んだ時の速度の限界値
#define ACCELE_SPEEDDOWN_SIZE_T  ( 0.20f)		//加速床を踏んで、限界速度を超えている状態のときの減速量

#define MOVE_HITSIZE_T		   ( 0.20f)		//車に当たった時になってしまう速度
#define HEAL_SPEED_T			   ( 0.05f)		//車に当たって遅くなった後の、徐々に元の速さにもどっていく量

#define DRAW_INTERVAL_T		   (   100)		//車に当たった時の点滅する間隔


#define MILEAGE_FRICTION_T	   ( 0.18f)		//走行距離にかける係数（そのままの値を足したら大きくなりすぎるので）




//キャラのドット絵関連のマクロ定義
#define PLAYER_WIDTH_T		   (12)//(全角)
#define PLAYER_HEIGHT_T		   (12)

#define SMOKE_WIDTH_T		   (12)//(半角)
#define SMOKE_HEIGHT_T		   ( 6)





struct THeart_T
{
	int nPosX;
	int nPosY;
	char szHeart[100];
};




//====================プロトタイプ宣言
bool CheckCollisionEnemy_T(void);
bool CheckCollisionAccele_T(void);




//====================グローバル宣言
TPlayer_T g_Player_T;				//プレイヤーの構造体の宣言
float g_fSpeedUp_T;				//ダッシュによるスピードアップ
THeart_T Heart_T[PLAYER_LIFE_T];		//ハート（プレイヤーのＨＰ表示）の構造体の宣言
bool g_bAcceleFlg_T;				//加速床を踏んで、限界速度を超えた状態にあるか（この状態の時は速度の限界の補正は受けないが、ゆっくり減速してく）
bool g_bCollisionEnemyFlg_T;		//敵に当たったかどうかのフラグ
char g_szSmoke_1_T[73];			//加速した時の煙その１（少し加速したらでる、ちょっとした煙）
char g_szSmoke_2_T[73];			//加速した時の煙その２（まぁまぁ加速したらでる、そこそこの煙）
char g_szSmoke_3_T[73];			//加速した時の煙その３（ほぼＭＡＸまで加速したら出る、火花）
bool g_bShowHitPlayer_T;			//敵に当たったプレイヤーを点滅させるための、描画するかしないかのフラグ
int  g_nHitTime_T;				//プレーヤーが敵に当たった時間
float g_fMileage_T;				//プレイヤーが走った距離（スコアに関係してくる）

char g_szNumber_T[10][41];

//char g_szNumber_0_T[41];			//数字の０
//char g_szNumber_1_T[41];			//数字の１
//char g_szNumber_2_T[41];			//数字の２
//char g_szNumber_3_T[41];			//数字の３
//char g_szNumber_4_T[41];			//数字の４
//char g_szNumber_5_T[41];			//数字の５
//char g_szNumber_6_T[41];			//数字の６
//char g_szNumber_7_T[41];			//数字の７
//char g_szNumber_8_T[41];			//数字の８
//char g_szNumber_9_T[41];			//数字の９
char g_szMeter_T[37];				//メートルのm

int g_nMileage_T[4];				//走行距離格納用の配列




void InitPlayer_T(void)
{
	int nCntPlayer;
	FILE *pFile;
	
	//-----プレイヤーの初期化
	g_Player_T.fPosX      = MY_POS_X_T;
	g_Player_T.fPosY      = MY_POS_Y_T;
	g_Player_T.fOldPosX   = MY_POS_X_T;
	g_Player_T.fOldPosY   = MY_POS_Y_T;
	g_Player_T.fMoveX     = 0.0f;
	g_Player_T.fMoveY     = 0.0f;
	g_Player_T.nHp        = PLAYER_LIFE_T;
	g_Player_T.bNoHitTime = false;
	
	pFile = fopen("Junior_2_1.txt","r");
	fscanf(pFile,"%s",g_Player_T.szPlayer_1);
	fclose(pFile);
	pFile = fopen("Junior_2_2.txt","r");
	fscanf(pFile,"%s",g_Player_T.szPlayer_2);
	fclose(pFile);
	pFile = fopen("Junior_2_3.txt","r");
	fscanf(pFile,"%s",g_Player_T.szPlayer_3);
	fclose(pFile);
	pFile = fopen("Junior_2_4.txt","r");
	fscanf(pFile,"%s",g_Player_T.szPlayer_4);
	fclose(pFile);


	
	Heart_T[0].nPosX = 1;
	Heart_T[0].nPosY = 1;
	Heart_T[1].nPosX = 16;
	Heart_T[1].nPosY = 1;
	Heart_T[2].nPosX = 31;
	Heart_T[2].nPosY = 1;
	
	for(nCntPlayer = 0 ; nCntPlayer < PLAYER_LIFE_T ; nCntPlayer ++)
	{
		pFile = fopen("Heart.txt","r");
		fscanf(pFile,"%s",Heart_T[nCntPlayer].szHeart);
		fclose(pFile);
	}


	//-----加速した時に出る煙の初期化
	pFile = fopen("kemuri_1.txt","r");
	fscanf(pFile,"%s",g_szSmoke_1_T);
	fclose(pFile);

	pFile = fopen("kemuri_2.txt","r");
	fscanf(pFile,"%s",g_szSmoke_2_T);
	fclose(pFile);

	pFile = fopen("kemuri_3.txt","r");
	fscanf(pFile,"%s",g_szSmoke_3_T);
	fclose(pFile);


	//数字の初期化
	pFile = fopen("number_0.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[0]);
	fclose(pFile);
	pFile = fopen("number_1.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[1]);
	fclose(pFile);
	pFile = fopen("number_2.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[2]);
	fclose(pFile);
	pFile = fopen("number_3.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[3]);
	fclose(pFile);
	pFile = fopen("number_4.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[4]);
	fclose(pFile);
	pFile = fopen("number_5.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[5]);
	fclose(pFile);
	pFile = fopen("number_6.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[6]);
	fclose(pFile);
	pFile = fopen("number_7.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[7]);
	fclose(pFile);
	pFile = fopen("number_8.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[8]);
	fclose(pFile);
	pFile = fopen("number_9.txt","r");
	fscanf(pFile,"%s",g_szNumber_T[9]);
	fclose(pFile);


	//-----メートル(m)の初期化
	pFile = fopen("m.txt","r");
	fscanf(pFile,"%s",g_szMeter_T);
	fclose(pFile);



	g_fMileage_T = 0.0f;
}

void UpdatePlayer_T(void)
{
	static int nHitTime = timeGetTime();	//プレイヤーが敵に当たった時間
	int nCurrentTime;						//今の時間
	static int nExecTime;					//描画フラグの実行時間
	

	static int nCntHit;


	//=====現在座標を退避=====
	g_Player_T.fOldPosX = g_Player_T.fPosX;
	g_Player_T.fOldPosY =	g_Player_T.fPosY;
	

	//=====移動量を初期化=====
	g_Player_T.fMoveX =0.0f;
	g_Player_T.fMoveY =0.0f;


	//=====キー入力=====
	if(INP(PK_RIGHT) || GPRIGHT() != 0)		//RIGHTキーが押されたら
	{
		g_Player_T.fMoveX += MOVE_SIZE_T;
	}

	if(INP(PK_LEFT) || GPLEFT() != 0)		//LEFTキーが押されたら
	{
		g_Player_T.fMoveX -= MOVE_SIZE_T;
	}
	if(INP(PK_UP) || GPUP() != 0)			//UPキーが押されたら
	{
		g_Player_T.fMoveY -= MOVE_SIZE_T;
	}
	if(INP(PK_DOWN) || GPDOWN() != 0)		//DOWNキーが押されたら
	{
		g_Player_T.fMoveY += MOVE_SIZE_T;
	}


	//===== ダッシュ =====
	if(INP(PK_SP) || GPBTN3() != 0)
		g_fSpeedUp_T += SPEEDUP_SIZE_T;
	else
		g_fSpeedUp_T -= SPEEDDOWN_SIZE_T;


	//===== ブレーキ =====
	if(INP(PK_SHIFT) || GPBTN1() != 0)
	{
		if(g_fSpeedUp_T > 10.0f)
			g_fSpeedUp_T -= (g_fSpeedUp_T * HIGHFRICTION_SIZE_T);		//現在のスピードに摩擦係数をかけた値が実際に減速されるようにする
		else
			g_fSpeedUp_T -= (g_fSpeedUp_T * SLOWFRICTION_SIZE_T);


	}


	//===== 加速量補正 =====
	if(g_fSpeedUp_T < 0)												//加速が０を下回るなら、補正
		g_fSpeedUp_T = 0.0f;
	if(g_fSpeedUp_T > LIMIT_SPEEDUP_T && !g_bAcceleFlg_T)					//加速床を踏んでない状態で、限界速度を超えようとしたら、補正
		g_fSpeedUp_T = LIMIT_SPEEDUP_T;
	if(g_bAcceleFlg_T)												//加速床を踏んで、加速状態にあるときの減速
		g_fSpeedUp_T -= ACCELE_SPEEDDOWN_SIZE_T;
	if(g_bAcceleFlg_T && g_fSpeedUp_T <= (LIMIT_SPEEDUP_T + MOVE_SIZE_T))	//加速床を踏んだ加速状態で、普通の限界速度より遅くなったら加速フラグをおろす
		g_bAcceleFlg_T = false;
	if(g_bCollisionEnemyFlg_T)										//敵に当たった状態のとき、徐々に元の速さに戻す。
		g_fSpeedUp_T += HEAL_SPEED_T;
	if(g_bCollisionEnemyFlg_T && (g_fSpeedUp_T >= MOVE_SIZE_T))		//敵に当たったフラグが立っていて、元の速さに戻ったら、フラグをさげる
		g_bCollisionEnemyFlg_T = false;

	//===== 座標更新 =====
	g_Player_T.fPosX += g_Player_T.fMoveX;
	g_Player_T.fPosY += g_Player_T.fMoveY;


	//===== 座標補正 =====
	if( g_Player_T.fPosX < LIMIT_LEFT_T)
		g_Player_T.fPosX = LIMIT_LEFT_T;

	if( g_Player_T.fPosX > LIMIT_RIGHT_T)
		g_Player_T.fPosX = LIMIT_RIGHT_T;

	if( g_Player_T.fPosY < LIMIT_UP_T)
		g_Player_T.fPosY = LIMIT_UP_T;

	if( g_Player_T.fPosY > LIMIT_BOTTOM_T)
		g_Player_T.fPosY = LIMIT_BOTTOM_T;



	//-----敵とのあたり判定
	nCurrentTime = timeGetTime();		//現在時間を取得

	if( !g_Player_T.bNoHitTime && CheckCollisionEnemy_T() )		//無敵時間ではない、かつ、敵と当たったときの処理
	{
		nHitTime = timeGetTime();		//プレイヤーが敵に当たった時の時間を取得
		nExecTime = timeGetTime();		//プレイヤーが敵に当たった時の時間を取得
		g_Player_T.bNoHitTime = true;		//無敵フラグを立てる
		g_bShowHitPlayer_T = true;		//点滅フラグを立てる

		g_Player_T.nHp --;				//プレイヤーのＨＰ減少
		StartSound_T(HIT_T, NOREPEAT_T);

		if(g_Player_T.nHp == 0)
			SetState_T(STATE_RESULT_T);		//ＨＰが０になったら、ゲーム終了

		g_Player_T.fMoveX = MOVE_HITSIZE_T;	//速度を遅くする
		g_fSpeedUp_T = 0.0f;				//加速をなしにする。
		g_bCollisionEnemyFlg_T = true;	//「敵に当たった」フラグをたてる


	}
	
	if( g_Player_T.bNoHitTime && nCurrentTime - nHitTime >= NO_HIT_INTERVAL_T)	//無敵フラグが立っていて、無敵時間を過ぎていたら
		g_Player_T.bNoHitTime = false;										//無敵フラグを下げる

	if(g_Player_T.bNoHitTime && (nCurrentTime - nExecTime >= DRAW_INTERVAL_T))	//無敵フラグが立っていて、点滅間隔をすぎたら
	{																		//描画フラグの切り替え
		nExecTime = nCurrentTime;
		if(g_bShowHitPlayer_T)
			g_bShowHitPlayer_T = false;
		else
			g_bShowHitPlayer_T = true;
	}
	if(!g_Player_T.bNoHitTime && g_bShowHitPlayer_T)							//無敵フラグが下がっていて、キャラ描画フラグが下がっていたら
		g_bShowHitPlayer_T = false;											//キャラ描画フラグをたてる



	//加速床とのあたり判定
	if(CheckCollisionAccele_T())
	{
		g_bAcceleFlg_T = true;	//加速状態にする
		g_fSpeedUp_T = 30.0f;
		StartSound_T(SPEEDUP_T,NOREPEAT_T);
	}

	//-----走行距離の計算
	g_fMileage_T += (g_fSpeedUp_T + MOVE_SIZE_T) * MILEAGE_FRICTION_T;		//走行距離の変数に今のスピードを足していく

	//配列に値を格納
	g_nMileage_T[0] = ((int)g_fMileage_T / 10000);						//千の位
	g_nMileage_T[1] = ((int)g_fMileage_T % 10000 / 1000);				//百の位
	g_nMileage_T[2] = ((int)g_fMileage_T % 10000 % 1000 / 100);			//十の位
	g_nMileage_T[3] = ((int)g_fMileage_T % 10000 % 1000 % 100 / 10);	//一の位


}





void DrawPlayer_T(void)
{
	int nX;
	int nY;
	int nCntPlayer;
	int nMileage_PosX = 140;		//走行距離のＸ座標						←新しく追加
	static int nAnimeFlg = 1;		//どのドット絵をだすかのフラグ
	static float fAnimeCnt = 10.0f;
	
	if(!g_bShowHitPlayer_T)
	{
	
		//-----アニメフラグの設定（描画するドット絵を決定
		fAnimeCnt -= (MOVE_SIZE_T + g_fSpeedUp_T);
		if(fAnimeCnt < 0)
		{
			nAnimeFlg ++;
			if(nAnimeFlg == 5)
				nAnimeFlg = 1;

			if(MOVE_SIZE_T + g_fSpeedUp_T <= 5.0f)
				fAnimeCnt = 20.0f;
			else if(MOVE_SIZE_T + g_fSpeedUp_T > 5.0f && MOVE_SIZE_T + g_fSpeedUp_T <= 10.0f)
				fAnimeCnt = 25.0f;
			else if(MOVE_SIZE_T + g_fSpeedUp_T > 10.0f && MOVE_SIZE_T + g_fSpeedUp_T <= 15.0f)
				fAnimeCnt = 30.0f;
			else
				fAnimeCnt = 40.0f;
		}


		//-----プレイヤーの描画
		for(nY = 0 ; nY < PLAYER_HEIGHT_T ; nY ++)
		{
			switch (nAnimeFlg)
			{
			case 1:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_1[nX + nY * 24] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_1[nX + nY * 24]);				
				}
				break;

			
			case 2:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_2[nX + nY * 24] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_2[nX + nY * 24]);				
				}
				break;

			
			case 3:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_3[nX + nY * 24] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_3[nX + nY * 24]);				
				}
				break;

			
			case 4:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_4[nX + nY * 24] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_4[nX + nY * 24]);				
				}
				break;


			}




		
		}

	

		//-----加速した時の煙・火の描画・・・その１
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 5.0f && MOVE_SIZE_T + g_fSpeedUp_T < 10.0f)	//そこそこの加速の時の煙
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_1_T[nX + nY * SMOKE_WIDTH_T] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosX + nX - 12) < 0)
						continue;

					if(((int)g_Player_T.fPosY + nY + 6) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX - 12),((int)g_Player_T.fPosY + nY + 6),g_szSmoke_1_T[nX + nY * SMOKE_WIDTH_T]);				
				}
			}
		}

		//-----加速した時の煙・火の描画・・・その２
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 10.0f && MOVE_SIZE_T + g_fSpeedUp_T < 15.0f)	//まぁまぁの加速の時の煙
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_2_T[nX + nY * SMOKE_WIDTH_T] == '^')			//透明なら何も描画しない
						continue;
				
					if(((int)g_Player_T.fPosX + nX - 12) < 0)
						continue;

					if(((int)g_Player_T.fPosY + nY + 6) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX - 12),((int)g_Player_T.fPosY + nY + 6),g_szSmoke_2_T[nX + nY * SMOKE_WIDTH_T]);
				}
			}
		}

		//-----加速した時の煙・火の描画・・・その３
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 15.0f)										//かなりの加速の時の煙
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_3_T[nX + nY * SMOKE_WIDTH_T] == '^')			//透明なら何も描画しない
						continue;

					if(((int)g_Player_T.fPosX + nX - 12) < 0)
						continue;

					if(((int)g_Player_T.fPosY + nY + 6) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX - 12),((int)g_Player_T.fPosY + nY + 6),g_szSmoke_3_T[nX + nY * SMOKE_WIDTH_T]);				
				}
			}
		}

		
	}

	
	//-----ハートマークの描画
	for(nCntPlayer = 0 ; nCntPlayer < g_Player_T.nHp ; nCntPlayer ++)
	{
		for(nY = 0 ; nY < 7 ; nY ++)
		{
			for(nX = 0 ; nX < 14 ; nX ++)
			{
				if(Heart_T[nCntPlayer].szHeart[nX + nY * 14] == '^')
					continue;

				SetNextData_T(Heart_T[nCntPlayer].nPosX + nX , Heart_T[nCntPlayer].nPosY + nY, Heart_T[nCntPlayer].szHeart[nX + nY * 14] );
			}
		}
	}



	//-----↓この下２つのループ新しく追加

	//-----走行距離の描画（とりあえず、小数点以下切り捨て４ケタ表示で）
	for(nCntPlayer = 0 ; nCntPlayer < MAX_FIGURE_T ; nCntPlayer ++)
	{
		for(nY = 0 ; nY < NUMBER_HEIGHT_T ; nY ++)
		{
			for(nX = 0 ; nX < NUMBER_WIDTH_T ; nX ++)
			{
				if(g_szNumber_T[g_nMileage_T[nCntPlayer]][nX + nY * NUMBER_WIDTH_T] == '^')
					continue;

				SetNextData_T(nMileage_PosX + nX, 2 + nY, g_szNumber_T[g_nMileage_T[nCntPlayer]][nX + nY * NUMBER_WIDTH_T]);
			}
		}

		nMileage_PosX += 10;
	}

	//メートルのmの描画
	for(nY = 0 ; nY < METER_HEIGHT_T ; nY ++)
	{
		for(nX = 0 ; nX < METER_WIDTH_T ; nX ++)
		{
			if(g_szMeter_T[nX + nY * METER_WIDTH_T] == '^')
				continue;

			SetNextData_T(nMileage_PosX + nX, 4 + nY, g_szMeter_T[nX + nY * METER_WIDTH_T]);
		}
	}


}






bool CheckCollisionEnemy_T()
{
	int nCntEnemy;
	float fDistance;
	float fPlayerCenter_Up_X, fPlayerCenter_Up_Y;			//プレイヤーの上半身のX,Yそれぞれの中心座標
	float fPlayerCenter_Front_X, fPlayerCenter_Front_Y;		//プレイヤーの自転車の前輪のX,Yそれぞれの中心座標
	float fPlayerCenter_Back_X, fPlayerCenter_Back_Y;		//プレイヤーの自転車の後輪のX,Yそれぞれの中心座標
	float fEnemyCenter_X , fEnemyCenter_Y ;					//敵（車）のX,Yそれぞれの中心座標

	TEnemy_T *pEnemy = GetEnemyData_T();
	
	fPlayerCenter_Up_X     = g_Player_T.fPosX + 12;			//プレイヤーの上半身      のＸの中心座標の格納
	fPlayerCenter_Up_Y     = g_Player_T.fPosY + 3;			//プレイヤーの上半身      のＹの中心座標の格納
	fPlayerCenter_Front_X  = g_Player_T.fPosX + 22;			//プレイヤーの自転車の前輪のＸの中心座標の格納
	fPlayerCenter_Front_Y  = g_Player_T.fPosY + 9;			//プレイヤーの自転車の前輪のＹの中心座標の格納
	fPlayerCenter_Back_X   = g_Player_T.fPosX + 3;			//プレイヤーの自転車の後輪のＸの中心座標の格納
	fPlayerCenter_Back_Y   = g_Player_T.fPosY + 9;			//プレイヤーの自転車の後輪のＹの中心座標の格納


	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++, pEnemy ++)
	{
		//未使用の敵は判定しない
		if(!pEnemy->bUse)
			continue;

		fEnemyCenter_X = pEnemy->fPosX + (ENEMY_CAR_WIDTH_T  / 2);	//敵（車）のX軸の中心座標の格納
		fEnemyCenter_Y = pEnemy->fPosY + 6;							//敵（車）のY軸の中心座標の格納


		//前輪
		fDistance = (fPlayerCenter_Front_X - fEnemyCenter_X) * 
					(fPlayerCenter_Front_X - fEnemyCenter_X) +
					(fPlayerCenter_Front_Y - fEnemyCenter_Y) *
					(fPlayerCenter_Front_Y - fEnemyCenter_Y) * 4;

		if(fDistance < 150.0f)
			return true;


		//後輪
		fDistance = (fPlayerCenter_Back_X - fEnemyCenter_X) * 
					(fPlayerCenter_Back_X - fEnemyCenter_X) +
					(fPlayerCenter_Back_Y - fEnemyCenter_Y) *
					(fPlayerCenter_Back_Y - fEnemyCenter_Y) * 4;

		if(fDistance < 150.0f)
			return true;


	}
	
		//当たらなかった時の処理
		return false;
}


bool CheckCollisionAccele_T(void)
{
	int nCntAccele;
	float fDistance;
	float fPlayerCenter_Front_X, fPlayerCenter_Front_Y;		//プレイヤーの自転車の前輪のX,Yそれぞれの中心座標
	float fPlayerCenter_Back_X, fPlayerCenter_Back_Y;		//プレイヤーの自転車の後輪のX,Yそれぞれの中心座標
	float fAcceleCenter_X , fAcceleCenter_Y ;				//オイルのX,Yそれぞれの中心座標

	TAccelerator_T *pAccele = GetAcceleData_T();

	fPlayerCenter_Front_X  = g_Player_T.fPosX + 22;			//プレイヤーの自転車の前輪のＸの中心座標の格納
	fPlayerCenter_Front_Y  = g_Player_T.fPosY + 9;			//プレイヤーの自転車の前輪のＹの中心座標の格納
	fPlayerCenter_Back_X   = g_Player_T.fPosX + 3;			//プレイヤーの自転車の後輪のＸの中心座標の格納
	fPlayerCenter_Back_Y   = g_Player_T.fPosY + 9;			//プレイヤーの自転車の後輪のＹの中心座標の格納

	for(nCntAccele = 0 ; nCntAccele < MAX_ACCELE_T ; nCntAccele ++, pAccele ++)
	{
		//未使用の敵は判定しない
		if(!pAccele->bUse)
			continue;

		fAcceleCenter_X = pAccele->fPosX + (ACCELE_WIDTH_T  / 2);		//オイルのX軸の中心座標の格納
		fAcceleCenter_Y = pAccele->fPosY + (ACCELE_HEIGHT_T / 2);		//オイルのY軸の中心座標の格納


		//=====敵とのあたり判定
		//前輪
		fDistance = (fPlayerCenter_Front_X - fAcceleCenter_X) * 
					(fPlayerCenter_Front_X - fAcceleCenter_X) +
					(fPlayerCenter_Front_Y - fAcceleCenter_Y) *
					(fPlayerCenter_Front_Y - fAcceleCenter_Y) * 4;

		if(fDistance < 100.0f)
			return true;


		//後輪
		fDistance = (fPlayerCenter_Back_X - fAcceleCenter_X) * 
					(fPlayerCenter_Back_X - fAcceleCenter_X) +
					(fPlayerCenter_Back_Y - fAcceleCenter_Y) *
					(fPlayerCenter_Back_Y - fAcceleCenter_Y) * 4;

		if(fDistance < 100.0f)
			return true;

	}

	//当たらなかった時の戻り値
	return false;

}








TPlayer_T *GetPlayerData_T(void)
{
	return &g_Player_T;
}


float GetPlayerSpeed_T(void)
{
	return (MOVE_SIZE_T + g_fSpeedUp_T);
}


bool GetCollisionFlg_T(void)
{
	return g_bCollisionEnemyFlg_T;
}


float Getg_fMileageData_T(void)				//←新しく追加
{
	return g_fMileage_T;
}

char *Getg_szMeterData_T(void)
{
	return g_szMeter_T;
}

char *Getg_szNumber(void)
{
	return *g_szNumber_T;
}