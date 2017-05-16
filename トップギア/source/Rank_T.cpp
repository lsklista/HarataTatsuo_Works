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

//====================プロトタイプ宣言




//==========グローバル宣言==========
char g_szRankA_T[122 * 35 + 1];		//Ａランク
char g_szRankB_T[122 * 35 + 1];		//Ｂランク
char g_szRankC_T[122 * 35 + 1];		//Ｃランク
char g_szRankD_T[122 * 35 + 1];		//Ｄランク



void InitRank_T(void)
{
	FILE *pFile;

	
	pFile = fopen("rankA.txt","r");
	fscanf(pFile,"%s",g_szRankA_T);
	fclose(pFile);
	pFile = fopen("rankB.txt","r");
	fscanf(pFile,"%s",g_szRankB_T);
	fclose(pFile);
	pFile = fopen("rankC.txt","r");
	fscanf(pFile,"%s",g_szRankC_T);
	fclose(pFile);
	pFile = fopen("rankD.txt","r");
	fscanf(pFile,"%s",g_szRankD_T);
	fclose(pFile);
}


void UpdateRank_T(void)
{
	
}


void DrawRank_T(void)
{
	int nX, nY;
	float fMileage = Getg_fMileageData_T();	//走行距離を取得


	if(fMileage > 10000.0f)														//ランクＡ
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankA_T[nX + nY * 122]);
	}
	else if(fMileage > 5000.0f)													//ランクＢ
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankB_T[nX + nY * 122]);
	}
	else if(fMileage > 1000.0f)													//ランクＣ
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankC_T[nX + nY * 122]);
	}
	else																		//ランクＤ
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankD_T[nX + nY * 122]);
	

}	