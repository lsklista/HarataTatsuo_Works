using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Cloud_StageSelect : MonoBehaviour {
	[SerializeField] float m_fOneLoopTime;	// 雲が1ループするのにかかる時間
	
	RawImage m_RawImage;
	float m_fAddU;					// UV座標のUの1ループあたりの変化量
	float m_fU;						// 代入するU座標

	
	void Start()
	{
		m_RawImage = GetComponent<RawImage>();
		m_RawImage.uvRect = new Rect(0.0f, 0.0f, 1.0f, 1.0f);	// UV座標初期化
		m_fAddU = (1.0f / m_fOneLoopTime) / 30.0f;
	}
	
	void Update()
	{
		m_fU = m_RawImage.uvRect.x + m_fAddU;
		if(m_fU >= 1.0f)
			m_fU -= 1.0f;
		m_RawImage.uvRect = new Rect(m_fU, 0.0f, 1.0f, 1.0f);
	}
}