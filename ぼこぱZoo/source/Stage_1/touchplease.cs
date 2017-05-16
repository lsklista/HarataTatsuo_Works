using UnityEngine;
using System.Collections;

public class touchplease : MonoBehaviour {
	public float fMinAlpha;		// 点滅時のRGBの最大値
	public float fFlashTime;		// 1回の点滅にかかる時間(光ってから, 消えるまでで1回)
	
	SpriteRenderer sp;
	public float m_fAlpha;			// 現在のRGB
	float m_fChangeAlpha;				// 1ループあたりのRGBの変化量


	// Use this for initialization
	void Start ()
	{
		m_fAlpha = 1.0f;	// 最初は元の色
		m_fChangeAlpha = ((1.0f - fMinAlpha) / fFlashTime) / 30.0f * 2.0f;
		
		sp = GetComponent<SpriteRenderer> ();
		sp.color = new Color (1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	// Update is called once per frame
	void Update ()
	{
		m_fAlpha -= m_fChangeAlpha;
		if(m_fAlpha >= 1.0f)
			m_fChangeAlpha = -m_fChangeAlpha;
		if(m_fAlpha <= fMinAlpha)
			m_fChangeAlpha = -m_fChangeAlpha;
		sp.color = new Color (1.0f, 1.0f, 1.0f, m_fAlpha);
	}
}
