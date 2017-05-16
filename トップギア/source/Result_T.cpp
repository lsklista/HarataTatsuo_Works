//////////////////////////////////////////////
//ファイル名　：Title.cpp
//制作者　　　：原田達夫
//
//概要　　　　：タイトルのcppファイル
//////////////////////////////////////////////


//====================インクルード部
#include "CScreen.h"
#include "Buffer_T.h"
#include "Main_T.h"
#include "Player_T.h"




//====================マクロ定義
//#define MAX_DRAW			(10001)		//フィールドのマス数
//#define MAX_DRAW_WIDTH		(200)		//フィールドの横幅
//#define MAX_DRAW_HEIGHT_T		(50)		//フィールドの縦幅


//====================プロトタイプ宣言




//==========グローバル宣言==========
char g_szResultMap_T[122 * 35 + 1];	//ゲームオーバー



void InitResult_T(void)
{
	FILE *pFile;

	pFile = fopen("gameover.txt","r");
	fscanf(pFile,"%s",g_szResultMap_T);
	fclose(pFile);
}


void UpdateResult_T(void)
{
	
}


void DrawResult_T(void)
{
	int nX, nY;

	for(nY = 0 ; nY < 35 ; nY ++)
	{
		for(nX = 0 ; nX < 122 ; nX ++)
		{
			if(g_szResultMap_T[nX + nY * 122] == '^')
				continue;

			SetNextData_T(39 + nX, 3 + nY, g_szResultMap_T[nX + nY * 122]);
		}
	}



}	