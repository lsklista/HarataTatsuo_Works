using UnityEngine;
using System.Collections;

public class Storyato_button : MonoBehaviour
{
	Storyato_window Story_window_cs;


	// Use this for initialization
	void Start()
	{
		Story_window_cs = GameObject.Find("Story_window").GetComponent<Storyato_window>();
	}

	public void OnTapLeftButton()
	{
		Story_window_cs.ChangeSub();
	}

	public void OnTapRightButton()
	{
		Story_window_cs.ChangeAdd();
	}

	// ストーリーのバツが押されたら呼ばれる
	public void OnTapBatuButton()
	{
		// フェード中ならタップは無効
		if (GameObject.Find("Fade").GetComponent<Fade>().m_bFade)
			return;

		GameObject.Find("Fade").GetComponent<Fade>().FadeStart(Fade.NEXTSCENE.STAGESELECT);

		// ボタンがタップされた音を鳴らす
		Sound.PlaySe("SE_Enter");

		// ステセレシーンに, BGMは再生するように設定する
		Main_SS.SetPlayBGM(true);
	}
}
