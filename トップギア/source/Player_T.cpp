//////////////////////////////////////////////
//�t�@�C�����@�FPlayer.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�v���C���[��cpp�t�@�C��
//////////////////////////////////////////////



//====================�C���N���[�h��
#include "CScreen.h"
#include "Buffer_T.h"
#include "Enemy_T.h"
#include "Player_T.h"
#include "Main_T.h"
#include "Sound_T.h"




//====================�}�N����`
#define MY_POS_X_T			   (  0.0f)		//�v���C���[�̏����ʒu�̂w���W
#define MY_POS_Y_T			   ( 30.0f)		//�v���C���[�̏����ʒu�̂x���W

#define LIMIT_LEFT_T			   (  0.0f)		//�v���C���[���ړ��ł���E�����̈ړ����E
#define LIMIT_RIGHT_T			   (176.0f)		//�v���C���[���ړ��ł��鍶�����̈ړ����E
#define LIMIT_UP_T			   (  6.0f)		//�v���C���[���ړ��ł��������̈ړ����E	6
#define LIMIT_BOTTOM_T		   ( 34.0f)		//�v���C���[���ړ��ł��鉺�����̈ړ����E


#define PLAYER_LIFE_T			   (     3)		//�v���C���[�̂g�o�i����܂ł������Ă������j	�������ς���Ƃ��́A�������̐��������Ă�������
#define NO_HIT_INTERVAL_T		   (  1300)		//�G�ɓ���������́A���G����


#define MOVE_SIZE_T			   (  2.0f)		//�_�b�V�����ĂȂ����̃f�t�H���g�̈ړ���
#define SPEEDUP_SIZE_T		   ( 0.07f)		//�_�b�V���ɂ��ړ��ʂ̉�����	0.05f
#define SPEEDDOWN_SIZE_T		   ( 0.10f)		//�_�b�V�����ĂȂ����ɂ������ʂ̌�����
#define LIMIT_SPEEDUP_T		   (17.00f)		//�����ʂ̌��E�l
#define HIGHFRICTION_SIZE_T	   (0.015f)		//�ړ��ʂ��傫���Ƃ��̖��C�W��
#define SLOWFRICTION_SIZE_T	   (0.060f)		//�ړ��ʂ��������Ƃ��̖��C�W��

#define LIMIT_ACCELERATOR_T	   ( 30.0f)		//�������𓥂񂾎��̑��x�̌��E�l
#define ACCELE_SPEEDDOWN_SIZE_T  ( 0.20f)		//�������𓥂�ŁA���E���x�𒴂��Ă����Ԃ̂Ƃ��̌�����

#define MOVE_HITSIZE_T		   ( 0.20f)		//�Ԃɓ����������ɂȂ��Ă��܂����x
#define HEAL_SPEED_T			   ( 0.05f)		//�Ԃɓ������Ēx���Ȃ�����́A���X�Ɍ��̑����ɂ��ǂ��Ă�����

#define DRAW_INTERVAL_T		   (   100)		//�Ԃɓ����������̓_�ł���Ԋu


#define MILEAGE_FRICTION_T	   ( 0.18f)		//���s�����ɂ�����W���i���̂܂܂̒l�𑫂�����傫���Ȃ肷����̂Łj




//�L�����̃h�b�g�G�֘A�̃}�N����`
#define PLAYER_WIDTH_T		   (12)//(�S�p)
#define PLAYER_HEIGHT_T		   (12)

#define SMOKE_WIDTH_T		   (12)//(���p)
#define SMOKE_HEIGHT_T		   ( 6)





struct THeart_T
{
	int nPosX;
	int nPosY;
	char szHeart[100];
};




//====================�v���g�^�C�v�錾
bool CheckCollisionEnemy_T(void);
bool CheckCollisionAccele_T(void);




