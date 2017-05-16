//===== インクルード =====
#include"CScreen.h"
#include"Sound_T.h"


//=====マクロ定義
#define MAXSOUND (3)



//===== グローバル変数 =====
int nSoundHandle[MAXSOUND];
LOOP_T eLoop_T;
SOUND_T eKind_T;




void InitSound_T(void)
{
	FILE *pFile;
	

	//===== ゲーム内で必要な音を開く =====
	nSoundHandle[0] = OPENWAVE(BGMFILE);
	//nSoundHandle[0] = OPENMP3(BGMFILE);
	nSoundHandle[1] = OPENWAVE(HITFILE);
	nSoundHandle[2] = OPENWAVE(SPEEDUPFILE);

}



void StartSound_T(SOUND_T eKind_T, LOOP_T eLoop_T)
{
	PLAYWAVE(nSoundHandle[eKind_T],eLoop_T);
	//PLAYMP3(nSoundHandle[eKind_T],eLoop_T);
}



void StopSound_T(SOUND_T eKind_T)
{
	STOPWAVE(nSoundHandle[eKind_T]);
	//STOPMP3(nSoundHandle[eKind_T]);
}

void CloseSound_T()
{
	CLOSEWAVE(0);
	//CLOSEMP3(0);
	CLOSEWAVE(1);
	CLOSEWAVE(2);
}