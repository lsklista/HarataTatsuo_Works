using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Setumei_circle : MonoBehaviour {
	public Texture2D ActiveCircle;		// アクティブな時の丸
	public Texture2D NonActiveCircle;	// ノンアクティブな時の丸
	public float fCircleInterval;	// 丸と丸の間隔

	GameObject[]		CircleArray;
	Image[]				ImgArray;

	int nOldActiveNum;	// 前回アクティブだった丸の番号

	// Use this for initialization
	void Start ()
	{
		// 配列作成
		CircleArray = new GameObject[6];
		ImgArray = new Image[6];

		// オブジェクト・コンポーネント取得
		CircleArray = GameObject.FindGameObjectsWithTag("Setumei_circle");
		int i = 0;
		foreach(GameObject obj in CircleArray)
		{
			ImgArray[i] = obj.GetComponent<Image>();
			i ++;
		}

		// 子オブジェクトの座標初期化
		CircleArray [0].transform.localPosition = new Vector3(-2.5f * fCircleInterval, 0.0f, 0.0f);
		CircleArray [1].transform.localPosition = new Vector3(-1.5f * fCircleInterval, 0.0f, 0.0f);
		CircleArray [2].transform.localPosition = new Vector3(-0.5f * fCircleInterval, 0.0f, 0.0f);
		CircleArray [3].transform.localPosition = new Vector3( 0.5f * fCircleInterval, 0.0f, 0.0f);
		CircleArray [4].transform.localPosition = new Vector3( 1.5f * fCircleInterval, 0.0f, 0.0f);
		CircleArray [5].transform.localPosition = new Vector3( 2.5f * fCircleInterval, 0.0f, 0.0f);

		// 子オブジェクトのテクスチャ設定
		ImgArray [0].sprite = Sprite.Create(ActiveCircle, new Rect(0,0,ActiveCircle.width,
		                                                           ActiveCircle.height),Vector2.zero);
		ImgArray [1].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [2].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [3].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [4].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [5].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);

		nOldActiveNum = 1;	// アクティブなのは1個目の丸

		// 子オブジェクトを描画しないようにする
		foreach (Image img in ImgArray)
			img.enabled = false;
	}

	
	
	// 説明の丸を描画
	public void DrawSetumei_circle()
	{
		foreach (Image img in ImgArray)
			img.enabled = true;

		// 子オブジェクトのテクスチャ設定
		ImgArray [0].sprite = Sprite.Create(ActiveCircle, new Rect(0,0,ActiveCircle.width,
		                                                           ActiveCircle.height),Vector2.zero);
		ImgArray [1].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [2].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [3].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [4].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		ImgArray [5].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);
		nOldActiveNum = 1;	// アクティブなのは1個目の丸
	}
	
	// 説明の丸を描画しない
	public void UnDrawSetumei_circle()
	{
		foreach (Image img in ImgArray)
			img.enabled = false;
	}

	// アクティブな丸を変える(引数は, 新たにアクティブになった番号)
	public void ChangeActive(int num)
	{
		// 前回アクティブだった丸を, ノンアクティブにする
		ImgArray [nOldActiveNum-1].sprite = Sprite.Create(NonActiveCircle, new Rect(0,0,NonActiveCircle.width,
		                                                              NonActiveCircle.height),Vector2.zero);

		// ほかの丸をアクティブにする 	
		ImgArray [num-1].sprite = Sprite.Create(ActiveCircle, new Rect(0,0,ActiveCircle.width,
		                                                           ActiveCircle.height),Vector2.zero);

		// 前回アクティブだった丸の番号を切り替える
		nOldActiveNum = num;
	}
}
