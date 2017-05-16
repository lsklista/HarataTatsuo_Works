using UnityEngine;
using System.Collections;

public class Start_jump : MonoBehaviour {
	public float fStartPos;			// 落下し始める座標
	public float fGravity;			// 重力加速度
	public float fBoundPos;			// どこを跳ね返り地点とするかのY座標
	float fSpeed;					// 現在の速度
	float fPosY;					// 座標計算用

	public float fStartProgressPos;	// 落下を開始する座標(X)
	bool bProgress;


	// Use this for initialization
	void Start ()
	{
		fSpeed = 0;
		transform.position = new Vector3 (transform.position.x, fStartPos, 0.0f);	// 座標初期化

		bProgress = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (transform.position.x <= fStartProgressPos)
			bProgress = true;

		if (!bProgress)
			return;

		fSpeed += fGravity;
		fPosY = transform.position.y + fSpeed;

		// 跳ね返り時判定
		if(fPosY <= fBoundPos)
		{
			fSpeed *= -1;				// スピード跳ね返り
			fPosY = fBoundPos;			// 座標をバウンドする座標にする
		}

		// 座標変更
		transform.position = new Vector3(transform.position.x, fPosY, transform.position.z);
	}
}
