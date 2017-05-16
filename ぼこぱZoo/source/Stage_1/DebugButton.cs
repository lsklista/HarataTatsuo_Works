using UnityEngine;
using System.Collections;

public class DebugButton : MonoBehaviour {


	public void OnTapWinButton()
	{
		switch (GameObject.Find("MAINLOOP").GetComponent<MainLoop>().GetStage())
		{
			case 1:
				ResultNextButton.SetClearStage(Fade.NEXTSCENE.STAGE_1);
				EnemyCatapult.SetClearStage(Fade.NEXTSCENE.STAGE_1);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.RESULR);
				break;
			case 2:
				ResultNextButton.SetClearStage(Fade.NEXTSCENE.STAGE_2);
				EnemyCatapult.SetClearStage(Fade.NEXTSCENE.STAGE_2);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.RESULR);
				break;
			case 3:
				ResultNextButton.SetClearStage(Fade.NEXTSCENE.STAGE_3);
				EnemyCatapult.SetClearStage(Fade.NEXTSCENE.STAGE_3);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.RESULR);
				break;
			case 4:
				ResultNextButton.SetClearStage(Fade.NEXTSCENE.STAGE_4);
				EnemyCatapult.SetClearStage(Fade.NEXTSCENE.STAGE_4);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.RESULR);
				break;
			case 5:
				ResultNextButton.SetClearStage(Fade.NEXTSCENE.STAGE_5);
				EnemyCatapult.SetClearStage(Fade.NEXTSCENE.STAGE_5);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.RESULR);
				break;
		}
	}

	public void OnTapLoseButton()
	{
		switch (GameObject.Find("MAINLOOP").GetComponent<MainLoop>().GetStage())
		{
			case 1:
				RetryButton.SetLoseStage(Fade.NEXTSCENE.STAGE_1);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.GAMEOVER);
				break;
			case 2:
				RetryButton.SetLoseStage(Fade.NEXTSCENE.STAGE_2);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.GAMEOVER);
				break;
			case 3:
				RetryButton.SetLoseStage(Fade.NEXTSCENE.STAGE_3);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.GAMEOVER);
				break;
			case 4:
				RetryButton.SetLoseStage(Fade.NEXTSCENE.STAGE_4);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.GAMEOVER);
				break;
			case 5:
				RetryButton.SetLoseStage(Fade.NEXTSCENE.STAGE_5);
				Sound.StopBgm();
				GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.GAMEOVER);
				break;
		}
	}
}
