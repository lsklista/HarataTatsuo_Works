//////////////////////////////////////////////
//�t�@�C�����@�FBuffer.cpp
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�_�u���o�b�t�@�����邽�߂�cpp�t�@�C��
//////////////////////////////////////////////


//====================�C���N���[�h��
#include "CScreen.h"
#include "Buffer_T.h"
#include "Main_T.h"




//====================�}�N����`





//====================�v���g�^�C�v�錾




//==========�O���[�o���錾==========
char g_szNowDraw[MAX_DRAW_T];			//���`�悵�Ă�i�O�t���[���́j�t�B�[���h�f�[�^
char g_szNextDraw[MAX_DRAW_T];		//���ɕ`�悵�悤�Ƃ��Ă���t�B�[���h�f�[�^





void InitBuffer_T(void)
{
	//�ϐ��錾
	FILE *pFile_1;
	FILE *pFile_2;

	//�t�@�C���I�[�v��
	pFile_1 = fopen(ORIGINAL_FIELD_T, "r");
	pFile_2 = fopen(ORIGINAL_FIELD_T, "r");

	//�G���[����
	if(!pFile_1 || !pFile_2)
	{
		printf("�f�[�^���ǂݍ��߂܂���B");
		rewind(stdin);
		getchar();

		exit(EXIT_FAILURE);	//�����I��
	}

	//�t�@�C���ǂݍ���
	fscanf(pFile_1, "%s", g_szNextDraw);
	fscanf(pFile_2, "%s", g_szNowDraw);

	//�t�@�C���N���[�Y
	fclose(pFile_1);
	fclose(pFile_2);
}





void UpdateBuffer_T(void)
{
	
}





void DrawBuffer_T(void)
{
	//�ϐ��錾
	int nCntWidth;
	int nCntHeight;
	static bool bDrawInitialFlg = false;
	state_T NowState = GetState_T(); 

		//-----����`��
		if(!bDrawInitialFlg)
		{
			for( nCntHeight = 0 ; nCntHeight < MAX_DRAW_HEIGHT_T_T - 1 ; nCntHeight ++)
			{
				for( nCntWidth = 0; nCntWidth < MAX_DRAW_WIDTH_T ; nCntWidth ++)
				{
					//�}�b�v�`��
					if((g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0xF0) == 0x60)					//a�`f
						BACKCOLOR((g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09);
					else
						BACKCOLOR(g_szNowDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F);				//0�`9
					LOCATE(nCntWidth + 1 , nCntHeight + 1);
					printf(" ");

				}
			}
				bDrawInitialFlg = true;
		}
	


	//�`�揈��
	for( nCntHeight = 0 ; nCntHeight < MAX_DRAW_HEIGHT_T_T - 1 ; nCntHeight ++)
	{
		for( nCntWidth = 0; nCntWidth < MAX_DRAW_WIDTH_T ; nCntWidth ++)
		{
			//�F���ς���Ă��Ȃ������玟�̃��[�v��
			if( g_szNowDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)] == g_szNextDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)])
				continue;

			//�O�t���[���ƕς���Ă���Ƃ��낾���}�b�v�`��(�F�͕����R�[�h�Ŕ��f)
			if((g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0xF0) == 0x60)					//a�`f
				COLOR((g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09, (g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F) + 0x09);
			else
				COLOR(g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F, g_szNextDraw[ nCntWidth + (nCntHeight * 200) ] & 0x0F);		//0�`9
			LOCATE(nCntWidth + 1 , nCntHeight + 1);		//�`��ʒu
			printf("a");								//�`��

			//if(NowState != STATE_TITLE)
			//{
				//�����ς��Ă��܂����}�X�̏�������
				g_szNowDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)]  = g_szNextDraw[nCntWidth + (nCntHeight * MAX_DRAW_WIDTH_T)];
			//}

		}
	}

	//-----Next��Now�ɏ㏑������
	FILE *pFile;
	
	pFile = fopen(ORIGINAL_FIELD_T, "r");

	//�G���[����
	if(!pFile)
	{
		printf("�f�[�^���ǂݍ��߂܂���B");
		rewind(stdin);
		getchar();

		exit(EXIT_FAILURE);	//�����I��
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