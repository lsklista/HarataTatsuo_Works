//////////////////////////////////////////////
//�t�@�C�����@�FBuffer.h
//����ҁ@�@�@�F���c�B�v
//
//�T�v�@�@�@�@�F�_�u���o�b�t�@�����邽�߂�h�t�@�C��
//////////////////////////////////////////////


#ifndef __BUFFER_T_H__
#define __BUFFER_T_H__

#define MAX_DRAW_T				(10001)		//�t�B�[���h�̃}�X��
#define MAX_DRAW_WIDTH_T		(200)		//�t�B�[���h�̉���
#define MAX_DRAW_HEIGHT_T_T		(50)		//�t�B�[���h�̏c��

//�e�L�X�g�t�@�C���̖��O
#define ORIGINAL_FIELD_T "map_1.txt"			//���ƂȂ�}�b�v�̃e�L�X�g�t�@�C���̖��O


void InitBuffer_T(void);
void UpdateBuffer_T(void);
void DrawBuffer_T(void);

void SetNextData_T(int, int, char);
char *GetNowDrawData_T(void);
char *GetNextDrawData_T(void);


#endif