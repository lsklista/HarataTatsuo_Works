#ifndef __MAIN_H__
#define __MAIN_H__



//-----�񋓌^�錾
typedef enum
{
	STATE_TITLE_T,
	STATE_GAME_T,
	STATE_RESULT_T,
} state_T;


//-----�v���g�^�C�v�錾
void SetState_T(state_T);
state_T GetState_T(void);
int GetFrameData_T(void);
void SetFrameData_T(int);


#endif