//====================�O���[�o���錾
TPlayer_T g_Player_T;				//�v���C���[�̍\���̂̐錾
float g_fSpeedUp_T;				//�_�b�V���ɂ��X�s�[�h�A�b�v
THeart_T Heart_T[PLAYER_LIFE_T];		//�n�[�g�i�v���C���[�̂g�o�\���j�̍\���̂̐錾
bool g_bAcceleFlg_T;				//�������𓥂�ŁA���E���x�𒴂�����Ԃɂ��邩�i���̏�Ԃ̎��͑��x�̌��E�̕␳�͎󂯂Ȃ����A������茸�����Ă��j
bool g_bCollisionEnemyFlg_T;		//�G�ɓ����������ǂ����̃t���O
char g_szSmoke_1_T[73];			//�����������̉����̂P�i��������������ł�A������Ƃ������j
char g_szSmoke_2_T[73];			//�����������̉����̂Q�i�܂��܂�����������ł�A���������̉��j
char g_szSmoke_3_T[73];			//�����������̉����̂R�i�قڂl�`�w�܂ŉ���������o��A�Ήԁj
bool g_bShowHitPlayer_T;			//�G�ɓ��������v���C���[��_�ł����邽�߂́A�`�悷�邩���Ȃ����̃t���O
int  g_nHitTime_T;				//�v���[���[���G�ɓ�����������
float g_fMileage_T;				//�v���C���[�������������i�X�R�A�Ɋ֌W���Ă���j

char g_szNumber_T[10][41];

//char g_szNumber_0_T[41];			//�����̂O
//char g_szNumber_1_T[41];			//�����̂P
//char g_szNumber_2_T[41];			//�����̂Q
//char g_szNumber_3_T[41];			//�����̂R
//char g_szNumber_4_T[41];			//�����̂S
//char g_szNumber_5_T[41];			//�����̂T
//char g_szNumber_6_T[41];			//�����̂U
//char g_szNumber_7_T[41];			//�����̂V
//char g_szNumber_8_T[41];			//�����̂W
//char g_szNumber_9_T[41];			//�����̂X
char g_szMeter_T[37];				//���[�g����m

int g_nMileage_T[4];				//���s�����i�[�p�̔z��




void InitPlayer_T(void)
{
	int nCntPlayer;
	FILE *pFile;
	
	//-----�v���C���[�̏�����
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


	//-----�����������ɏo�鉌�̏�����
	pFile = fopen("kemuri_1.txt","r");
	fscanf(pFile,"%s",g_szSmoke_1_T);
	fclose(pFile);

	pFile = fopen("kemuri_2.txt","r");
	fscanf(pFile,"%s",g_szSmoke_2_T);
	fclose(pFile);

	pFile = fopen("kemuri_3.txt","r");
	fscanf(pFile,"%s",g_szSmoke_3_T);
	fclose(pFile);


	//�����̏�����
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


	//-----���[�g��(m)�̏�����
	pFile = fopen("m.txt","r");
	fscanf(pFile,"%s",g_szMeter_T);
	fclose(pFile);



	g_fMileage_T = 0.0f;
}

