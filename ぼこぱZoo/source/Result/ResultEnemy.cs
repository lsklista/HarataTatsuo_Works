using UnityEngine;
using System.Collections;

public class ResultEnemy : MonoBehaviour {
	Vector2 Speed;		// 移動量
	float fGravity;		// 下方向にかかる加速度
	float fAddAngle;	// 1ループでの角度の変化量

	// Use this for initialization
	void Start ()
	{
		
	}
	
	// Update is called once per frame
	void Update ()
	{
		Speed = new Vector2 (Speed.x, Speed.y - fGravity);

		// 移動
		transform.position = new Vector3 (transform.position.x + Speed.x,
		                                  transform.position.y + Speed.y,
		                                  transform.position.z);

		// 回転
		transform.Rotate (0.0f, 0.0f, fAddAngle);

		// 消滅判定(-16くらいで見えなくなるから)s
		if (transform.position.y <= -16.0f)
		{
			Destroy(this.gameObject);
		}
	}

	// 移動速度を設定
	// インスタンスが作られた瞬間に呼び出される
	public void SetSpeed(Vector2 speed, float gravity, float addangle)
	{
		Speed = speed;
		fGravity = gravity;
		fAddAngle = addangle;
	}
}
