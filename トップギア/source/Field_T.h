//////////////////////////////////////////////
//ファイル名　：Field.h
//制作者　　　：原田達夫
//
//概要　　　　：フィールド（道路、家など）のhファイル
//////////////////////////////////////////////


#ifndef __FIELD_H__
#define __FIELD_H__


#define MOVE_SIZE_T_NORMAL_T		(0.0f)



void InitField_T(void);
void UpdateField_T(void);
void DrawBackField_T(void);
void DrawFrontField_T(void);

#endif