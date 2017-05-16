//////////////////////////////////////////////
//�t�@�C�����@�FField.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�t�B�[���h�i���H�A�ƂȂǁj��cpp�t�@�C��
//////////////////////////////////////////////


//====================�C���N���[�h��
#include "CScreen.h"
#include "Buffer_T.h"
#include "Player_T.h"
#include "Field_T.h"




//====================�}�N����`
#define MAX_WHITELINE_T			(6)
#define MAX_GUARDRAIL_T			(12)


#define GUARDRAIL_WIDTH_T			(6)
#define GUARDRAIL_HEIGHT_T		(4)


//-----�\���̐錾
struct TWhiteLine_T				//���H�̔���
{
	float fPosX, fPosY;
	float fMoveX;
	char  szWhiteLine[41];
};

struct TGuardRail_T				//�K�[�h���[��
{
	float fPosX, fPosY;
	float fMoveX;
	char  szGuardRail[25];
};







//====================�v���g�^�C�v�錾




//==========�O���[�o���錾==========
TWhiteLine_T g_WhiteLine_T[MAX_WHITELINE_T];
TGuardRail_T g_GuardRail_T[MAX_GUARDRAIL_T];




void InitField_T(void)
{
	//==========���H�̔����̏�����
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

	//�h�b�g�G�ǂݍ���
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		pFile = fopen("white_line.txt", "r");
		fscanf(pFile,"%s", g_WhiteLine_T[nCntField].szWhiteLine);	
		fclose(pFile);
	}




	//==========�K�[�h���[���̏�����
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		//�w���W
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

		//�x���W
		if(nCntField % 2 == 0)
			g_GuardRail_T[nCntField].fPosY = 9.0f;
		else
			g_GuardRail_T[nCntField].fPosY = 44.0f;


		//�ړ���
		g_GuardRail_T[nCntField].fMoveX = 0.0f;

		//�h�b�g�G�ǂݍ���
		pFile = fopen("guardrail.txt", "r");
		fscanf(pFile,"%s", g_GuardRail_T[nCntField].szGuardRail);	
		fclose(pFile);

	}
}


void UpdateField_T(void)
{
	int nCntField;
	float PlayerSpeed = GetPlayerSpeed_T();	//�v���C���[�̈ړ����x���擾
	

	//==========���H�̔����̃A�b�v�f�[�g
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		//=====�ړ��ʂ�������=====
		g_WhiteLine_T[nCntField].fMoveX = MOVE_SIZE_T_NORMAL_T;
		
		//=====�ړ��ʂ�ݒ�=====
		g_WhiteLine_T[nCntField].fMoveX -= PlayerSpeed;


		//=====���W�X�V=====
		g_WhiteLine_T[nCntField].fPosX += g_WhiteLine_T[nCntField].fMoveX;


		//���W�␳�E�E�E�w���W��-100��������E�ɖ߂�
		if(g_WhiteLine_T[nCntField].fPosX < -100)
		{
			g_WhiteLine_T[nCntField].fPosX += 300;
		}
	}



	//==========�K�[�h���[���̃A�b�v�f�[�g
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		//=====�ړ��ʂ�������=====
		g_GuardRail_T[nCntField].fMoveX = MOVE_SIZE_T_NORMAL_T;
		
		//=====�ړ��ʂ�ݒ�=====
		g_GuardRail_T[nCntField].fMoveX -= PlayerSpeed;


		//=====���W�X�V=====
		g_GuardRail_T[nCntField].fPosX += g_GuardRail_T[nCntField].fMoveX;


		//���W�␳�E�E�E�w���W��-40��������E�ɖ߂�
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


	//==========���H�̔���
	for(nCntField = 0 ; nCntField < MAX_WHITELINE_T ; nCntField ++)
	{
		for(nX = 0 ; nX < 40 ; nX ++)
		{
			if(((int)g_WhiteLine_T[nCntField].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
				continue;

			if(((int)g_WhiteLine_T[nCntField].fPosX + nX) < 0)		//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
				continue;

			//�`�悷��
			SetNextData_T( ((int)g_WhiteLine_T[nCntField].fPosX + nX), ((int)g_WhiteLine_T[nCntField].fPosY), g_WhiteLine_T[nCntField].szWhiteLine[nX]);
		}
	}


	//==========�K�[�h���[���i���j
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		if(nCntField % 2 != 0)			//��O�̃K�[�h���[���Ȃ�`�悵�Ȃ�
			continue;


		for(nX = 0 ; nX < GUARDRAIL_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < GUARDRAIL_HEIGHT_T ; nY ++)
			{
				if(((int)g_GuardRail_T[nCntField].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_GuardRail_T[nCntField].fPosX + nX) < 0)		//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					break;

				//�`�悷��
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

	

	//==========�K�[�h���[���i��O�j
	for(nCntField = 0 ; nCntField < MAX_GUARDRAIL_T ; nCntField ++)
	{
		if(nCntField % 2 == 0)		//���̃K�[�h���[���Ȃ�`�悵�Ȃ�
			continue;


		for(nX = 0 ; nX < GUARDRAIL_WIDTH_T ; nX ++)
		{
			for(nY = 0 ; nY < GUARDRAIL_HEIGHT_T ; nY ++)
			{
				if(((int)g_GuardRail_T[nCntField].fPosX + nX) >= 200)		//�w���W���Q�O�O�𒴂��Ă���ꍇ�A�`�悵�Ȃ�
					continue;

				if(((int)g_GuardRail_T[nCntField].fPosX + nX) < 0)		//�w���W���O�ȉ��̏ꍇ�A�`�悵�Ȃ�
					break;

				//�`�悷��
				SetNextData_T( ((int)g_GuardRail_T[nCntField].fPosX + nX),
							 ((int)g_GuardRail_T[nCntField].fPosY + nY),
							 g_GuardRail_T[nCntField].szGuardRail[nX + (nY * GUARDRAIL_WIDTH_T)]
						   );
			}
		}
	}
}