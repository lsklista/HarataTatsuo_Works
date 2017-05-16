//////////////////////////////////////////////
//ファイル名　：Player.h
//制作者　　　：原田達夫
//
//概要　　　　：プレイヤーのhファイル
//////////////////////////////////////////////


#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_FIGURE_T			   (     4)		//右上に表示する走行距離の桁数
#define NUMBER_WIDTH_T		   ( 8)//(半角)
#define NUMBER_HEIGHT_T		   ( 5)
#define METER_WIDTH_T		   (12)//(半角)
#define METER_HEIGHT_T		   ( 3)


//-----構造体宣言
typedef struct
{
	float fPosX,fPosY;				//キャラ座標
	float fOldPosX,fOldPosY;		//　過去座標
	float fMoveX,fMoveY;			//移動量
	int   nHp;						//ＨＰ（０になるとゲームオーバー）
	bool  bNoHitTime;				//車と当った後の、無敵状態のフラグ
	char  szPlayer_1[300];			//色情報を格納している配列
	char  szPlayer_2[300];			//色情報を格納している配列
	char  szPlayer_3[300];			//色情報を格納している配列
	char  szPlayer_4[300];			//色情報を格納している配列
} TPlayer_T;



void InitPlayer_T(void);
void UpdatePlayer_T(void);
void DrawPlayer_T(void);


TPlayer_T *GetPlayerData_T(void);
float GetPlayerSpeed_T(void);
bool GetCollisionFlg_T(void);
float Getg_fMileageData_T(void);		//←新しく追加
char *Getg_szMeterData_T(void);			//←新しく追加
char *Getg_szNumber(void);				//←新しく追加


#endif