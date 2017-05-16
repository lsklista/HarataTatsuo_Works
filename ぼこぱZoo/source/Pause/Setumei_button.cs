using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Setumei_button : MonoBehaviour {
	Setumei_window Setumei_window_cs;


	// Use this for initialization
	void Start () 
	{
		Setumei_window_cs = GameObject.Find("Setumei_window").GetComponent<Setumei_window>();
		
		GetComponent<Image> ().enabled = false;			// ステージセレクトボタンを描画しない
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}
	
	// 説明の左ボタンが押されたら呼ばれる
	public void OnTapLeftButton()
	{
		Setumei_window_cs.ChangeSub ();
	}
	
	// 説明の右ボタンが押されたら呼ばれる
	public void OnTapRightButton()
	{
		Setumei_window_cs.ChangeAdd ();
	}
	
	// 説明ボタンを描画
	public void DrawSetumei_button()
	{
		GetComponent<Image> ().enabled = true;
	}
	
	// 説明ボタンを描画しない
	public void UnDrawSetumei_button()
	{
		GetComponent<Image> ().enabled = false;
	}
}
