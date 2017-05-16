using UnityEngine;
using System.Collections;

public class Pause_pause : MonoBehaviour {

	// Use this for initialization
	void Start ()
	{
		Sound.LoadSe ("SE_Menu", "SE_Menu");
	}
	
	// Update is called once per frame
	void Update ()
	{
		
	}

	// ポーズボタンがタップされたときに呼び出される
	public void OnTapButton()
	{
		// まだゲームが開始していなかったら処理をしない
		if (!GameObject.Find ("MAINLOOP").GetComponent<MainLoop> ().GetGameStart ())
			return;

		// ボタンがタップされた音を鳴らす
		Sound.PlaySe ("SE_Menu");

		GameObject.Find ("Pause").GetComponent<Pause>().ChangePause();
	}
}