void UpdatePlayer_T(void)
{
	static int nHitTime = timeGetTime();	//�v���C���[���G�ɓ�����������
	int nCurrentTime;						//���̎���
	static int nExecTime;					//�`��t���O�̎��s����
	

	static int nCntHit;


	//=====���ݍ��W��ޔ�=====
	g_Player_T.fOldPosX = g_Player_T.fPosX;
	g_Player_T.fOldPosY =	g_Player_T.fPosY;
	

	//=====�ړ��ʂ�������=====
	g_Player_T.fMoveX =0.0f;
	g_Player_T.fMoveY =0.0f;


	//=====�L�[����=====
	if(INP(PK_RIGHT) || GPRIGHT() != 0)		//RIGHT�L�[�������ꂽ��
	{
		g_Player_T.fMoveX += MOVE_SIZE_T;
	}

	if(INP(PK_LEFT) || GPLEFT() != 0)		//LEFT�L�[�������ꂽ��
	{
		g_Player_T.fMoveX -= MOVE_SIZE_T;
	}
	if(INP(PK_UP) || GPUP() != 0)			//UP�L�[�������ꂽ��
	{
		g_Player_T.fMoveY -= MOVE_SIZE_T;
	}
	if(INP(PK_DOWN) || GPDOWN() != 0)		//DOWN�L�[�������ꂽ��
	{
		g_Player_T.fMoveY += MOVE_SIZE_T;
	}


	//===== �_�b�V�� =====
	if(INP(PK_SP) || GPBTN3() != 0)
		g_fSpeedUp_T += SPEEDUP_SIZE_T;
	else
		g_fSpeedUp_T -= SPEEDDOWN_SIZE_T;


	//===== �u���[�L =====
	if(INP(PK_SHIFT) || GPBTN1() != 0)
	{
		if(g_fSpeedUp_T > 10.0f)
			g_fSpeedUp_T -= (g_fSpeedUp_T * HIGHFRICTION_SIZE_T);		//���݂̃X�s�[�h�ɖ��C�W�����������l�����ۂɌ��������悤�ɂ���
		else
			g_fSpeedUp_T -= (g_fSpeedUp_T * SLOWFRICTION_SIZE_T);


	}


	//===== �����ʕ␳ =====
	if(g_fSpeedUp_T < 0)												//�������O�������Ȃ�A�␳
		g_fSpeedUp_T = 0.0f;
	if(g_fSpeedUp_T > LIMIT_SPEEDUP_T && !g_bAcceleFlg_T)					//�������𓥂�łȂ���ԂŁA���E���x�𒴂��悤�Ƃ�����A�␳
		g_fSpeedUp_T = LIMIT_SPEEDUP_T;
	if(g_bAcceleFlg_T)												//�������𓥂�ŁA������Ԃɂ���Ƃ��̌���
		g_fSpeedUp_T -= ACCELE_SPEEDDOWN_SIZE_T;
	if(g_bAcceleFlg_T && g_fSpeedUp_T <= (LIMIT_SPEEDUP_T + MOVE_SIZE_T))	//�������𓥂񂾉�����ԂŁA���ʂ̌��E���x���x���Ȃ���������t���O�����낷
		g_bAcceleFlg_T = false;
	if(g_bCollisionEnemyFlg_T)										//�G�ɓ���������Ԃ̂Ƃ��A���X�Ɍ��̑����ɖ߂��B
		g_fSpeedUp_T += HEAL_SPEED_T;
	if(g_bCollisionEnemyFlg_T && (g_fSpeedUp_T >= MOVE_SIZE_T))		//�G�ɓ��������t���O�������Ă��āA���̑����ɖ߂�����A�t���O��������
		g_bCollisionEnemyFlg_T = false;

	//===== ���W�X�V =====
	g_Player_T.fPosX += g_Player_T.fMoveX;
	g_Player_T.fPosY += g_Player_T.fMoveY;


	//===== ���W�␳ =====
	if( g_Player_T.fPosX < LIMIT_LEFT_T)
		g_Player_T.fPosX = LIMIT_LEFT_T;

	if( g_Player_T.fPosX > LIMIT_RIGHT_T)
		g_Player_T.fPosX = LIMIT_RIGHT_T;

	if( g_Player_T.fPosY < LIMIT_UP_T)
		g_Player_T.fPosY = LIMIT_UP_T;

	if( g_Player_T.fPosY > LIMIT_BOTTOM_T)
		g_Player_T.fPosY = LIMIT_BOTTOM_T;



	//-----�G�Ƃ̂����蔻��
	nCurrentTime = timeGetTime();		//���ݎ��Ԃ��擾

	if( !g_Player_T.bNoHitTime && CheckCollisionEnemy_T() )		//���G���Ԃł͂Ȃ��A���A�G�Ɠ��������Ƃ��̏���
	{
		nHitTime = timeGetTime();		//�v���C���[���G�ɓ����������̎��Ԃ��擾
		nExecTime = timeGetTime();		//�v���C���[���G�ɓ����������̎��Ԃ��擾
		g_Player_T.bNoHitTime = true;		//���G�t���O�𗧂Ă�
		g_bShowHitPlayer_T = true;		//�_�Ńt���O�𗧂Ă�

		g_Player_T.nHp --;				//�v���C���[�̂g�o����
		StartSound_T(HIT_T, NOREPEAT_T);

		if(g_Player_T.nHp == 0)
			SetState_T(STATE_RESULT_T);		//�g�o���O�ɂȂ�����A�Q�[���I��

		g_Player_T.fMoveX = MOVE_HITSIZE_T;	//���x��x������
		g_fSpeedUp_T = 0.0f;				//�������Ȃ��ɂ���B
		g_bCollisionEnemyFlg_T = true;	//�u�G�ɓ��������v�t���O�����Ă�


	}
	
	if( g_Player_T.bNoHitTime && nCurrentTime - nHitTime >= NO_HIT_INTERVAL_T)	//���G�t���O�������Ă��āA���G���Ԃ��߂��Ă�����
		g_Player_T.bNoHitTime = false;										//���G�t���O��������

	if(g_Player_T.bNoHitTime && (nCurrentTime - nExecTime >= DRAW_INTERVAL_T))	//���G�t���O�������Ă��āA�_�ŊԊu����������
	{																		//�`��t���O�̐؂�ւ�
		nExecTime = nCurrentTime;
		if(g_bShowHitPlayer_T)
			g_bShowHitPlayer_T = false;
		else
			g_bShowHitPlayer_T = true;
	}
	if(!g_Player_T.bNoHitTime && g_bShowHitPlayer_T)							//���G�t���O���������Ă��āA�L�����`��t���O���������Ă�����
		g_bShowHitPlayer_T = false;											//�L�����`��t���O�����Ă�



	//�������Ƃ̂����蔻��
	if(CheckCollisionAccele_T())
	{
		g_bAcceleFlg_T = true;	//������Ԃɂ���
		g_fSpeedUp_T = 30.0f;
		StartSound_T(SPEEDUP_T,NOREPEAT_T);
	}

	//-----���s�����̌v�Z
	g_fMileage_T += (g_fSpeedUp_T + MOVE_SIZE_T) * MILEAGE_FRICTION_T;		//���s�����̕ϐ��ɍ��̃X�s�[�h�𑫂��Ă���

	//�z��ɒl���i�[
	g_nMileage_T[0] = ((int)g_fMileage_T / 10000);						//��̈�
	g_nMileage_T[1] = ((int)g_fMileage_T % 10000 / 1000);				//�S�̈�
	g_nMileage_T[2] = ((int)g_fMileage_T % 10000 % 1000 / 100);			//�\�̈�
	g_nMileage_T[3] = ((int)g_fMileage_T % 10000 % 1000 % 100 / 10);	//��̈�


}





