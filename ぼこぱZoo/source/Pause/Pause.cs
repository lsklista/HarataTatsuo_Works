using UnityEngine;
using System.Collections;

public class Pause : MonoBehaviour {
	public bool m_bPause;		// ポーズ中ならtrue

	MainLoop 			MainLoop_cs;
	Pause_bg 			Pause_bg_cs;
	Pause_window		Pause_window_cs;
	Pause_back			Pause_back_cs;
	Pause_stageselect	Pause_stageselect_cs;
	Pause_tabu			Pause_tabu_cs;
	Setumei_tabu		Setumei_tabu_cs;
	Setumei_window		Setumei_window_cs;
	Pause_retry			Pause_retry_cs;

	// Use this for initialization
	void Start ()
	{
		m_bPause = false;

		MainLoop_cs = GameObject.Find("MAINLOOP").GetComponent<MainLoop>();
		Pause_bg_cs = GameObject.Find("Pause_bg").GetComponent<Pause_bg>();
		Pause_window_cs = GameObject.Find("Pause_window").GetComponent<Pause_window>();
		Pause_back_cs = GameObject.Find("Pause_back").GetComponent<Pause_back>();
		Pause_stageselect_cs = GameObject.Find("Pause_stageselect").GetComponent<Pause_stageselect>();
		Pause_tabu_cs = GameObject.Find("Pause_tabu").GetComponent<Pause_tabu>();
		Setumei_tabu_cs = GameObject.Find("Setumei_tabu").GetComponent<Setumei_tabu>();
		Setumei_window_cs = GameObject.Find("Setumei_window").GetComponent<Setumei_window>();
		Pause_retry_cs = GameObject.Find("Pause_retry").GetComponent<Pause_retry>();
	}
	
	// Update is called once per frame
	public void Up ()
	{
		Pause_window_cs.Up ();
		Setumei_window_cs.Up ();

		// ポーズウィンドウが移動していなければ、ボタンを更新する
		if (!Pause_window_cs.m_bMove)
		{
			Pause_back_cs.Up();
			Pause_stageselect_cs.Up();
		}
	}

	// ポーズ状態が変更されたときの処理
	public void ChangePause()
	{
		if (m_bPause)
		{// ポーズ解除
			Pause_window_cs.UnDrawPause_window();	// ウィンドウ終了処理開始
			Setumei_window_cs.UnDrawSetumei_window();	// 説明ウィンドウ非表示
		}
		else
		{// ポーズ開始
			m_bPause = true;						// ポーズ開始
			Pause_bg_cs.DrawPause_bg();				// 背景画像表示
			Pause_window_cs.DrawPause_window();		// ウィンドウ描画処理開始
			Pause_back_cs.DrawPause_back();			// バックボタン表示
			Pause_stageselect_cs.DrawPause_stageselect();	// ステージセレクトボタン表示
			Pause_tabu_cs.DrawPause_tabu();			// タブ1を表示
			Setumei_tabu_cs.DrawSetumei_tabu();		// タブ2を表示
			Setumei_window_cs.DrawSetumei_window();	// 説明ウィンドウ表示
			Pause_retry_cs.DrawPause_retry();		// リトライボタンを表示

			// ポーズ状態が変更されたのでスクリプトを操作する
			MainLoop_cs.ChangePause ();

			// アニメーションを止めるため, タイムを0にする
			Time.timeScale = 0;
		}
	}

	// ポーズウィンドウのスライドアウトが終了したので、ほかの処理をいろいろする
	public void PauseEnd()
	{
		m_bPause = false;						// ポーズ終了
		Pause_bg_cs.UnDrawPause_bg();			// 背景画像非表示
		Pause_back_cs.UnDrawPause_back();		// バックボタン非表示
		Pause_stageselect_cs.UnDrawPause_stageselect();	// ステージセレクトボタン非表示
		Pause_tabu_cs.UnDrawPause_tabu ();		// タブ1非表示
		Setumei_tabu_cs.UnDrawSetumei_tabu ();	// タブ2非表示
		Pause_retry_cs.UnDrawPause_retry();		// リトライボタンを非表示


		// ポーズ状態が変更されたのでスクリプトを操作する
		MainLoop_cs.ChangePause ();
		
		// アニメーションを動かすため, タイムを1にする
		Time.timeScale = 1;
	}
}
