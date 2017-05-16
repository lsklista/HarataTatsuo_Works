using UnityEngine;
using System.Collections;

public class Dokoiku : MonoBehaviour {
	float fRadian;						// 今のラジアン値
	public float fOneLoopTime;			// 1波長動くのにかかる時間
	float fAddradian;					// 1ループで加算されるラジアン値
	public float fAmplitude;			// 振幅 
	float fHeni;						// 変位(計算用)

	SpriteRenderer sp;


	// Use this for initialization
	void Start ()
	{
		fRadian = Mathf.PI;//0.0f;			// ラジアン値初期化
		fAddradian = (Mathf.PI * 2.0f / fOneLoopTime) / 30.0f;	// 1ループで加算されるラジアン値の計算
		sp = GetComponent<SpriteRenderer> ();
		Color color = sp.color;
		color.a = 0;
		sp.color = color;
	}
	
	// Update is called once per frame
	public void Up ()
	{
		fRadian += fAddradian;						// 角度加算
		if(fRadian >= Mathf.PI * 2.0f)
			fRadian -= Mathf.PI * 2.0f;
		fHeni = Mathf.Sin(fRadian) * fAmplitude;	// 変位計算

		transform.position = new Vector3(transform.position.x,
		                                 transform.position.y + fHeni,
		                                 transform.position.z);
	}
	public bool DokoikuFade(){

		Color color = sp.color;
		color.a += 0.075f;
		sp.color = color;
		if (color.a >= 1) {
			return true;
		} else {
			return false;
		}
	}
	public void AlfaOn(){
		Color color = sp.color;
		color.a = 1;
		sp.color = color;
	}
}
