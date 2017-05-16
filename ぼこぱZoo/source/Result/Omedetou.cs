using UnityEngine;
using System.Collections;

public class Omedetou : MonoBehaviour {
	float fSpeed;


	// Use this for initialization
	void Start ()
	{
		fSpeed = 0.0f;
		GetComponent<SpriteRenderer>().enabled = false;	// 最初は描画しない
	}
	
	// Update is called once per frame
	void Update ()
	{
		transform.position = new Vector3 (transform.position.x,
		                                  transform.position.y + fSpeed,
		                                  transform.position.z);
	}

	// はむちが切り離された瞬間に呼ばれて, あとはこっちで動く
	public void SetSpeed(float speed)
	{
		fSpeed = speed;
	}
}
