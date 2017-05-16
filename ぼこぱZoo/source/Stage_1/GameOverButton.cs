using UnityEngine;
using System.Collections;

public class GameOverButton : MonoBehaviour {
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
		RetryButton.SetLoseStage (Fade.NEXTSCENE.STAGE_1);	// ゲームオーバーに, 負けたシーンを渡す
		Fade_cs.FadeStart(Fade.NEXTSCENE.GAMEOVER);			// 遷移したいシーンを選択
	}
}
