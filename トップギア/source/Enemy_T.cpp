//////////////////////////////////////////////
//�t�@�C�����@�FEnemy.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�G��cpp�t�@�C��
//////////////////////////////////////////////



//====================�C���N���[�h��
#include "CScreen.h"
#include "Buffer_T.h"
#include "Enemy_T.h"
#include "Player_T.h"
#include "Main_T.h"
#include "Field_T.h"


//====================�}�N����`
#define MOVE_SIZE_T_HIGH_T		   ( 0.80f)	//�Ԃ��Ԃ̈ړ���
#define MOVE_SIZE_T_MIDDLE_T	   ( 1.30f)	//���F���Ԃ̈ړ���
#define MOVE_SIZE_T_SLOW_T		   ( 1.50f)	//�΂̎Ԃ̈ړ���


#define CAR_POS_UP_X_T		   (200.0f)	//�Ԃ̃��C����̏����ʒu�̂w���W
#define CAR_POS_UP_Y_T		   ( 14.0f)	//�Ԃ̃��C����̏����ʒu�̂x���W
#define CAR_POS_MIDDLE_X_T	   (200.0f)	//�Ԃ̃��C�����̏����ʒu�̂w���W
#define CAR_POS_MIDDLE_Y_T	   ( 25.0f)	//�Ԃ̃��C�����̏����ʒu�̂x���W
#define CAR_POS_BOTTOM_X_T	   (200.0f)	//�Ԃ̃��C�����̏����ʒu�̂w���W
#define CAR_POS_BOTTOM_Y_T	   ( 36.0f)	//�Ԃ̃��C�����̏����ʒu�̂x���W

#define OIL_POS_UP_X_T		   (200.0f)	//�I�C���̃��C����̏����ʒu�̂w���W
#define OIL_POS_UP_Y_T		   ( 15.0f)	//�I�C���̃��C����̏����ʒu�̂x���W
#define OIL_POS_MIDDLE_X_T	   (200.0f)	//�I�C���̃��C�����̏����ʒu�̂w���W
#define OIL_POS_MIDDLE_Y_T	   ( 27.0f)	//�I�C���̃��C�����̏����ʒu�̂x���W
#define OIL_POS_BOTTOM_X_T	   (200.0f)	//�I�C���̃��C�����̏����ʒu�̂w���W
#define OIL_POS_BOTTOM_Y_T	   ( 37.0f)	//�I�C���̃��C�����̏����ʒu�̂x���W

#define ACCELE_POS_UP_X_T		   (200.0f)	//�������̃��C����̏����ʒu�̂w���W
#define ACCELE_POS_UP_Y_T		   ( 15.0f)	//�������̃��C����̏����ʒu�̂x���W
#define ACCELE_POS_MIDDLE_X_T	   (200.0f)	//�������̃��C�����̏����ʒu�̂w���W
#define ACCELE_POS_MIDDLE_Y_T	   ( 27.0f)	//�������̃��C�����̏����ʒu�̂x���W
#define ACCELE_POS_BOTTOM_X_T	   (200.0f)	//�������̃��C�����̏����ʒu�̂w���W
#define ACCELE_POS_BOTTOM_Y_T	   ( 37.0f)	//�������̃��C�����̏����ʒu�̂x���W


//#define



//-----�\���̐錾




//====================�v���g�^�C�v�錾
void CreateEnemy_T(int);		//�Ԃ��o��������
void CreateOil_T(int);		//�I�C�����o��������
void CreateAccele_T(int);		//���������o��������




//====================�O���[�o���錾
TEnemy_T g_Car[MAX_ENEMY_T];			//��
TAccelerator_T   g_Accele[MAX_ACCELE_T];//������
int g_nEnemySpawnframe[MAX_ENEMY_T] = {
										100, 200, 400, 450, 550, 700, 800, 800, 850, 900,
										1050,1100,1200,1260,1380,1500,1600,1640, 1690,1700
								
								
								   };		//�G�̏o���t���[����

