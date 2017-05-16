//////////////////////////////////////////////
//�t�@�C�����@�FPlayer.h
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�v���C���[��h�t�@�C��
//////////////////////////////////////////////


#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_FIGURE_T			   (     4)		//�E��ɕ\�����鑖�s�����̌���
#define NUMBER_WIDTH_T		   ( 8)//(���p)
#define NUMBER_HEIGHT_T		   ( 5)
#define METER_WIDTH_T		   (12)//(���p)
#define METER_HEIGHT_T		   ( 3)


//-----�\���̐錾
typedef struct
{
	float fPosX,fPosY;				//�L�������W
	float fOldPosX,fOldPosY;		//�@�ߋ����W
	float fMoveX,fMoveY;			//�ړ���
	int   nHp;						//�g�o�i�O�ɂȂ�ƃQ�[���I�[�o�[�j
	bool  bNoHitTime;				//�ԂƓ�������́A���G��Ԃ̃t���O
	char  szPlayer_1[300];			//�F�����i�[���Ă���z��
	char  szPlayer_2[300];			//�F�����i�[���Ă���z��
	char  szPlayer_3[300];			//�F�����i�[���Ă���z��
	char  szPlayer_4[300];			//�F�����i�[���Ă���z��
} TPlayer_T;



void InitPlayer_T(void);
void UpdatePlayer_T(void);
void DrawPlayer_T(void);


TPlayer_T *GetPlayerData_T(void);
float GetPlayerSpeed_T(void);
bool GetCollisionFlg_T(void);
float Getg_fMileageData_T(void);		//���V�����ǉ�
char *Getg_szMeterData_T(void);			//���V�����ǉ�
char *Getg_szNumber(void);				//���V�����ǉ�


#endif