//////////////////////////////////////////////
//�g�d�v��i
//�[���E�E�E�@�Q���Q�W���܂�
//���[���E�E�@�Q���P�X���܂�
//
//�v���O�������F�g�d�v�f�`�l�d
//�t�@�C�����@�Fmain.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�Q�[���̗���E����Ɋւ���cpp�t�@�C��
//
//////////////////////////////////////////////

//====================�C���N���[�h��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CScreen.h"
#include "Player_T.h"		//�v���C���[
#include "Enemy_T.h"		//�G
#include "Buffer_T.h"		//�o�b�t�@�[
#include "Field_T.h"		//�n�`
#include "Main_T.h"			//���C��
#include "Title_T.h"		//�^�C�g��
#include "Result_T.h"		//���U���g
#include "Rank_T.h"			//�����N
#include "Sound_T.h"		//��


//====================�}�N����`
#define DIPS_INTERVAL_T (1000)
#define DIPS_POS_X_T       (1)
#define DIPS_POS_Y_T		 (1)

const int RATE = 1000 / 60;


//====================�v���g�^�C�v�錾
void Continue_T(void);


//====================�O���[�o���錾
unsigned int nFrame_T;
state_T g_eGameState_T;
bool bGameContinue_T = true;	//�Q�[������������邩�ǂ����̃t���O
bool bGameEnd_T;		//�Q�[������������邩�ǂ����̃t���O







//==============================================
//���C���֐�
//�֐����Fmain
//�����@�F�Ȃ�
//�߂�l�F�Ȃ�
//-----�T�v-------------------------------------
//�v���O�����̗���
//==============================================
void main(void)
{
	bGameEnd_T = false;
		InitBuffer_T();



	while(!bGameEnd_T)
	{
		//-----�ϐ��錾-----
		int nExecTime;			//���s����
		int nDipsFPSTime;		//FPS�l�̕\������
		int nCurrentTime;		//���݂̎���
		int nFPS;				//�f�o�b�O�p��FPS�l
		int nFrame_TCount;		//�f�o�b�O�p��FPS�l�̃J�E���^�[
		
		TPlayer_T PlayerData;



		//----- ���������� -----
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
	
		//----- ���O���� -----
		timeBeginPeriod(1);			//����\
		CUROFF();					//�J�[�\������
		StartSound_T(BGM_T,REPEAT_T);



		//----- �Q�[�����C�����[�v -----
		while(bGameContinue_T)
		{

		
			nCurrentTime = timeGetTime();		//���̎��Ԃ��Ƃ�

			if(nCurrentTime - nDipsFPSTime >=DIPS_INTERVAL_T)
			{
				nDipsFPSTime = nCurrentTime;
				nFPS = nFrame_TCount;
				nFrame_TCount = 0;
			}

			if(nCurrentTime - nExecTime >= RATE)
			{
				//----- �X�V���� -----
				nExecTime = nCurrentTime;
				nFrame_TCount ++;
				nFrame_T ++;
				if(nFrame_T > 1900)		//�G�Ƃ���S���o���āA����������A�G�����Z�b�g
				{
					nFrame_T = 0;
					InitEnemy_T();
				}
				switch(g_eGameState_T)
				{
					//-----�^�C�g��
					case STATE_TITLE_T:
						UpdateTitle_T();
						DrawTitle_T();
						DrawBuffer_T();
						nFrame_T = 0;
						break;
					
					//-----�Q�[��
					case STATE_GAME_T:
						UpdatePlayer_T();
						UpdateField_T();
						UpdateEnemy_T();
						UpdateBuffer_T();
			
						//----- �`�揈�� -----
						PlayerData = *GetPlayerData_T();		//�v���C���[�̏����擾�i�`�悷�鏇�ԂɊ֌W����j
						DrawBackField_T();					//���H�̔����≜�̃K�[�h���[��
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
						DrawFrontField_T();			//��O�̃K�[�h���[��
						DrawBuffer_T();				//�o�b�t�@�̏�����ʂɏo���i�����Ŏ��ۂɕ`��j
						break;

					//-----���U���g
					case STATE_RESULT_T:		//�v���C���[�̂g�o���O�ɂȂ����烊�U���g
						UpdateResult_T();
						DrawResult_T();
						DrawBuffer_T();
						while(1)									//���͑҂�
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
	printf("������x�v���C���܂����H");
	LOCATE(80, 42);
	printf("�͂��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@������");
	LOCATE(80,42);
	COLOR(WHITE, SKYBLUE);
	printf("�͂�");

	while(1)
	{
		if(INP(PK_LEFT) || GPLEFT() != 0)
		{
			LOCATE(80,42);
			COLOR(BLACK, SKYBLUE);
			printf("�͂�");

			LOCATE(114,42);
			COLOR(WHITE,BLACK);
			printf("������");

			bGameEnd_T = false;
			

			INPCLEAR();
		}

		if(INP(PK_RIGHT) || GPRIGHT() != 0)
		{
			LOCATE(80,42);
			COLOR(WHITE, BLACK);
			printf("�͂�");

			LOCATE(114,42);
			COLOR(BLACK,SKYBLUE);
			printf("������");

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

