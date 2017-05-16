﻿using UnityEngine;
using System.Collections;

public class ClearButton : MonoBehaviour {
	Fade Fade_cs;		//フェード用


	// Use this for initialization
	void Start ()
	{
		Fade_cs = GameObject.Find("Fade").GetComponent<Fade> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void onTapButton()
	{
		ResultNextButton.SetClearStage (Fade.NEXTSCENE.STAGE_1);	// 「次へボタン」に勝ったシーンを渡す
		Fade_cs.FadeStart(Fade.NEXTSCENE.RESULR);		// 遷移したいシーンを選択
	}
}
