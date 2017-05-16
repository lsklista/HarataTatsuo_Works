//////////////////////////////////////////////
//ファイル名　：Buffer.h
//制作者　　　：原田達夫
//
//概要　　　　：ダブルバッファをするためのhファイル
//////////////////////////////////////////////


#ifndef __BUFFER_T_H__
#define __BUFFER_T_H__

#define MAX_DRAW_T				(10001)		//フィールドのマス数
#define MAX_DRAW_WIDTH_T		(200)		//フィールドの横幅
#define MAX_DRAW_HEIGHT_T_T		(50)		//フィールドの縦幅

//テキストファイルの名前
#define ORIGINAL_FIELD_T "map_1.txt"			//元となるマップのテキストファイルの名前


void InitBuffer_T(void);
void UpdateBuffer_T(void);
void DrawBuffer_T(void);

void SetNextData_T(int, int, char);
char *GetNowDrawData_T(void);
char *GetNextDrawData_T(void);


#endif