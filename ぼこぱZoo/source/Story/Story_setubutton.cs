using UnityEngine;
using System.Collections;

public class Story_setubutton : MonoBehaviour
{
	Story_setuwindow Setumei_window_cs;

	// Use this for initialization
	void Start()
	{
		if (GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
			return;

		Setumei_window_cs = GameObject.Find("Setumei_window").GetComponent<Story_setuwindow>();
	}

	// 説明の左ボタンが押されたら呼ばれる
	public void OnTapLeftButton()
	{
		if (GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
			return;

		Setumei_window_cs.ChangeSub();
	}

	// 説明の右ボタンが押されたら呼ばれる
	public void OnTapRightButton()
	{
		Setumei_window_cs.ChangeAdd();
	}

	// ばつボタンが押されたら呼ばれる
	public void OnTapBatuButton()
	{
		Sound.PlaySe("SE_Enter");

		GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGESELECT);
	}
}
