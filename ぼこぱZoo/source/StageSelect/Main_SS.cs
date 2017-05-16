using UnityEngine;
using System.Collections;
using System.Collections.Generic;



public class Main_SS : MonoBehaviour {
	//動かすパネルオブジェクト
	public GameObject ChildPanel;
	//上のゲームオブジェクトのスクリプトを触る
	Child_SS child;
	//リストの宣言部
	public List<GameObject> PanelList = new List<GameObject>();
	//Androidでタッチされたかどうか用変数


	Vector3 touchPoint_screen;
	Vector3 touchPoint_world;
	Vector3 MousePoint_Screen;
	Vector3 MousePoint_World;
	Vector3 currentScreenPoint;
	Collider2D aCollider2d;
	Collider2D col;
	GameObject obj;
	public RaycastHit2D hit;
	SpriteRenderer sp;




	// 枠との判定用の変数
	GameObject Waku;			// 枠のオブジェクト
	waku Waku_cs;				// 枠のスクリプト
	public float fHitDistance;	// 「枠に入った」とする距離(この値より小さければOK)
	float fDistance;			// 現在の枠との距離
	bool bStageSelect;			// ステージが選ばれたら操作を無効にするフラグ

	bool NullFlg = false;
	bool NullFlg2 = false;

	//グローバル変数宣言部
	//パネルオブジェクトの座標用
	Vector3 PanelPos = new Vector3(0.0f, 3.0f, 0.0f);

	// BGMを鳴らし始めるか, どうかのフラグ
	static bool bPlayBGM;

	// Use this for initialization
	void Start ()
	{
		for (int i = 1 ; i <= 5 ; i ++)
		{
			GameObject obj;
			obj = Instantiate (ChildPanel, PanelPos, Quaternion.identity)as GameObject;
			child = obj.GetComponent<Child_SS> ();
			child.ChildNumber (i);
			child.StageNumber = i;	// ステージ番号をセットする
			child.Init();

			// 座標設定
			PanelPos += new Vector3 (7.0f, 0.0f, 0.0f);
			if (i == 3)
			{
				PanelPos = new Vector3 (3.5f, -4.0f, 0);
			}
			
			PanelList.Add (obj);
		}
		sp = GetComponent<SpriteRenderer> ();
		child = null;

		Waku = GameObject.Find ("Waku");
		Waku_cs = Waku.GetComponent<waku>();
		fDistance = 0.0f;
		bStageSelect = false;

		// ※BGMはタイトルから鳴りっぱなしなのでロードする必要はなし
		// タイトル・ステセレ兼用BGMを鳴らす
		// タイトルから遷移してきた場合は鳴らさない
		Sound.PlayBgm ("BGM_Title");

		Sound.LoadSe ("Click", "SE_Click");
	}
	
