using UnityEngine;
using System.Collections;

public class ResultButton : MonoBehaviour {
	Fade Fade_cs;		//フェード用

	// Use this for initialization
	void Start ()
	{
		Fade_cs = GameObject.Find ("Fade").GetComponent<Fade> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void onTapButton()
	{
		Fade_cs.FadeStart(Fade.NEXTSCENE.RESULR);
	}
}