int g_nEnemySpawnLine[MAX_ENEMY_T]  = {     
										0,   1,   2,   1,   0,   2,   1,   0,   2,   1,
										0,	 1,	  2,   1,   0,   2,   1,   0,   2,   1
										
								    };		//�G�̏o�����C��


//int g_nOilSpawnFrame_T[MAX_OIL_T] = {50, 120,180,250,320};	//�I�C���̏o���t���[����
//int g_nOilSpawnLine[MAX_OIL_T]  = {1, 2, 1, 0, 2};		//�I�C���̏o�����C��

int g_nAcceleSpawnFrame_T[MAX_ACCELE_T] = {300,400, 600,880,1000,1100,1250,1330,1520,1600};	//�������̏o���t���[����
int g_nAcceleSpawnLine[MAX_ACCELE_T]  = {1, 2, 1, 0, 2, 1, 0, 0, 2, 1};			//�������̏o�����C��
int nCurrentFrame_T;	//���̃t���[����



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
			continue;		//�g�p�����玟�̃��[�v��
		
		//���g�p�̓G�����������ꍇ
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
			continue;		//�g�p�����玟�̃��[�v��
		
		//���g�p�̓G�����������ꍇ
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
	
	//----------�Ԃ̏�����
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		//�l������
		g_Car[nCntEnemy].fPosX      = 0.0f;
		g_Car[nCntEnemy].fPosY      = 0.0f;
		g_Car[nCntEnemy].fOldPosX   = 0.0f;
		g_Car[nCntEnemy].fOldPosY   = 0.0f;
		g_Car[nCntEnemy].fMoveX     = 0.0f;
		g_Car[nCntEnemy].fMoveY     = 0.0f;
		g_Car[nCntEnemy].bUse       = false;

		//�h�b�g�G�ǂݍ���
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




	//----------�������̏�����
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
	
	bool bCollisionEnemyFlg;//�v���C���[���G�ƐڐG�������ǂ����̃t���O
	float PlayerSpeed = GetPlayerSpeed_T();	//�v���C���[�̈ړ����x���擾
	nCurrentFrame_T = GetFrameData_T();	//���݂̃t���[�������擾
	bCollisionEnemyFlg = GetCollisionFlg_T();


	//==============�G�̏o��==============
	//-----��
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		//���Ԗڂ̓G���g���ĕ`�悷�邩�̌���
		if(g_Car[nCntEnemy].bUse)
			continue;										//���̓G�������Ă�����A���̓G���g�p�������肷��


		if(nCurrentFrame_T >= g_nEnemySpawnframe[nCntEnemy])
			CreateEnemy_T( g_nEnemySpawnLine[nCntEnemy] );	//�G����				�����g���G�̐����z�����΂������E�E�E

	}
	



	//-----������
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		//���Ԗڂ̉��������g���ĕ`�悷�邩�̌���
		if(g_Accele[nCntEnemy].bUse)
			continue;									//���̉������������Ă�����A���̉��������g�p�������肷��

		if(nCurrentFrame_T >= g_nAcceleSpawnFrame_T[nCntEnemy])
			CreateAccele_T( g_nAcceleSpawnLine[nCntEnemy] );	//����������

	}






	//===============�X�V==============
	//-----��
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		if(!g_Car[nCntEnemy].bUse)	//�g���ĂȂ��G�L�����̓A�b�v�f�[�g���Ȃ�
			continue;

		//=====���ݍ��W��ޔ�=====
		g_Car[nCntEnemy].fOldPosX = g_Car[nCntEnemy].fPosX;
		g_Car[nCntEnemy].fOldPosY = g_Car[nCntEnemy].fPosY;
	

		//=====�ړ��ʂ�������=====
		g_Car[nCntEnemy].fMoveX = 0.0f;
		g_Car[nCntEnemy].fMoveY = 0.0f;


		//=====�ړ��ʂ�ݒ�=====
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
		
		//=====���W�X�V=====
		g_Car[nCntEnemy].fPosX += g_Car[nCntEnemy].fMoveX;

	}


	

	//-----������
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		if(!g_Accele[nCntEnemy].bUse)	//�g���ĂȂ��G�L�����̓A�b�v�f�[�g���Ȃ�
			continue;

		//=====�ړ��ʂ�������=====
		g_Accele[nCntEnemy].fMoveX = MOVE_SIZE_T_NORMAL_T;


		//=====�ړ��ʂ�ݒ�=====		
		g_Accele[nCntEnemy].fMoveX -= PlayerSpeed;
		

		//=====���W�X�V=====
		g_Accele[nCntEnemy].fPosX += g_Accele[nCntEnemy].fMoveX;

	}


}


