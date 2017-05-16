using UnityEngine;
using System.Collections;

public class ten : MonoBehaviour {
	public float fLoadTime;		// ロードにかける時間
	public float fTenTime;		// 1個の点がついてから, 次の点が付くまでの時間
	int nTen;					// 今何個の点が付いているのか
	SpriteRenderer[] spriterenderer;
	float fTTime;	// 点用タイマー
	float fLTime;	// ロード用タイマー

	// Use this for initialization
	void Start ()
	{
		fLTime = 0.0f;
		fTTime = 0.0f;
		nTen = 0;

		spriterenderer = new SpriteRenderer[3];
		spriterenderer [0] = GameObject.Find ("ten1").GetComponent<SpriteRenderer>();
		spriterenderer [1] = GameObject.Find ("ten2").GetComponent<SpriteRenderer>();
		spriterenderer [2] = GameObject.Find ("ten3").GetComponent<SpriteRenderer>();

		for(int i = 0 ; i < 3 ; i ++)
			spriterenderer [i].enabled = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		fLTime += Time.deltaTime;
		if (fLTime >= fLoadTime)
		{
			if(GameObject.Find("MAINLOOP").GetComponent<MainLoop>().GetStage() == 1)
			{
				GameObject.Find("Setumei_gamen").GetComponent<Setumei_gamen>().StartSetumeigamen();
			}
			else
			{
				// スタートを走らせる
				GameObject.Find("hamu_start").GetComponent<Hamu_start>().StartProgress();
			}

			// ロード関係を全て削除する
			Destroy(GameObject.Find("LOAD"));
		}



		fTTime += Time.deltaTime;
		if (fTTime >= fTenTime)
		{
			fTTime = 0.0f;
			nTen ++;
			if(nTen == 4)
				nTen = 0;

			switch(nTen)
			{
			case 0:
				for(int i = 0 ; i < 3 ; i ++)
					spriterenderer [i].enabled = false;
				break;
				
			case 1:
				spriterenderer [0].enabled = true;
				break;
				
			case 2:
				spriterenderer [1].enabled = true;
				break;
				
			case 3:
				spriterenderer [2].enabled = true;
				break;
			}
		}
	}
}
