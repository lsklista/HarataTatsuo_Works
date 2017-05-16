//////////////////////////////////////////////
//ファイル名　：Field.cpp
//制作者　　　：原田達夫
//
//概要　　　　：フィールド（道路、家など）のcppファイル
//////////////////////////////////////////////


//====================インクルード部
#include "CScreen.h"
#include "Buffer_T.h"
#include "Player_T.h"
#include "Field_T.h"




//====================マクロ定義
#define MAX_WHITELINE_T			(6)
#define MAX_GUARDRAIL_T			(12)


#define GUARDRAIL_WIDTH_T			(6)
#define GUARDRAIL_HEIGHT_T		(4)


//-----構造体宣言
struct TWhiteLine_T				//道路の白線
{
	float fPosX, fPosY;
	float fMoveX;
	char  szWhiteLine[41];
};

struct TGuardRail_T				//ガードレール
{
	float fPosX, fPosY;
	float fMoveX;
	char  szGuardRail[25];
};







//====================プロトタイプ宣言




//==========グローバル宣言==========
TWhiteLine_T g_WhiteLine_T[MAX_WHITELINE_T];
TGuardRail_T g_GuardRail_T[MAX_GUARDRAIL_T];




void InitField_T(void)
{
	//==========道路の白線の初期化
	int nCntField;
	FILE *pFile;

	g_WhiteLine_T[0].fPosX  = 1.0f;
	g_WhiteLine_T[0].fPosY  = 25.0f;
	g_WhiteLine_T[0].fMoveX = 0.0f;
	
	g_WhiteLine_T[1].fPosX  = 1.0f;
	g_WhiteLine_T[1].fPosY  = 36.0f;
	g_WhiteLine_T[1].fMoveX = 0.0f;

	g_WhiteLine_T[2].fPosX  = 101.0f;
	g_WhiteLine_T[2].fPosY  = 25.0f;
	g_WhiteLine_T[2].fMoveX = 0.0f;

	g_WhiteLine_T[3].fPosX  = 101.0f;
	g_WhiteLine_T[3].fPosY  = 36.0f;
	g_WhiteLine_T[3].fMoveX = 0.0f;

	g_WhiteLine_T[4].fPosX  = 201.0f;
	g_WhiteLine_T[4].fPosY  = 25.0f;
	g_WhiteLine_T[4].fMoveX = 0.0f;

	g_WhiteLine_T[5].fPosX  = 201.0f;
	g_WhiteLine_T[5].fPosY  = 36.0f;
	g_WhiteLine_T[5].fMoveX = 0.0f;

	//ドット絵読み込み
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		pFile = fopen("white_line.txt", "r");
		fscanf(pFile,"%s", g_WhiteLine_T[nCntField].szWhiteLine);	
		fclose(pFile);
	}




	//==========ガードレールの初期化
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		//Ｘ座標
		if(nCntField < 2)
			g_GuardRail_T[nCntField].fPosX = 1.0f;
		else if(nCntField < 4)
			g_GuardRail_T[nCntField].fPosX = 41.0f;
		else if(nCntField < 6)
			g_GuardRail_T[nCntField].fPosX = 81.0f;
		else if(nCntField < 8)
			g_GuardRail_T[nCntField].fPosX = 121.0f;
		else if(nCntField < 10)
			g_GuardRail_T[nCntField].fPosX = 161.0f;
		else if(nCntField < 12)
			g_GuardRail_T[nCntField].fPosX = 201.0f;

		//Ｙ座標
		if(nCntField % 2 == 0)
			g_GuardRail_T[nCntField].fPosY = 9.0f;
		else
			g_GuardRail_T[nCntField].fPosY = 44.0f;


		//移動量
		g_GuardRail_T[nCntField].fMoveX = 0.0f;

		//ドット絵読み込み
		pFile = fopen("guardrail.txt", "r");
		fscanf(pFile,"%s", g_GuardRail_T[nCntField].szGuardRail);	
		fclose(pFile);

	}
}


