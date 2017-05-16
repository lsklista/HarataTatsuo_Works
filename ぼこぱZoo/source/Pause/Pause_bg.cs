using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Pause_bg : MonoBehaviour {
	public float fAlpha;		// ポーズ背景画像のアルファ値

	// Use this for initialization
	void Start ()
	{
		GetComponent<Image> ().color = new Color (0.0f, 0.0f, 0.0f, fAlpha);;	// アルファ値変更
		GetComponent<Image> ().enabled = false;									// ポーズ背景画像を描画しない
	}
	
	// ポーズ背景用画像を描画
	public void DrawPause_bg()
	{
		GetComponent<Image> ().enabled = true;
	}
	
	// ポーズ背景用画像を描画しない
	public void UnDrawPause_bg()
	{
		GetComponent<Image> ().enabled = false;
	}
}
