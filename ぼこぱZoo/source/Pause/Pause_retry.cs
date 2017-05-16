using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Pause_retry : MonoBehaviour {

	// Use this for initialization
	void Start ()
	{
		GetComponent<Image> ().enabled = false;
	}
	
	public void OnTapButton()
	{
		// ポーズウィンドウが移動中ならタップは無効
		if (GameObject.Find ("Pause_window").GetComponent<Pause_window> ().m_bMove)
			return;
		
		// フェード中ならタップは無効
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;
		
		// ボタンがタップされた音を鳴らす
		Sound.PlaySe ("SE_Enter");
		
		// アニメーションをするために, タイムスケールを1に戻す
		Time.timeScale = 1;

		// リトライするために, 今のシーンを読み込む
		switch(GameObject.Find("MAINLOOP").GetComponent<MainLoop>().GetStage())
		{
		case 1:
			GameObject.Find ("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGE_1);
			break;
		case 2:
			GameObject.Find ("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGE_2);
			break;
		case 3:
			GameObject.Find ("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGE_3);
			break;
		case 4:
			GameObject.Find ("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGE_4);
			break;
		case 5:
			GameObject.Find ("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGE_5);
			break;
		}
	}
	
	// リトライボタンを描画
	public void DrawPause_retry()
	{
		GetComponent<Image> ().enabled = true;
	}
	
	// リトライボタンを描画しない
	public void UnDrawPause_retry()
	{
		GetComponent<Image> ().enabled = false;
	}
}
