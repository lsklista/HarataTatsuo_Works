//////////////////////////////////////////////
//�t�@�C�����@�FTitle.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�^�C�g����cpp�t�@�C��
//////////////////////////////////////////////


//====================�C���N���[�h��
#include "CScreen.h"
#include "Buffer_T.h"
#include "Main_T.h"
#include "Player_T.h"




//====================�}�N����`
//#define MAX_DRAW			(10001)		//�t�B�[���h�̃}�X��
//#define MAX_DRAW_WIDTH		(200)		//�t�B�[���h�̉���
//#define MAX_DRAW_HEIGHT_T		(50)		//�t�B�[���h�̏c��


//====================�v���g�^�C�v�錾




//==========�O���[�o���錾==========
char g_szResultMap_T[122 * 35 + 1];	//�Q�[���I�[�o�[



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