//////////////////////////////////////////////
//ファイル名　：Enemy.cpp
//制作者　　　：原田達夫
//
//概要　　　　：敵のcppファイル
//////////////////////////////////////////////



//====================インクルード部
#include "CScreen.h"
#include "Buffer_T.h"
#include "Enemy_T.h"
#include "Player_T.h"
#include "Main_T.h"
#include "Field_T.h"


//====================マクロ定義
#define MOVE_SIZE_T_HIGH_T		   ( 0.80f)	//赤い車の移動量
#define MOVE_SIZE_T_MIDDLE_T	   ( 1.30f)	//黄色い車の移動量
#define MOVE_SIZE_T_SLOW_T		   ( 1.50f)	//緑の車の移動量


#define CAR_POS_UP_X_T		   (200.0f)	//車のライン上の初期位置のＸ座標
#define CAR_POS_UP_Y_T		   ( 14.0f)	//車のライン上の初期位置のＹ座標
#define CAR_POS_MIDDLE_X_T	   (200.0f)	//車のライン中の初期位置のＸ座標
#define CAR_POS_MIDDLE_Y_T	   ( 25.0f)	//車のライン中の初期位置のＹ座標
#define CAR_POS_BOTTOM_X_T	   (200.0f)	//車のライン下の初期位置のＸ座標
#define CAR_POS_BOTTOM_Y_T	   ( 36.0f)	//車のライン下の初期位置のＹ座標

#define OIL_POS_UP_X_T		   (200.0f)	//オイルのライン上の初期位置のＸ座標
#define OIL_POS_UP_Y_T		   ( 15.0f)	//オイルのライン上の初期位置のＹ座標
#define OIL_POS_MIDDLE_X_T	   (200.0f)	//オイルのライン中の初期位置のＸ座標
#define OIL_POS_MIDDLE_Y_T	   ( 27.0f)	//オイルのライン中の初期位置のＹ座標
#define OIL_POS_BOTTOM_X_T	   (200.0f)	//オイルのライン下の初期位置のＸ座標
#define OIL_POS_BOTTOM_Y_T	   ( 37.0f)	//オイルのライン下の初期位置のＹ座標

#define ACCELE_POS_UP_X_T		   (200.0f)	//加速床のライン上の初期位置のＸ座標
#define ACCELE_POS_UP_Y_T		   ( 15.0f)	//加速床のライン上の初期位置のＹ座標
#define ACCELE_POS_MIDDLE_X_T	   (200.0f)	//加速床のライン中の初期位置のＸ座標
#define ACCELE_POS_MIDDLE_Y_T	   ( 27.0f)	//加速床のライン中の初期位置のＹ座標
#define ACCELE_POS_BOTTOM_X_T	   (200.0f)	//加速床のライン下の初期位置のＸ座標
#define ACCELE_POS_BOTTOM_Y_T	   ( 37.0f)	//加速床のライン下の初期位置のＹ座標


//#define



//-----構造体宣言




//====================プロトタイプ宣言
void CreateEnemy_T(int);		//車を出現させる
void CreateOil_T(int);		//オイルを出現させる
void CreateAccele_T(int);		//加速床を出現させる




//====================グローバル宣言
TEnemy_T g_Car[MAX_ENEMY_T];			//車
TAccelerator_T   g_Accele[MAX_ACCELE_T];//加速床
int g_nEnemySpawnframe[MAX_ENEMY_T] = {
										100, 200, 400, 450, 550, 700, 800, 800, 850, 900,
										1050,1100,1200,1260,1380,1500,1600,1640, 1690,1700
								
								
								   };		//敵の出現フレーム数

int g_nEnemySpawnLine[MAX_ENEMY_T]  = {     
										0,   1,   2,   1,   0,   2,   1,   0,   2,   1,
										0,	 1,	  2,   1,   0,   2,   1,   0,   2,   1
										
								    };		//敵の出現ライン


//int g_nOilSpawnFrame_T[MAX_OIL_T] = {50, 120,180,250,320};	//オイルの出現フレーム数
//int g_nOilSpawnLine[MAX_OIL_T]  = {1, 2, 1, 0, 2};		//オイルの出現ライン

int g_nAcceleSpawnFrame_T[MAX_ACCELE_T] = {300,400, 600,880,1000,1100,1250,1330,1520,1600};	//加速床の出現フレーム数
int g_nAcceleSpawnLine[MAX_ACCELE_T]  = {1, 2, 1, 0, 2, 1, 0, 0, 2, 1};			//加速床の出現ライン
int nCurrentFrame_T;	//今のフレーム数