	// Update is called once per frame
	public void Up ()
	{
		// ステージが選択されていたら、操作できなくする。
		if (bStageSelect)
			return;


		//マウスの処理
		if (Input.GetMouseButtonDown (0))
		{
			child = null;
			MousePoint_Screen = Camera.main.WorldToScreenPoint(transform.position);
			Vector3 newVector = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x,Input.mousePosition.y,MousePoint_Screen.z));
			col = Physics2D.OverlapPoint(new Vector2(newVector.x,newVector.y));
			if(col)
			{
				for(int i = 0;i < PanelList.Count;i ++)
				{
					if(PanelList[i] == col.gameObject)
					{
						obj = col.gameObject;
						child = obj.GetComponent<Child_SS>();
						obj.GetComponent<SpriteRenderer>().sortingOrder = 2;	// 描画順変更
						Sound.PlaySe("Click");
						break;
					}
				}
			}
		}
		if (Input.GetMouseButton (0) && child)
		{
			if(!NullFlg){
				child = null;
				NullFlg = true;
				return;
			}
			currentScreenPoint = Input.mousePosition;
			Vector3 currentPosition = Camera.main.ScreenToWorldPoint(currentScreenPoint);
			child.PanelMove(new Vector3(currentPosition.x,currentPosition.y,0));
		}
		
		if (Input.GetMouseButtonUp (0))
		{
			if(!NullFlg2){
				child = null;
				NullFlg2 = true;
			}
			if(child)
			{// childがあるときだけ、枠との判定をする。
				// ここで枠との距離をとり、枠にはまったか、はまってないかの判定をする。
				fDistance = Vector3.Distance(child.transform.position, Waku.transform.position);
				if(fDistance <= fHitDistance)
				{// 枠にはまる
					child.PanelMove(Waku.transform.position);	//パネルを枠の中心に移動させる
					Waku_cs.SetStageNumber(child.StageNumber);	// 枠に何番目のステージがはまったのかをセットする。
					bStageSelect = true;						// ステージを選択したので、操作を無効にする。
				}
				else
				{// 枠にはまらない
					child.MoveDefault();	// 枠をデフォルトの位置に戻す
				}

				// 描画順を元に戻す
				obj.GetComponent<SpriteRenderer>().sortingOrder = 1;
			}

			child = null;
		}
		
		//Androidのタップ処理
		if(Input.touchCount > 0)
		{
			if(Input.touchCount > 0)
			{
				Touch t = Input.GetTouch(0);
				if(t.phase == TouchPhase.Began)
				{
					child = null;
					touchPoint_screen = Camera.main.WorldToScreenPoint(transform.position);
					Vector3 newVector = Camera.main.ScreenToWorldPoint(new Vector3(t.position.x,t.position.y,touchPoint_screen.z));
					aCollider2d = Physics2D.OverlapPoint(new Vector2(newVector.x,newVector.y));
					if(aCollider2d)
					{
						for(int i = 0;i < PanelList.Count;i ++)
						{
							if(PanelList[i] == aCollider2d.gameObject)
							{
								obj = aCollider2d.gameObject;
								child = obj.GetComponent<Child_SS>();
								obj.GetComponent<SpriteRenderer>().sortingOrder = 2;	// 描画順変更
								Sound.PlaySe("Click");
								break;
							}
						}
					}
				}

				if(t.phase == TouchPhase.Moved && child)
				{
					if(!NullFlg){
						child = null;
						NullFlg = true;
						return;
					}
					currentScreenPoint = t.position;
					Vector3 currentPosition = Camera.main.ScreenToWorldPoint(currentScreenPoint);
					child.PanelMove(new Vector3(currentPosition.x,currentPosition.y,0));
				}
				
				if(t.phase == TouchPhase.Ended)
				{
					if(!NullFlg2){
						child = null;
						NullFlg2 = true;
					}
					if(child)
					{// childがあるときだけ、枠との判定をする。
						// ここで枠との距離をとり、枠にはまったか、はまってないかの判定をする。
						fDistance = Vector3.Distance(child.transform.position, Waku.transform.position);
						if(fDistance <= fHitDistance)
						{// 枠にはまる
							child.PanelMove(Waku.transform.position);	//パネルを枠の中心に移動させる
							Waku_cs.SetStageNumber(child.StageNumber);	// 枠に何番目のステージがはまったのかをセットする。
							bStageSelect = true;						// ステージを選択したので、操作を無効にする。
						}
						else
						{// 枠にはまらない
							child.MoveDefault();	// 枠をデフォルトの位置に戻す
						}

						// 描画順を元に戻す
						obj.GetComponent<SpriteRenderer>().sortingOrder = 1;
					}

					child = null;
				}
			}
		}
	}

	// ステージセレクトシーンで, BGMを鳴らし始めるのかどうかのフラグ
	// trueなら鳴らす
	static public void SetPlayBGM(bool flg)
	{
		bPlayBGM = flg;
	}

	public void SkipOn(){
		for (int i = 0; i < PanelList.Count; i ++) {
			child = PanelList [i].GetComponent<Child_SS> ();
			child.AlfaOn();
		}
	}

	public bool PanelFadeIn(){
		for (int i = 0; i < PanelList.Count; i ++) {
			child = PanelList[i].GetComponent<Child_SS>();
			bool ChildFadeFlg = child.FadeIn();
			if(ChildFadeFlg){
				return true;
				break;
			}
		}
		return false;
	}
}
