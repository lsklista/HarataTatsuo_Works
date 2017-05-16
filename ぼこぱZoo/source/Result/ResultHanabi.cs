using UnityEngine;
using System.Collections;

public class ResultHanabi : MonoBehaviour {
	public ParticleSystem PS;
	public float fHanabiInterval;	// 花火を出す間隔
	float fTime;					// タイマー
	float fSixtyFPSTime;			// 60fpsのときの1フレームの時間
	public Vector2 CreateDistance;	// 花火の出現可能な中心からの幅
	Vector3 CreatePos;				// 花火の出現座標

	bool bStop;						// 花火を止める


	// Use this for initialization
	void Start ()
	{
		fTime = 0.0f;
		fSixtyFPSTime = 1.0f / 30.0f;
		CreatePos = Vector3.zero;
		bStop = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
		// フェードイン中なら処理はしない
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFadeIn)
			return;

		// 
		if (bStop)
			return;

		fTime += fSixtyFPSTime;

		// 花火作成
		if (fTime >= fHanabiInterval)
		{
			CreatePos = new Vector3 (Random.Range (-CreateDistance.x, CreateDistance.x),
			                        Random.Range (-CreateDistance.y, CreateDistance.y),
			                        0.0f);
			
			Instantiate (PS, CreatePos, Quaternion.identity);

			fTime = 0.0f;
		}
	}

	// 花火の処理を止める
	public void StopHanabi()
	{
		bStop = true;
	}
}