void UpdateField_T(void)
{
	int nCntField;
	float PlayerSpeed = GetPlayerSpeed_T();	//プレイヤーの移動速度を取得
	

	//==========道路の白線のアップデート
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		//=====移動量を初期化=====
		g_WhiteLine_T[nCntField].fMoveX = MOVE_SIZE_T_NORMAL_T;
		
		//=====移動量を設定=====
		g_WhiteLine_T[nCntField].fMoveX -= PlayerSpeed;


		//=====座標更新=====
		g_WhiteLine_T[nCntField].fPosX += g_WhiteLine_T[nCntField].fMoveX;


		//座標補正・・・Ｘ座標が-100いったら右に戻す
		if(g_WhiteLine_T[nCntField].fPosX < -100)
		{
			g_WhiteLine_T[nCntField].fPosX += 300;
		}
	}



	//==========ガードレールのアップデート
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		//=====移動量を初期化=====
		g_GuardRail_T[nCntField].fMoveX = MOVE_SIZE_T_NORMAL_T;
		
		//=====移動量を設定=====
		g_GuardRail_T[nCntField].fMoveX -= PlayerSpeed;


		//=====座標更新=====
		g_GuardRail_T[nCntField].fPosX += g_GuardRail_T[nCntField].fMoveX;


		//座標補正・・・Ｘ座標が-40いったら右に戻す
		if(g_GuardRail_T[nCntField].fPosX < -40)
		{
			g_GuardRail_T[nCntField].fPosX += 240;
		}

	}




	


}



void DrawBackField_T(void)
{
	int nX;
	int nY;
	int nCntField;


	//==========道路の白線
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		for(nX = 0 ; nX < 40 ; nX ++)
		{
			if(((int)g_WhiteLine_T[nCntField].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
				continue;

			if(((int)g_WhiteLine_T[nCntField].fPosX + nX) < 0)		//Ｘ座標が０以下の場合、描画しない
				continue;

			//描画する
			SetNextData_T( ((int)g_WhiteLine_T[nCntField].fPosX + nX), ((int)g_WhiteLine_T[nCntField].fPosY), g_WhiteLine_T[nCntField].szWhiteLine[nX]);
		}
	}


	//==========ガードレール（奥）
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		if(nCntField % 2 != 0)			//手前のガードレールなら描画しない
			continue;


		for(nX = 0 ; nX < GUARDRAIL_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < GUARDRAIL_HEIGHT_T ; nY ++)
			{
				if(((int)g_GuardRail_T[nCntField].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_GuardRail_T[nCntField].fPosX + nX) < 0)		//Ｘ座標が０以下の場合、描画しない
					break;

				//描画する
				SetNextData_T( ((int)g_GuardRail_T[nCntField].fPosX + nX),
							 ((int)g_GuardRail_T[nCntField].fPosY + nY),
							 g_GuardRail_T[nCntField].szGuardRail[nX + (nY * GUARDRAIL_WIDTH_T)]
						   );
			}
		}
	}



}






void DrawFrontField_T(void)
{
	int nX;
	int nY;
	int nCntField;

	

	//==========ガードレール（手前）
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		if(nCntField % 2 == 0)		//奥のガードレールなら描画しない
			continue;


		for(nX = 0 ; nX < GUARDRAIL_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < GUARDRAIL_HEIGHT_T ; nY ++)
			{
				if(((int)g_GuardRail_T[nCntField].fPosX + nX) >= 200)		//Ｘ座標が２００を超えている場合、描画しない
					continue;

				if(((int)g_GuardRail_T[nCntField].fPosX + nX) < 0)		//Ｘ座標が０以下の場合、描画しない
					break;

				//描画する
				SetNextData_T( ((int)g_GuardRail_T[nCntField].fPosX + nX),
							 ((int)g_GuardRail_T[nCntField].fPosY + nY),
							 g_GuardRail_T[nCntField].szGuardRail[nX + (nY * GUARDRAIL_WIDTH_T)]
						   );
			}
		}
	}
}