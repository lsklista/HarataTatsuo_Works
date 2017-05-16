using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Story_setuwindow : MonoBehaviour
{
	Image Img;
	int nTexture;				// 今何枚目のテクスチャなのか
	public Texture2D Setumei_1;
	public Texture2D Setumei_2;
	public Texture2D Setumei_3;
	public Texture2D Setumei_3to4;
	public Texture2D Setumei_4;
	public Texture2D Setumei_5;

	bool bSEPase;	// 1枚目の時に左押された時と, 最後のページの時に右押された時に, SEを鳴らさないようにするフラグ
	UIFlush uiflush_cs;

	// Use this for initialization
	void Start()
	{
		Img = GetComponent<Image>();
		uiflush_cs = GameObject.Find("Setumei_batu").GetComponent<UIFlush>();

		nTexture = 1;	// 最初は1枚目の説明を表示
		Img.sprite = Sprite.Create(Setumei_1, new Rect(0, 0, Setumei_1.width, Setumei_1.height), Vector2.zero);
	}

	// 画像を１枚前のものに切り替える
	public void ChangeSub()
	{
		nTexture--;
		bSEPase = true;	// ページ音を鳴らす
		uiflush_cs.StopFlush();	// 点滅停止

		if (nTexture == 0)
		{
			nTexture = 1;
			bSEPase = false;	// やっぱりページ音は鳴らさない
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
				Img.sprite = Sprite.Create(Setumei_3to4, new Rect(0, 0, Setumei_3to4.width, Setumei_3to4.height), Vector2.zero);
				break;

			case 5:
				Img.sprite = Sprite.Create(Setumei_4, new Rect(0, 0, Setumei_4.width, Setumei_4.height), Vector2.zero);
				break;

			case 6:
				Img.sprite = Sprite.Create(Setumei_5, new Rect(0, 0, Setumei_5.width, Setumei_5.height), Vector2.zero);
				break;
		}

		// 変わった画像に対応する丸をアクティブにする
		GameObject.Find("Setumei_circle").GetComponent<Story_setucircle>().ChangeActive(nTexture);
	}

	// 画像を１枚後のものに切り替える
	public void ChangeAdd()
	{
		nTexture++;
		bSEPase = true;	// ページ音を鳴らす

		if (nTexture == 7)
		{
			nTexture = 6;
			bSEPase = false;	// やっぱりページ音は鳴らさない
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
				Img.sprite = Sprite.Create(Setumei_3to4, new Rect(0, 0, Setumei_3to4.width, Setumei_3to4.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 5:
				Img.sprite = Sprite.Create(Setumei_4, new Rect(0, 0, Setumei_4.width, Setumei_4.height), Vector2.zero);
				uiflush_cs.StopFlush();	// 点滅停止
				break;

			case 6:
				Img.sprite = Sprite.Create(Setumei_5, new Rect(0, 0, Setumei_5.width, Setumei_5.height), Vector2.zero);
				uiflush_cs.StartFlush();	// 点滅開始
				break;
		}

		// 変わった画像に対応する丸をアクティブにする
		GameObject.Find("Setumei_circle").GetComponent<Story_setucircle>().ChangeActive(nTexture);
	}

	// 今何枚目の説明なのかを渡す(Setumei_Circle()で使う)
	public int GetSetumeiNum()
	{
		return nTexture;
	}
}