//�o�����C������inLine == 0�j�̓G�̕`��
void DrawBackEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	

	//-----������
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Accele[nCntEnemy].nLine != 0)
			continue;					//�o�����C�����ザ��Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�������`��
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}


	//-----��
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Car[nCntEnemy].nLine % 3 != 0)
			continue;					//�o�����C�����ザ��Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�G�`��
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')			//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
					continue;


				SetNextData_T( ((int)g_Car[nCntEnemy].fPosX + nX), ((int)g_Car[nCntEnemy].fPosY + nY), g_Car[nCntEnemy].szCarDot[nX + (nY * 24)]);
			}
		}
	}

}

//�o�����C�����^�񒆁inLine == 1�j�̓G�̕`��
void DrawMiddleEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	
	//-----������
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Accele[nCntEnemy].nLine != 1)
			continue;					//�o�����C�����^�񒆂���Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�������`��
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}

	//-----��
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Car[nCntEnemy].nLine % 3 != 1)
			continue;					//�o�����C�����^�񒆂���Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�G�`��
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')			//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
					continue;


				SetNextData_T( ((int)g_Car[nCntEnemy].fPosX + nX), ((int)g_Car[nCntEnemy].fPosY + nY), g_Car[nCntEnemy].szCarDot[nX + (nY * 24)]);
			}
		}
	}
	
}

//�o�����C�������inLine == 2�j�̓G�̕`��
void DrawFrontEnemy_T(void)
{
	int nCntEnemy;
	int nX;
	int nY;
	TPlayer_T *pPlayer = GetPlayerData_T();

	

	//-----������
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ACCELE_T ; nCntEnemy ++)
	{
		
		if(!g_Accele[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Accele[nCntEnemy].nLine != 2)
			continue;					//�o�����C����������Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�������`��
		for(nX = 0 ; nX < ACCELE_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ACCELE_HEIGHT_T ; nY ++)
			{
				if(g_Accele[0].szAcceleDot_1[nX + (nY * ACCELE_WIDTH_T)] == '^')			//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Accele[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Accele[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
					continue;


				SetNextData_T(((int)g_Accele[nCntEnemy].fPosX + nX),((int)g_Accele[nCntEnemy].fPosY + nY),g_Accele[nCntEnemy].szAcceleDot_1[nX+(nY*ACCELE_WIDTH_T)]);
			}
		}
	}

	//-----��
	for(nCntEnemy = 0 ; nCntEnemy < MAX_ENEMY_T ; nCntEnemy ++)
	{
		
		if(!g_Car[nCntEnemy].bUse)
			continue;					//���g�p�Ȃ玟�̃��[�v��

		if(g_Car[nCntEnemy].nLine % 3 != 2)
			continue;					//�o�����C����������Ȃ��G�́A�����ł͕`�悵�Ȃ�



		//-----�G�`��
		for(nX = 0 ; nX < ENEMY_CAR_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < ENEMY_CAR_HEIGHT_T ; nY ++)
			{
				if(g_Car[0].szCarDot[nX + (nY * 24)] == '^')		//�����Ȃ牽���`�悵�Ȃ�
					continue;
				
				if(((int)g_Car[nCntEnemy].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosX + nX) < 0)			//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_Car[nCntEnemy].fPosY + nY) >= 45)		//�K�[�h���[���̂Ƃ���͕`�悵�Ȃ�
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