void DrawPlayer_T(void)
{
	int nX;
	int nY;
	int nCntPlayer;
	int nMileage_PosX = 140;		//���s�����̂w���W						���V�����ǉ�
	static int nAnimeFlg = 1;		//�ǂ̃h�b�g�G���������̃t���O
	static float fAnimeCnt = 10.0f;
	
	if(!g_bShowHitPlayer_T)
	{
	
		//-----�A�j���t���O�̐ݒ�i�`�悷��h�b�g�G������
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


		//-----�v���C���[�̕`��
		for(nY = 0 ; nY < PLAYER_HEIGHT_T ; nY ++)
		{
			switch (nAnimeFlg)
			{
			case 1:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_1[nX + nY * 24] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_1[nX + nY * 24]);				
				}
				break;

			
			case 2:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_2[nX + nY * 24] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_2[nX + nY * 24]);				
				}
				break;

			
			case 3:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_3[nX + nY * 24] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_3[nX + nY * 24]);				
				}
				break;

			
			case 4:
				for(nX = 0 ; nX < (PLAYER_WIDTH_T*2) ; nX ++)
				{ 
					if(g_Player_T.szPlayer_4[nX + nY * 24] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;

					if(((int)g_Player_T.fPosY + nY) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX),((int)g_Player_T.fPosY + nY),g_Player_T.szPlayer_4[nX + nY * 24]);				
				}
				break;


			}




		
		}

	

		//-----�����������̉��E�΂̕`��E�E�E���̂P
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 5.0f && MOVE_SIZE_T + g_fSpeedUp_T < 10.0f)	//���������̉����̎��̉�
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_1_T[nX + nY * SMOKE_WIDTH_T] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;

					if(((int)g_Player_T.fPosX + nX - 12) < 0)
						continue;

					if(((int)g_Player_T.fPosY + nY + 6) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX - 12),((int)g_Player_T.fPosY + nY + 6),g_szSmoke_1_T[nX + nY * SMOKE_WIDTH_T]);				
				}
			}
		}

		//-----�����������̉��E�΂̕`��E�E�E���̂Q
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 10.0f && MOVE_SIZE_T + g_fSpeedUp_T < 15.0f)	//�܂��܂��̉����̎��̉�
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_2_T[nX + nY * SMOKE_WIDTH_T] == '^')			//�����Ȃ牽���`�悵�Ȃ�
						continue;
				
					if(((int)g_Player_T.fPosX + nX - 12) < 0)
						continue;

					if(((int)g_Player_T.fPosY + nY + 6) >= 45)
						continue;

					SetNextData_T( ((int)g_Player_T.fPosX + nX - 12),((int)g_Player_T.fPosY + nY + 6),g_szSmoke_2_T[nX + nY * SMOKE_WIDTH_T]);
				}
			}
		}

		//-----�����������̉��E�΂̕`��E�E�E���̂R
		if(MOVE_SIZE_T + g_fSpeedUp_T >= 15.0f)										//���Ȃ�̉����̎��̉�
		{
			for(nY = 0 ; nY < SMOKE_HEIGHT_T ; nY ++)
			{
			
				for(nX = 0 ; nX < SMOKE_WIDTH_T ; nX ++)
				{ 
					if(g_szSmoke_3_T[nX + nY * SMOKE_WIDTH_T] == '^')			//�����Ȃ牽���`�悵�Ȃ�
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

	
	//-----�n�[�g�}�[�N�̕`��
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



	//-----�����̉��Q�̃��[�v�V�����ǉ�

	//-----���s�����̕`��i�Ƃ肠�����A�����_�ȉ��؂�̂ĂS�P�^�\���Łj
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

	//���[�g����m�̕`��
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
	float fPlayerCenter_Up_X, fPlayerCenter_Up_Y;			//�v���C���[�̏㔼�g��X,Y���ꂼ��̒��S���W
	float fPlayerCenter_Front_X, fPlayerCenter_Front_Y;		//�v���C���[�̎��]�Ԃ̑O�ւ�X,Y���ꂼ��̒��S���W
	float fPlayerCenter_Back_X, fPlayerCenter_Back_Y;		//�v���C���[�̎��]�Ԃ̌�ւ�X,Y���ꂼ��̒��S���W
	float fEnemyCenter_X , fEnemyCenter_Y ;					//�G�i�ԁj��X,Y���ꂼ��̒��S���W

	TEnemy_T *pEnemy = GetEnemyData_T();
	
	fPlayerCenter_Up_X     = g_Player_T.fPosX + 12;			//�v���C���[�̏㔼�g      �̂w�̒��S���W�̊i�[
	fPlayerCenter_Up_Y     = g_Player_T.fPosY + 3;			//�v���C���[�̏㔼�g      �̂x�̒��S���W�̊i�[
	fPlayerCenter_Front_X  = g_Player_T.fPosX + 22;			//�v���C���[�̎��]�Ԃ̑O�ւ̂w�̒��S���W�̊i�[
	fPlayerCenter_Front_Y  = g_Player_T.fPosY + 9;			//�v���C���[�̎��]�Ԃ̑O�ւ̂x�̒��S���W�̊i�[
	fPlayerCenter_Back_X   = g_Player_T.fPosX + 3;			//�v���C���[�̎��]�Ԃ̌�ւ̂w�̒��S���W�̊i�[
	fPlayerCenter_Back_Y   = g_Player_T.fPosY + 9;			//�v���C���[�̎��]�Ԃ̌�ւ̂x�̒��S���W�̊i�[


	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++, pEnemy ++)
	{
		//���g�p�̓G�͔��肵�Ȃ�
		if(!pEnemy->bUse)
			continue;

		fEnemyCenter_X = pEnemy->fPosX + (ENEMY_CAR_WIDTH_T  / 2);	//�G�i�ԁj��X���̒��S���W�̊i�[
		fEnemyCenter_Y = pEnemy->fPosY + 6;							//�G�i�ԁj��Y���̒��S���W�̊i�[


		//�O��
		fDistance = (fPlayerCenter_Front_X - fEnemyCenter_X) * 
					(fPlayerCenter_Front_X - fEnemyCenter_X) +
					(fPlayerCenter_Front_Y - fEnemyCenter_Y) *
					(fPlayerCenter_Front_Y - fEnemyCenter_Y) * 4;

		if(fDistance < 150.0f)
			return true;


		//���
		fDistance = (fPlayerCenter_Back_X - fEnemyCenter_X) * 
					(fPlayerCenter_Back_X - fEnemyCenter_X) +
					(fPlayerCenter_Back_Y - fEnemyCenter_Y) *
					(fPlayerCenter_Back_Y - fEnemyCenter_Y) * 4;

		if(fDistance < 150.0f)
			return true;


	}
	
		//������Ȃ��������̏���
		return false;
}


bool CheckCollisionAccele_T(void)
{
	int nCntAccele;
	float fDistance;
	float fPlayerCenter_Front_X, fPlayerCenter_Front_Y;		//�v���C���[�̎��]�Ԃ̑O�ւ�X,Y���ꂼ��̒��S���W
	float fPlayerCenter_Back_X, fPlayerCenter_Back_Y;		//�v���C���[�̎��]�Ԃ̌�ւ�X,Y���ꂼ��̒��S���W
	float fAcceleCenter_X , fAcceleCenter_Y ;				//�I�C����X,Y���ꂼ��̒��S���W

	TAccelerator_T *pAccele = GetAcceleData_T();

	fPlayerCenter_Front_X  = g_Player_T.fPosX + 22;			//�v���C���[�̎��]�Ԃ̑O�ւ̂w�̒��S���W�̊i�[
	fPlayerCenter_Front_Y  = g_Player_T.fPosY + 9;			//�v���C���[�̎��]�Ԃ̑O�ւ̂x�̒��S���W�̊i�[
	fPlayerCenter_Back_X   = g_Player_T.fPosX + 3;			//�v���C���[�̎��]�Ԃ̌�ւ̂w�̒��S���W�̊i�[
	fPlayerCenter_Back_Y   = g_Player_T.fPosY + 9;			//�v���C���[�̎��]�Ԃ̌�ւ̂x�̒��S���W�̊i�[

	for(nCntAccele = 0 ; nCntAccele < MAX_ACCELE_T ; nCntAccele ++, pAccele ++)
	{
		//���g�p�̓G�͔��肵�Ȃ�
		if(!pAccele->bUse)
			continue;

		fAcceleCenter_X = pAccele->fPosX + (ACCELE_WIDTH_T  / 2);		//�I�C����X���̒��S���W�̊i�[
		fAcceleCenter_Y = pAccele->fPosY + (ACCELE_HEIGHT_T / 2);		//�I�C����Y���̒��S���W�̊i�[


		//=====�G�Ƃ̂����蔻��
		//�O��
		fDistance = (fPlayerCenter_Front_X - fAcceleCenter_X) * 
					(fPlayerCenter_Front_X - fAcceleCenter_X) +
					(fPlayerCenter_Front_Y - fAcceleCenter_Y) *
					(fPlayerCenter_Front_Y - fAcceleCenter_Y) * 4;

		if(fDistance < 100.0f)
			return true;


		//���
		fDistance = (fPlayerCenter_Back_X - fAcceleCenter_X) * 
					(fPlayerCenter_Back_X - fAcceleCenter_X) +
					(fPlayerCenter_Back_Y - fAcceleCenter_Y) *
					(fPlayerCenter_Back_Y - fAcceleCenter_Y) * 4;

		if(fDistance < 100.0f)
			return true;

	}

	//������Ȃ��������̖߂�l
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


float Getg_fMileageData_T(void)				//���V�����ǉ�
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