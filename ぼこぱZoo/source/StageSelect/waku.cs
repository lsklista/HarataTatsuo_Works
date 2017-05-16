using UnityEngine;
using System.Collections;

public class waku : MonoBehaviour
{
	Fade Fade_cs;		//フェード用
	SpriteRenderer sp;

	public int StageNumber;

	// Use this for initialization
	void Start ()
	{
		Fade_cs = GameObject.Find ("Fade").GetComponent<Fade> ();
		StageNumber = 0;
		sp = GetComponent<SpriteRenderer> ();
		Color color = sp.color;
		color.a = 0;
		sp.color = color;
		Sound.LoadBgm ("Stage_BOSS", "LastStage_BGM");
		Sound.LoadSe ("SE_Enter2", "SE_Enter2");
	}
	
	// Update is called once per frame
	void Update ()
	{
		switch (StageNumber)
		{
		case 0:
			break;
		case 1:
			MainLoop.SetStage(1);
			Sound.StopBgm ();
			Fade_cs.FadeStart(Fade.NEXTSCENE.STAGE_1);
			break;
		case 2:
			MainLoop.SetStage(2);
			Sound.StopBgm ();
			Fade_cs.FadeStart(Fade.NEXTSCENE.STAGE_2);
			break;
		case 3:
			MainLoop.SetStage(3);
			Sound.StopBgm ();
			Fade_cs.FadeStart(Fade.NEXTSCENE.STAGE_3);
			break;
		case 4:
			MainLoop.SetStage(4);
			Sound.StopBgm ();
			Fade_cs.FadeStart(Fade.NEXTSCENE.STAGE_4);
			break;
		case 5:
			MainLoop.SetStage(5);
			Sound.StopBgm ();
			Fade_cs.FadeStart(Fade.NEXTSCENE.STAGE_5);
			break;
		}
	}

	public void WakuFade(){
		Color color = sp.color;
		color.a += 0.075f;
		sp.color = color;
	}

	public void AlfaOn(){
		Color color = sp.color;
		color.a = 1;
		sp.color = color;
	}

	// 枠にはめられたステージの番号を設定する
	public void SetStageNumber(int number)
	{
		StageNumber = number;
		Sound.PlaySe ("SE_Enter2");
	}
}
