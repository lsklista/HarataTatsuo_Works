using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIFlush : MonoBehaviour
{
	[SerializeField]
	float fMaxColor;
	[SerializeField]
	float fFlushTime;

	Image image;
	Material mat;
	float fColor;		// rgb同じ色で行くので、一色分
	float fChange;

	bool bProgress;


	// Use this for initialization
	void Start()
	{
		image = GetComponent<Image>();
		mat = GetComponent<Image>().material;
		fColor = 0.5f;
		mat.color = new Color(fColor, fColor, fColor, 1.0f);

		fChange = ((fMaxColor - 0.5f) / fFlushTime) / 30.0f * 2.0f;

		bProgress = false;
	}

	// Update is called once per frame
	void Update()
	{
		if (!bProgress)
			return;

		fColor += fChange;
		if (fColor >= fMaxColor) fChange = -fChange;
		if (fColor <= 0.5f) fChange = -fChange;
		mat.color = new Color(fColor, fColor, fColor, mat.color.a);
	}

	public void StartFlush()
	{
		if (bProgress)
			return;

		fChange = Mathf.Abs(fChange);
		bProgress = true;
	}

	public void StopFlush()
	{
		fColor = 0.5f;
		mat.color = new Color(fColor, fColor, fColor, 1.0f);
		bProgress = false;
	}
}
