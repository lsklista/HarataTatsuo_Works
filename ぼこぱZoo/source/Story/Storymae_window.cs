using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Storymae_window : MonoBehaviour
{
	RectTransform recttransform;

	Image Img;
	public int nTexture;				// 今何枚目のテクスチャなのか
	public Texture2D Setumei_1;
	public Texture2D Setumei_2;
	public Texture2D Setumei_3;
	public Texture2D Setumei_4;
	public Texture2D Setumei_5;
	public Texture2D Setumei_6;
	public Texture2D Setumei_7;

	bool bSEPase;	// 1枚目の時に左押された時と, 最後のページの時に右押された時に, SEを鳴らさないようにするフラグ

	Storymae_circle circle_cs;
	UIFlush uiflush_cs;

	// Use this for initialization
	void Start()
	{
		recttransform = GetComponent<RectTransform>();
		Img = GetComponent<Image>();
		circle_cs = GameObject.Find("Story_circle").GetComponent<Storymae_circle>();
		uiflush_cs = GameObject.Find("Story_batu").GetComponent<UIFlush>();

		nTexture = 1;	// 最初は1枚目の説明を表示
		Img.sprite = Sprite.Create(Setumei_1, new Rect(0, 0, Setumei_1.width, Setumei_1.height), Vector2.zero);

		Sound.LoadBgm("BGM_mae", "BGM_mae");
		Sound.PlayBgm("BGM_mae");

		Sound.LoadSe("SE_Page", "SE_Page");
	}

	// 画像を１枚後のものに切り替える
	public void ChangeAdd()
	{
		nTexture++;
		bSEPase = true;

		if (nTexture == 8)
		{
			nTexture = 7;
			//GameObject.Find("tocyuuFade").GetComponent<tocyuuFade>().FadeStart();
			bSEPase = false;
		}

		// SEを鳴らす
		if (bSEPase)
			Sound.PlaySe("SE_Page");

		switch (nTexture)
		{
			case 1:
				Img.sprite = Sprite.Create(Setumei_1, new Rect(0, 0, Setumei_1.width, Setumei_1.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 2:
				Img.sprite = Sprite.Create(Setumei_2, new Rect(0, 0, Setumei_2.width, Setumei_2.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 3:
				Img.sprite = Sprite.Create(Setumei_3, new Rect(0, 0, Setumei_3.width, Setumei_3.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 4:
				Img.sprite = Sprite.Create(Setumei_4, new Rect(0, 0, Setumei_4.width, Setumei_4.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 5:
				Img.sprite = Sprite.Create(Setumei_5, new Rect(0, 0, Setumei_5.width, Setumei_5.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 6:
				Img.sprite = Sprite.Create(Setumei_6, new Rect(0, 0, Setumei_6.width, Setumei_6.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 7:
				Img.sprite = Sprite.Create(Setumei_7, new Rect(0, 0, Setumei_7.width, Setumei_7.height), Vector2.zero);
				uiflush_cs.StartFlush();	// 点滅開始
				break;
		}

		circle_cs.ChangeActive(nTexture);	// 丸変更
	}

	// 画像を１枚前のものに切り替える
	public void ChangeSub()
	{
		nTexture--;
		bSEPase = true;
		uiflush_cs.StopFlush();	// 点滅停止

		if (nTexture == 0)
		{
			nTexture = 1;
			bSEPase = false;
		}

		// SEを鳴らす
		if (bSEPase)
			Sound.PlaySe("SE_Page");

		switch (nTexture)
		{
			case 1:
				Img.sprite = Sprite.Create(Setumei_1, new Rect(0, 0, Setumei_1.width, Setumei_1.height), Vector2.zero);
				break;

			case 2:
				Img.sprite = Sprite.Create(Setumei_2, new Rect(0, 0, Setumei_2.width, Setumei_2.height), Vector2.zero);
				break;

			case 3:
				Img.sprite = Sprite.Create(Setumei_3, new Rect(0, 0, Setumei_3.width, Setumei_3.height), Vector2.zero);
				break;

			case 4:
				Img.sprite = Sprite.Create(Setumei_4, new Rect(0, 0, Setumei_4.width, Setumei_4.height), Vector2.zero);
				break;

			case 5:
				Img.sprite = Sprite.Create(Setumei_5, new Rect(0, 0, Setumei_5.width, Setumei_5.height), Vector2.zero);
				break;

			case 6:
				Img.sprite = Sprite.Create(Setumei_6, new Rect(0, 0, Setumei_6.width, Setumei_6.height), Vector2.zero);
				break;

			case 7:
				Img.sprite = Sprite.Create(Setumei_7, new Rect(0, 0, Setumei_7.width, Setumei_7.height), Vector2.zero);
				break;
		}

		circle_cs.ChangeActive(nTexture);	// 丸変更
	}
}