void CreateEnemy_T(int nLine)
{
	int nCntEnemy;
	float fPosX;
	float fPosY;

	switch(nLine)
	{
		case 0:
			fPosX = CAR_POS_UP_X_T;
			fPosY = CAR_POS_UP_Y_T;
			break;

		case 1:
			fPosX = CAR_POS_MIDDLE_X_T;
			fPosY = CAR_POS_MIDDLE_Y_T;
			break;

		case 2:
			fPosX = CAR_POS_BOTTOM_X_T;
			fPosY = CAR_POS_BOTTOM_Y_T;
			break;
	}


	for( nCntEnemy = 0; nCntEnemy < MAX_ENEMY_T; nCntEnemy ++)
	{
		if(g_Car[nCntEnemy].bUse)
			continue;		//使用したら次のループへ
		
		//未使用の敵が見つかった場合
		g_Car[nCntEnemy].fPosX      = fPosX;
		g_Car[nCntEnemy].fPosY      = fPosY;
		g_Car[nCntEnemy].fOldPosX   = fPosX;
		g_Car[nCntEnemy].fOldPosY   = fPosY;
		g_Car[nCntEnemy].fMoveX     = 0.0f;
		g_Car[nCntEnemy].fMoveY     = 0.0f;
		g_Car[nCntEnemy].nLine      = nLine;
		g_Car[nCntEnemy].bUse       = true; 
		break;
		
	}	
}





void CreateAccele_T(int nLine)
{
	int nCntAccele;
	float fPosX;
	float fPosY;

	switch(nLine)
	{
		case 0:
			fPosX = ACCELE_POS_UP_X_T;
			fPosY = ACCELE_POS_UP_Y_T;
			break;

		case 1:
			fPosX = ACCELE_POS_MIDDLE_X_T;
			fPosY = ACCELE_POS_MIDDLE_Y_T;
			break;

		case 2:
			fPosX = ACCELE_POS_BOTTOM_X_T;
			fPosY = ACCELE_POS_BOTTOM_Y_T;
			break;
	}


	for( nCntAccele = 0; nCntAccele < MAX_ACCELE_T; nCntAccele ++)
	{
		if(g_Accele[nCntAccele].bUse)
			continue;		//使用したら次のループへ
		
		//未使用の敵が見つかった場合
		g_Accele[nCntAccele].fPosX  = fPosX;
		g_Accele[nCntAccele].fPosY  = fPosY;
		g_Accele[nCntAccele].fMoveX = 0.0f;
		g_Accele[nCntAccele].nLine  = nLine;
		g_Accele[nCntAccele].bUse   = true; 
		break;
		
	}	


}






void InitEnemy_T(void)
{
	int nCntEnemy;
	FILE *pFile;
	
	//----------車の初期化
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		//値初期化
		g_Car[nCntEnemy].fPosX      = 0.0f;
		g_Car[nCntEnemy].fPosY      = 0.0f;
		g_Car[nCntEnemy].fOldPosX   = 0.0f;
		g_Car[nCntEnemy].fOldPosY   = 0.0f;
		g_Car[nCntEnemy].fMoveX     = 0.0f;
		g_Car[nCntEnemy].fMoveY     = 0.0f;
		g_Car[nCntEnemy].bUse       = false;

		//ドット絵読み込み
		switch(nCntEnemy % 3)
		{
			case 0:
				pFile = fopen("car_red.txt","r");
				g_Car[nCntEnemy].eColor = HIGH;
				break;

			case 1:
				pFile = fopen("car_yellow.txt","r");
				g_Car[nCntEnemy].eColor = MIDDLE;				
				break;

			case 2:
				pFile = fopen("car_green.txt","r");
				g_Car[nCntEnemy].eColor = SLOW;
				break;
		}

		fscanf(pFile,"%s", g_Car[nCntEnemy].szCarDot);	
		fclose(pFile);
	}




	//----------加速床の初期化
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		g_Accele[nCntEnemy].fPosX  = 0.0f;
		g_Accele[nCntEnemy].fPosY  = 0.0f;
		g_Accele[nCntEnemy].bUse  = false;
		g_Accele[nCntEnemy].fMoveX = 0.0f;
		
		pFile = fopen("kasoku_1.txt","r");
		fscanf(pFile,"%s", g_Accele[nCntEnemy].szAcceleDot_1);	
		fclose(pFile);

		pFile = fopen("kasoku_2.txt","r");
		fscanf(pFile,"%s", g_Accele[nCntEnemy].szAcceleDot_2);	
		fclose(pFile);

		pFile = fopen("kasoku_3.txt","r");
		fscanf(pFile,"%s", g_Accele[nCntEnemy].szAcceleDot_3);	
		fclose(pFile);
	}



}



