using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class SpeedUp : MonoBehaviour {
	Image img;
	float fAlpha;
	float fSubAlpha;

	// Use this for initialization
	void Start ()
	{
		img = GetComponent<Image>();
		fAlpha = 0.0f;
		fSubAlpha = 1.0f / 15.0f;
		img.color = new Color (1.0f, 1.0f, 1.0f, 0.0f);
	}
	
	// Update is called once per frame
	public void Up ()
	{
		if (fAlpha == 0.0f)
			return;

		fAlpha -= fSubAlpha;
		if (fAlpha <= 0.0f)
			fAlpha = 0.0f;

		img.color = new Color (1.0f, 1.0f, 1.0f, fAlpha);
	}

	public void StartSpeedUp()
	{
		fAlpha = 1.0f;
	}
}
