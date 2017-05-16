using UnityEngine;
using System.Collections;

public class ResultBoss : MonoBehaviour {
	public GameObject PS;

	Vector2 fSpeed;		// 初速度
	float fGravity;		// 下方向にかかる加速度
	float fSubScale;	// 1ループあたりの拡大率の減少量
	float fBombTime;	// 爆発するまでの時間

	float fTime;

	// Use this for initialization
	void Start ()
	{
		fTime = 0.0f;
	}
	
	// Update is called once per frame
	void Update ()
	{
		fTime += 1.0f / 30.0f;
		// 時間経過により爆発
		if (fTime >= fBombTime)
		{
			// エフェクト発生
			PS.transform.position = transform.position;
			Instantiate(PS, transform.position, Quaternion.identity);

			Destroy (this.gameObject);
		}

		fSpeed.y -= fGravity;
		transform.position = new Vector3 (transform.position.x + fSpeed.x,
		                                  transform.position.y + fSpeed.y,
		                                  transform.position.z);

		transform.localScale = new Vector3 (transform.localScale.x - fSubScale,
		                                    transform.localScale.y - fSubScale,
		                                    transform.localScale.z);
	}
	
	// 移動速度などを設定
	// インスタンスが作られた瞬間に呼び出される
	public void SetSpeed(Vector2 speed, float gravity, float startscale, float finscale, float bombtime)
	{
		fSpeed = speed;
		fGravity = gravity;
		fBombTime = bombtime;

		// 初期拡大率に設定
		transform.localScale = new Vector3 (startscale, startscale, 1.0f);

		// ループあたりの拡大率の減少量を計算
		fSubScale = ((startscale - finscale) / bombtime) / 30.0f;
	}
}
