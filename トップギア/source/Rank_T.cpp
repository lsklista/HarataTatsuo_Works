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

//====================�v���g�^�C�v�錾




//==========�O���[�o���錾==========
char g_szRankA_T[122 * 35 + 1];		//�`�����N
char g_szRankB_T[122 * 35 + 1];		//�a�����N
char g_szRankC_T[122 * 35 + 1];		//�b�����N
char g_szRankD_T[122 * 35 + 1];		//�c�����N



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
	float fMileage = Getg_fMileageData_T();	//���s�������擾


	if(fMileage > 10000.0f)														//�����N�`
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankA_T[nX + nY * 122]);
	}
	else if(fMileage > 5000.0f)													//�����N�a
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankB_T[nX + nY * 122]);
	}
	else if(fMileage > 1000.0f)													//�����N�b
	{
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankC_T[nX + nY * 122]);
	}
	else																		//�����N�c
		for(nY = 0 ; nY < 35 ; nY ++)
			for(nX = 0 ; nX < 122 ; nX ++)
				SetNextData_T(39 + nX, 3 + nY, g_szRankD_T[nX + nY * 122]);
	

}	