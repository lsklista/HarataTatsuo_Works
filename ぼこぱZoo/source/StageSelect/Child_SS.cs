using UnityEngine;
using System.Collections;

public class Child_SS : MonoBehaviour {
	//変数宣言部
	[SerializeField] int Number = 0;
	//変更スプライトの宣言
	[SerializeField] Sprite SpriteData_1;
	[SerializeField] Sprite SpriteData_2;
	[SerializeField] Sprite SpriteData_3;
	[SerializeField] Sprite SpriteData_4;
	[SerializeField] Sprite SpriteData_5;

	SpriteRenderer sp;

	Vector3 DefaultPos;			// 最初の位置
	public int StageNumber;		// 自分のステージ番号
	
	
	void Start()
	{
		DefaultPos = transform.position;
	}
	
	public void PanelMove(Vector3 pos)
	{
		transform.position = pos;
	}
	
	// 枠を最初に表示された位置へ戻す
	public void MoveDefault()
	{
		transform.position = DefaultPos;
	}
	
	// ステージ番号を設定する
	public void MoveDefault(int number)
	{
		StageNumber = number;
	}
	
	//public void PanelRespon(Vector3 pos){	}
	
	//スプライトを変更する
	public void ChildNumber(int number){
		Number = number;
		
		switch (Number) {
		case 1:
			GetComponent<SpriteRenderer>().sprite = SpriteData_1;
			break;
		case 2:
			GetComponent<SpriteRenderer>().sprite = SpriteData_2;
			break;
		case 3:
			GetComponent<SpriteRenderer>().sprite = SpriteData_3;
			break;
		case 4:
			GetComponent<SpriteRenderer>().sprite = SpriteData_4;
			break;
		case 5:
			GetComponent<SpriteRenderer>().sprite = SpriteData_5;
			break;
		}
	}

	public void Init(){
		sp = GetComponent<SpriteRenderer> ();
		Color color = sp.color;
		color.a = 0;
		sp.color = color;
	}
	public bool FadeIn(){
		Color color = sp.color;
		color.a += 0.075f / 2.0f;
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

	
	public void Destory_Obj(){
		GameObject.Destroy (gameObject);
	}
}
