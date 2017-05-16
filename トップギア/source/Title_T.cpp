//////////////////////////////////////////////
//ƒtƒ@ƒCƒ‹–¼@FTitle.cpp
//§ìŽÒ@@@FŒ´“c’B•v
//
//ŠT—v@@@@Fƒ^ƒCƒgƒ‹‚Ìcppƒtƒ@ƒCƒ‹
//////////////////////////////////////////////


//====================ƒCƒ“ƒNƒ‹[ƒh•”
#include "CScreen.h"
#include "Buffer_T.h"
#include "Main_T.h"




//====================ƒ}ƒNƒ’è‹`
#define PUSHENTER_WIDTH_T	(100)	//‚o‚t‚r‚g@‚d‚m‚s‚d‚q‚Ì‰¡•
#define PUSHENETR_HEIGHT_T	(8)		//‚o‚t‚r‚g@‚d‚m‚s‚d‚q‚Ìc•
#define BRING_ENTERVAL_T	(500)	//ƒuƒŠƒ“ƒO‚ÌŠÔŠu
#define PUSHENETR_DRAW_X_T	(50)	//‚o‚t‚r‚g@‚d‚m‚s‚d‚q‚Ì•\Ž¦ŠJŽnˆÊ’u‚Ì‚wÀ•W
#define PUSHENETR_DRAW_Y_T	(40)	//‚o‚t‚r‚g@‚d‚m‚s‚d‚q‚Ì•\Ž¦ŠJŽnˆÊ’u‚Ì‚xÀ•W

//====================ƒvƒƒgƒ^ƒCƒvéŒ¾




//==========ƒOƒ[ƒoƒ‹éŒ¾==========
char g_szTitleMap_T[MAX_DRAW_T];
char g_szPushEnter_T[PUSHENTER_WIDTH_T * PUSHENETR_HEIGHT_T + 1];
bool g_bDrawFlg_T;



void InitTitle_T(void)
{
	FILE *pFile;

	pFile = fopen("title.txt","r");
	fscanf(pFile,"%s",g_szTitleMap_T);
	fclose(pFile);

	/*pFile = fopen("pushenter.txt","r");
	fscanf(pFile,"%s",g_szPushEnter_T);
	fclose(pFile);*/
}





void UpdateTitle_T(void)
{
	int nExecTime, nCurrentTime;
	nExecTime = nCurrentTime = timeGetTime();



	//ƒGƒ“ƒ^[‰Ÿ‚³‚ê‚½‚çAƒQ[ƒ€ŠJŽn
	if(INP(PK_ENTER) || GPBTN3() != 0)
		SetState_T(STATE_GAME_T);
		

	//u‚o‚t‚r‚g@‚d‚m‚s‚d‚qv‚ðƒuƒŠƒ“ƒO‚³‚¹‚é‚½‚ß‚Ìƒtƒ‰ƒO‘€ì
	nCurrentTime = timeGetTime();

	if(nCurrentTime - nExecTime >= BRING_ENTERVAL_T)
	{
		nExecTime = nCurrentTime;

		if(g_bDrawFlg_T)
			g_bDrawFlg_T = false;
		else
			g_bDrawFlg_T = true;
	}

}





void DrawTitle_T(void)
{
	int nX, nY;

	for(nY = 0 ; nY < 50 ; nY ++)
		for(nX = 0 ; nX < 200 ; nX ++)
			SetNextData_T(nX, nY, g_szTitleMap_T[nX + nY * 200]);

	
	if(g_bDrawFlg_T)
	{
		for(nY = 0 ; nY < PUSHENETR_HEIGHT_T ; nY ++)
			for(nX = 0 ; nX < PUSHENTER_WIDTH_T ; nX ++)
				SetNextData_T(PUSHENETR_DRAW_X_T + nX, PUSHENETR_DRAW_Y_T + nY, g_szPushEnter_T[nX + nY * PUSHENTER_WIDTH_T]);
	}



}