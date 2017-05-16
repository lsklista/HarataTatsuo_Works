using UnityEngine;
using System.Collections;

public class Hamu_start : MonoBehaviour {
	public float fStartPosX;		// 移動開始のX座標
	public float fDeletePosX;		// 消去判定を行うためのX座標
	public float fSpeed;			// 移動速度
	float fPosX;					// 現在のX座標(計算用)
	bool bProgress;					// 処理を開始していいかのフラグ



	// Use this for initialization
	void Start ()
	{
		bProgress = false;

		// 座標初期化
		transform.position = new Vector3 (fStartPosX, transform.position.y, transform.position.z);
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (!bProgress)
			return;

		fPosX = transform.position.x - fSpeed;
		if (fPosX <= fDeletePosX)
		{
			GameObject.Find("bg").GetComponent<bg>().Deletebg();	// bgを消す
			GameObject.Find("MAINLOOP").GetComponent<MainLoop>().GameStart();	// MAINLOOPの処理を開始する
			GameObject.Find("PuzzleMain").GetComponent<PuzzleMain>().StartPuzzleMain();

			// 自身を消去
			Destroy(this.gameObject);
		}

		transform.position = new Vector3 (fPosX, transform.position.y, transform.position.z);
	}

	// 処理を開始してよくなったら呼ばれる
	public void StartProgress()
	{
		bProgress = true;

		Sound.PlaySe ("Start");
	}
}