void UpdateEnemy_T(void)
{
	int nCntEnemy;
	
	bool bCollisionEnemyFlg;//プレイヤーが敵と接触したかどうかのフラグ
	float PlayerSpeed = GetPlayerSpeed_T();	//プレイヤーの移動速度を取得
	nCurrentFrame_T = GetFrameData_T();	//現在のフレーム数を取得
	bCollisionEnemyFlg = GetCollisionFlg_T();


	//==============敵の出現==============
	//-----車
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		//何番目の敵を使って描画するかの決定
		if(g_Car[nCntEnemy].bUse)
			continue;										//その敵をつかっていたら、次の敵が使用中か判定する


		if(nCurrentFrame_T >= g_nEnemySpawnframe[nCntEnemy])
			CreateEnemy_T( g_nEnemySpawnLine[nCntEnemy] );	//敵生成				もう使う敵の数分配列つくればいいか・・・

	}
	



	//-----加速床
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		//何番目の加速床を使って描画するかの決定
		if(g_Accele[nCntEnemy].bUse)
			continue;									//その加速床をつかっていたら、次の加速床が使用中か判定する

		if(nCurrentFrame_T >= g_nAcceleSpawnFrame_T[nCntEnemy])
			CreateAccele_T( g_nAcceleSpawnLine[nCntEnemy] );	//加速床生成

	}






	//===============更新==============
	//-----車
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		if(!g_Car[nCntEnemy].bUse)	//使ってない敵キャラはアップデートしない
			continue;

		//=====現在座標を退避=====
		g_Car[nCntEnemy].fOldPosX = g_Car[nCntEnemy].fPosX;
		g_Car[nCntEnemy].fOldPosY = g_Car[nCntEnemy].fPosY;
	

		//=====移動量を初期化=====
		g_Car[nCntEnemy].fMoveX = 0.0f;
		g_Car[nCntEnemy].fMoveY = 0.0f;


		//=====移動量を設定=====
		switch(g_Car[nCntEnemy].eColor)
		{
		case HIGH:
			g_Car[nCntEnemy].fMoveX = MOVE_SIZE_T_HIGH_T - PlayerSpeed;
			break;

		case MIDDLE:
			g_Car[nCntEnemy].fMoveX = MOVE_SIZE_T_MIDDLE_T - PlayerSpeed;
			break;

		case SLOW:
			g_Car[nCntEnemy].fMoveX = MOVE_SIZE_T_SLOW_T - PlayerSpeed;
			break;
		}

		if(bCollisionEnemyFlg)
		{

		}
		
		//g_Car[nCntEnemy].fMoveX += GetSpeedUpData();
		
		//=====座標更新=====
		g_Car[nCntEnemy].fPosX += g_Car[nCntEnemy].fMoveX;

	}


	

	//-----加速床
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		if(!g_Accele[nCntEnemy].bUse)	//使ってない敵キャラはアップデートしない
			continue;

		//=====移動量を初期化=====
		g_Accele[nCntEnemy].fMoveX = MOVE_SIZE_T_NORMAL_T;


		//=====移動量を設定=====		
		g_Accele[nCntEnemy].fMoveX -= PlayerSpeed;
		

		//=====座標更新=====
		g_Accele[nCntEnemy].fPosX += g_Accele[nCntEnemy].fMoveX;

	}


}


//出現ラインが上（nLine == 0）の敵の描画
void DrawBackEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	

	//-----加速床
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Accele[nCntEnemy].nLine != 0)
			continue;					//出現ラインが上じゃない敵は、ここでは描画しない



		//-----加速床描画
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//透明なら何も描画しない
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}


	//-----車
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Car[nCntEnemy].nLine % 3 != 0)
			continue;					//出現ラインが上じゃない敵は、ここでは描画しない



		//-----敵描画
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')			//透明なら何も描画しない
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T( ((int)g_Car[nCntEnemy].fPosX + nX), ((int)g_Car[nCntEnemy].fPosY + nY), g_Car[nCntEnemy].szCarDot[nX + (nY * 24)]);
			}
		}
	}

}

//出現ラインが真ん中（nLine == 1）の敵の描画
void DrawMiddleEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	
	//-----加速床
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Accele[nCntEnemy].nLine != 1)
			continue;					//出現ラインが真ん中じゃない敵は、ここでは描画しない



		//-----加速床描画
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//透明なら何も描画しない
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}

	//-----車
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Car[nCntEnemy].nLine % 3 != 1)
			continue;					//出現ラインが真ん中じゃない敵は、ここでは描画しない



		//-----敵描画
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')			//透明なら何も描画しない
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T( ((int)g_Car[nCntEnemy].fPosX + nX), ((int)g_Car[nCntEnemy].fPosY + nY), g_Car[nCntEnemy].szCarDot[nX + (nY * 24)]);
			}
		}
	}
	
}

//出現ラインが下（nLine == 2）の敵の描画
void DrawFrontEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	

	//-----加速床
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Accele[nCntEnemy].nLine != 2)
			continue;					//出現ラインが下じゃない敵は、ここでは描画しない



		//-----加速床描画
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//透明なら何も描画しない
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}

	//-----車
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//未使用なら次のループへ

		if(g_Car[nCntEnemy].nLine % 3 != 2)
			continue;					//出現ラインが下じゃない敵は、ここでは描画しない



		//-----敵描画
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')		//透明なら何も描画しない
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//Ｘ座標が０以下の場合、描画しない
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//ガードレールのところは描画しない
					continue;


				SetNextData_T( ((int)g_Car[nCntEnemy].fPosX + nX), ((int)g_Car[nCntEnemy].fPosY + nY), g_Car[nCntEnemy].szCarDot[nX + (nY * 24)]);
			}
		}
	}

}






TEnemy_T *GetEnemyData_T(void)
{
	return g_Car;
}


TAccelerator_T *GetAcceleData_T(void)
{
	return g_Accele;
}