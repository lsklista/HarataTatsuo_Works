using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Pause_tabu : MonoBehaviour {
	Pause_window	Pause_window_cs;
	Setumei_window	Setumei_window_cs;

	public Texture2D ActiveTexture;
	public Texture2D NonActiveTexture;


	// Use this for initialization
	void Start ()
	{
		Pause_window_cs = GameObject.Find("Pause_window").GetComponent<Pause_window>();
		Setumei_window_cs = GameObject.Find("Setumei_window").GetComponent<Setumei_window>();

		// 画像をアクティブに変える
		GetComponent<Image> ().sprite =
			Sprite.Create(ActiveTexture,new Rect(0,0,ActiveTexture.width,ActiveTexture.height),Vector2.zero);

		GetComponent<Image> ().enabled = false;			// ステージセレクトボタンを描画しない
	}
	
	// タブ1ボタンが押されたときに呼び出される
	public void OnTaptabu1()
	{
		Sound.PlaySe ("Click");

		Pause_window_cs.Active ();
		Setumei_window_cs.NonActive ();
		
		// 画像をアクティブに変える
		GetComponent<Image> ().sprite =
			Sprite.Create(ActiveTexture,new Rect(0,0,ActiveTexture.width,ActiveTexture.height),Vector2.zero);
	}
	
	// タブ2ボタンが押されたときに呼び出される
	public void OnTaptabu2()
	{
		Sound.PlaySe ("Click");

		// 画像をノンアクティブに変える
		GetComponent<Image> ().sprite = Sprite.Create(NonActiveTexture,new Rect(0,0,
		                                    NonActiveTexture.width,NonActiveTexture.height),Vector2.zero);
	}
	
	// ステージセレクトボタンを描画
	public void DrawPause_tabu()
	{
		GetComponent<Image> ().enabled = true;
	}
	
	// ステージセレクトボタンを描画しない
	public void UnDrawPause_tabu()
	{
		GetComponent<Image> ().enabled = false;
	}
}
