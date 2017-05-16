using UnityEngine;
using System.Collections;

public class bg : MonoBehaviour {
	bool bProgress;
	float fTime;
	public float fFadeOutTime;
	float fAlpha;
	SpriteRenderer spriterenderer;

	public float StopFadeAlpha;

	// Use this for initialization
	void Start ()
	{
		bProgress = false;
		fTime = 0.0f;
		spriterenderer = GetComponent<SpriteRenderer>();
		spriterenderer.enabled = true;


		if (GameObject.Find ("MAINLOOP").GetComponent<MainLoop> ().GetStage () == 1)
		{
			fAlpha = 1.0f;
		}
		else
		{
			fAlpha = StopFadeAlpha;

			// スタートを走らせる
			//GameObject.Find("hamu_start").GetComponent<Hamu_start>().StartProgress();
		}
		spriterenderer.color = new Color (1.0f, 1.0f, 1.0f, fAlpha);
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (!bProgress)
			return;

		// フェードアウト処理
		fTime += Time.deltaTime;
		fAlpha = 1.0f - (fTime / fFadeOutTime);
		if (fAlpha <= StopFadeAlpha)
		{
			// スタートを走らせる
			GameObject.Find("hamu_start").GetComponent<Hamu_start>().StartProgress();

			// 処理をとめる
			bProgress = false;
		}

		spriterenderer.color = new Color (1.0f, 1.0f, 1.0f, fAlpha);
	}

	public void StartProgress()
	{
		bProgress = true;
	}

	// bgを消す
	public void Deletebg()
	{
		Destroy (this.gameObject);
	}
}
