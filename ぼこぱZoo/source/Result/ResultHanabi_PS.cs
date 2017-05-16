using UnityEngine;
using System.Collections;

public class ResultHanabi_PS : MonoBehaviour {
	float fTime;
	float fSixtyFPSTime;	// 60fpsのときの1フレームの時間
	float fLifeTime;

	// Use this for initialization
	void Start ()
	{
		fTime = 0.0f;
		fSixtyFPSTime = 1.0f / 30.0f;
		fLifeTime = GetComponent<ParticleSystem> ().duration;
	}
	
	// Update is called once per frame
	void Update ()
	{
		fTime += fSixtyFPSTime;

		if (fTime >= fLifeTime)
			Destroy (this.gameObject);
	}
}
