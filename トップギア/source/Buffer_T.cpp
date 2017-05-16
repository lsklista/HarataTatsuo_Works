//////////////////////////////////////////////
//ファイル名　：Buffer.cpp
//制作者　　　：原田達夫
//
//概要　　　　：ダブルバッファをするためのcppファイル
//////////////////////////////////////////////


//====================インクルード部
#include "CScreen.h"
#include "Buffer_T.h"
#include "Main_T.h"




//====================マクロ定義





//====================プロトタイプ宣言




//==========グローバル宣言==========
char g_szNowDraw[MAX_DRAW_T];			//今描画してる（前フレームの）フィールドデータ
char g_szNextDraw[MAX_DRAW_T];		//次に描画しようとしているフィールドデータ





void InitBuffer_T(void)
{
	//変数宣言
	FILE *pFile_1;
	FILE *pFile_2;

	//ファイルオープン
	pFile_1 = fopen(ORIGINAL_FIELD_T, "r");
	pFile_2 = fopen(ORIGINAL_FIELD_T, "r");

	//エラー処理
	if(!pFile_1 || !pFile_2)
	{
		printf("データが読み込めません。");
		rewind(stdin);
		getchar();

		exit(EXIT_FAILURE);	//強制終了
	}

	//ファイル読み込み
	fscanf(pFile_1, "%s", g_szNextDraw);
	fscanf(pFile_2, "%s", g_szNowDraw);

	//ファイルクローズ
	fclose(pFile_1);
	fclose(pFile_2);
}





void UpdateBuffer_T(void)
{
	
}





void DrawBuffer_T(void)
{
	//変数宣言
	int nCntWidth;
	int nCntHeight;
	static bool bDrawInitialFlg = false;
	state_T NowState = GetState_T(); 

		//-----初回描画
		if(!bDrawInitialFlg)
		{
			for( nCntHeight = 0 ; nCntHeight < MAX_DRAW_HEIGHT_T_T - 1 ; nCntHeight ++)
			{
				for( nCntWidth = 0; nCntWidth < MAX_DRAW_WIDTH_T ; nCntWidth ++)
				{
					//マップ描画
					if((g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0xF0) == 0x60)					//a～f
						BACKCOLOR((g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09);
					else
						BACKCOLOR(g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F);				//0～9
					LOCATE(nCntWidth + 1 , nCntHeight + 1);
					printf(" ");

				}
			}
				bDrawInitialFlg = true;
		}
	


	//描画処理
	for( nCntHeight = 0 ; nCntHeight < MAX_DRAW_HEIGHT_T_T - 1 ; nCntHeight ++)
	{
		for( nCntWidth = 0; nCntWidth < MAX_DRAW_WIDTH_T ; nCntWidth ++)
		{
			//色が変わっていなかったら次のループへ
			if( g_szNowDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)] == g_szNextDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)])
				continue;

			//前フレームと変わっているところだけマップ描画(色は文字コードで判断)
			if((g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0xF0) == 0x60)					//a～f
				COLOR((g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09, (g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09);
			else
				COLOR(g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F, g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F);		//0～9
			LOCATE(nCntWidth + 1 , nCntHeight + 1);		//描画位置
			printf("a");								//描画

			//if(NowState != STATE_TITLE)
			//{
				//もう変えてしまったマスの情報を入れる
				g_szNowDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)]  = g_szNextDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)];
			//}

		}
	}

	//-----NextをNowに上書きする
	FILE *pFile;
	
	pFile = fopen(ORIGINAL_FIELD_T, "r");

	//エラー処理
	if(!pFile)
	{
		printf("データが読み込めません。");
		rewind(stdin);
		getchar();

		exit(EXIT_FAILURE);	//強制終了
	}

	fscanf(pFile, "%s", g_szNextDraw);

	fclose(pFile);
}




void SetNextData_T(int nX, int nY, char szColor)
{
	int nTest;
	nTest = nX + (nY  * 200);
	g_szNextDraw[nTest] = szColor;
}