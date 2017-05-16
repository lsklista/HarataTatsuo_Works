using UnityEngine;
using System.Collections;

public class select_guide : MonoBehaviour {
	SpriteRenderer sp;

	// Use this for initialization
	void Start ()
	{
		sp = GetComponent<SpriteRenderer> ();
		Color color = sp.color;
		color.a = 0;
		sp.color = color;
	}
	
	// Update is called once per frame
	void Update ()
	{
		
	}

	
	public bool guideFade(){
		
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
