//////////////////////////////////////////////
//�t�@�C�����@�FEnemy.h
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�G��h�t�@�C��
//////////////////////////////////////////////


#ifndef __ENEMY_H__
#define __ENEMY_H__

//==========�}�N����`
//-----�G�i�ԁj
#define MAX_ENEMY_T			   (    20)	//�G�̍ő吔
#define ENEMY_CAR_WIDTH_T		   (    24)	//�G�̉����i���p�j
#define ENEMY_CAR_HEIGHT_T	   (    10)	//�G�̏c��

//-----��Q���i�I�C���j
#define MAX_OIL_T				   (     5)	//�I�C���̍ő吔
#define OIL_HEIGHT_T			   (     8)	//�I�C���̉����i���p�j
#define OIL_WIDTH_T			   (    16)	//�I�C���̏c��

//-----��Q���i�������j
#define MAX_ACCELE_T			   (     10)	//�������̍ő吔
#define ACCELE_HEIGHT_T		   (     7)	//�������̏c��
#define ACCELE_WIDTH_T		   (    16)	//�������̏c���i���p�j





//-----�񋓌^�錾
typedef enum
{
	HIGH,
	MIDDLE,
	SLOW,
} eSpeed_T;



//-----�\���̐錾
typedef struct
{
	float fPosX,fPosY;				//�L�������W
	float fOldPosX,fOldPosY;		//�@�ߋ����W
	float fMoveX,fMoveY;			//�ړ���
	bool  bUse;						//�g�p�t���O
	int   nLine;					//�ǂ̃��C���Ȃ̂��i��O�A�^�񒆂P�A���Q�j
	char  szCarDot[ENEMY_CAR_HEIGHT_T * ENEMY_CAR_WIDTH_T + 1];	//�L�����N�^�[�̃h�b�g�G�p�̔z��
	eSpeed_T eColor;
} TEnemy_T;							//��



struct TAccelerator_T
{
	float fPosX, fPosY;
	float fMoveX;
	bool  bUse;
	int   nLine;
	char  szAcceleDot_1[ACCELE_WIDTH_T * ACCELE_HEIGHT_T + 1];
	char  szAcceleDot_2[ACCELE_WIDTH_T * ACCELE_HEIGHT_T + 1];
	char  szAcceleDot_3[ACCELE_WIDTH_T * ACCELE_HEIGHT_T + 1];
};


void InitEnemy_T(void);
void UpdateEnemy_T(void);
void DrawBackEnemy_T(void);
void DrawMiddleEnemy_T(void);
void DrawFrontEnemy_T(void);

TEnemy_T *GetEnemyData_T(void);
TAccelerator_T *GetAcceleData_T(void);

#endif