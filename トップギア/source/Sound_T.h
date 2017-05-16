#ifndef __SOUND_T_H__
#define __SOUND_T_H__



#define BGMFILE "bgm.wav"
#define HITFILE "syoutotu.wav"
#define SPEEDUPFILE "kasoku.wav"


//�񋓌^�錾
typedef enum
{
	BGM_T,
	HIT_T,
	SPEEDUP_T
}SOUND_T;


typedef enum
{
	NOREPEAT_T,
	REPEAT_T,

}LOOP_T;



//-----�v���g�^�C�v�錾
void InitSound_T(void);
void StartSound_T(SOUND_T eKind_T, LOOP_T eLoop_T);
void StopSound_T(SOUND_T eKind_T);
void CloseSound_T();


#endif