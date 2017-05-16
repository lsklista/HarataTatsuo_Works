//////////////////////////////////////////////
//ファイル名　：Enemy.h
//制作者　　　：原田達夫
//
//概要　　　　：敵のhファイル
//////////////////////////////////////////////


#ifndef __ENEMY_H__
#define __ENEMY_H__

//==========マクロ定義
//-----敵（車）
#define MAX_ENEMY_T			   (    20)	//敵の最大数
#define ENEMY_CAR_WIDTH_T		   (    24)	//敵の横幅（半角）
#define ENEMY_CAR_HEIGHT_T	   (    10)	//敵の縦幅

//-----障害物（オイル）
#define MAX_OIL_T				   (     5)	//オイルの最大数
#define OIL_HEIGHT_T			   (     8)	//オイルの横幅（半角）
#define OIL_WIDTH_T			   (    16)	//オイルの縦幅

//-----障害物（加速床）
#define MAX_ACCELE_T			   (     10)	//加速床の最大数
#define ACCELE_HEIGHT_T		   (     7)	//加速床の縦幅
#define ACCELE_WIDTH_T		   (    16)	//加速床の縦幅（半角）





//-----列挙型宣言
typedef enum
{
	HIGH,
	MIDDLE,
	SLOW,
} eSpeed_T;



//-----構造体宣言
typedef struct
{
	float fPosX,fPosY;				//キャラ座標
	float fOldPosX,fOldPosY;		//　過去座標
	float fMoveX,fMoveY;			//移動量
	bool  bUse;						//使用フラグ
	int   nLine;					//どのラインなのか（上０、真ん中１、下２）
	char  szCarDot[ENEMY_CAR_HEIGHT_T * ENEMY_CAR_WIDTH_T + 1];	//キャラクターのドット絵用の配列
	eSpeed_T eColor;
} TEnemy_T;							//車



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