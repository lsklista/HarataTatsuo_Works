using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Pause_window : MonoBehaviour {
	public bool m_bMove;		// 移動中フラグ(移動中ならtrue)(publicなのはバックやステセレで使うから)
	bool m_bIn;					// スライドインしてくるときtrue
	bool m_bUp;					// 上にあがってくるときtrue
	bool m_bHarf;				// さがりの前半ならtrue, さがりの後半ならfalse

	public float m_fStartPos;	// 移動開始地点
	public float m_fReturnPos;	// 折り返し地点
	public float m_fGoTime;		// 移動開始から、折り返し地点までの時間
	public float m_fBackTime;	// 折り返し地点から、真ん中に来て止まるまでの時間
	float m_fStartSpeed;		// デバッグ用の初速度
	float m_fAccele;			// デバッグ用の加速度
	float m_fTime;				// 移動が始まってからの時間
	float m_fHeni;				// 現在の変位
	float m_fPosY;				// 代入するY座標
	float m_KijunPos;			// 変位の基準となる座標

	RectTransform recttransform;

	bool m_bActive;				// ポーズか説明, どっちがアクティブなのか


	// Use this for initialization
	void Start ()
	{
		m_bActive = false;	// DrawSetumei_window()でのActiveのために, falseにしておく

		m_bMove = false;
		m_fTime = 0.0f;

		recttransform = GetComponent<RectTransform>();
		GetComponent<Image> ().enabled = false;		// ポーズウィンドウを描画しない
	}
	
	// Update is called once per frame
	public void Up ()
	{
		// 動いてなかったらreturn
		if (!m_bMove)
			return;

		m_fTime += 1.0f / 30.0f;	// 時間

		m_fHeni = (m_fStartSpeed * m_fTime) + (0.5f * m_fAccele * m_fTime * m_fTime);	// 変位の計算
		m_fPosY = m_KijunPos + m_fHeni;		// 座標の計算
		// 「初速度・加速度・基準となる座標」を変えればこの式で座標は計算できる


		if (m_bIn)
		{// スライドイン
			if (m_bUp)
			{// 上がり
				if (m_fTime >= m_fGoTime)
				{// 折り返し地点に到達
					m_fTime = 0.0f;				// タイマー初期化
					m_bUp = false;				// 下がり
					m_bHarf = true;				// 下がりの前半

					m_fStartSpeed = 0;			// さがりの初速度は0
					m_fAccele = (-m_fReturnPos / (m_fBackTime / 2)) / (m_fBackTime / 2); // さがりの加速度を計算
					m_KijunPos = m_fReturnPos;	// 基準座標を折り返し地点にする
				}
			}
			else
			{// 下がり
				if (m_bHarf)
				{// 下がりの前半
					if (m_fTime >= m_fBackTime / 2)
					{
						m_fTime = 0.0f;			// タイマー初期化
						m_bHarf = false;		// 下がりの後半

						m_fStartSpeed = -m_fReturnPos / (m_fBackTime / 2);	// 初速度の計算
						m_fAccele = -m_fAccele;			// 加速度の計算
						m_KijunPos = m_fReturnPos / 2;	// 基準座標を真ん中と折り返し地点との中間にする
					}
				}
				else
				{// 下がりの後半
					if (m_fTime >= m_fBackTime / 2)
					{// 折り返し地点に到達
						m_bMove = false;		// 移動終了

						m_fPosY = 0.0f;			// 座標を真ん中にする
						m_fTime = m_fBackTime / 2;
						m_KijunPos = 0.0f;		// 基準座標を真ん中にする
					}
				}
			}
		}
		else
		{// スライドアウト
			if(m_bUp)
			{// 上がり
				if(m_bHarf)
				{// 上がりの前半
					if(m_fTime >= m_fBackTime / 2)
					{
						m_fTime = 0.0f;			// タイマーの初期化
						m_bHarf = false;		// 上がりの後半

						m_fStartSpeed = m_fReturnPos / (m_fBackTime / 2);	// 初速度の計算
						m_fAccele = -m_fAccele;			// 加速度の計算
						m_KijunPos = m_fReturnPos / 2;	// 基準座標を真ん中と折り返し地点との中間にする
					}
				}
				else
				{// 上がりの後半
					if(m_fTime >= m_fBackTime / 2)
					{
						m_fTime = 0.0f;			// タイマーの初期化
						m_bUp = false;			// 下がり

						m_fStartSpeed = 0.0f;	// 下がりの初速度は0
						m_fAccele = (-(m_fReturnPos - m_fStartPos) * 2 / m_fGoTime) / m_fGoTime; // 加速度の計算
						m_KijunPos = m_fReturnPos;	// 基準座標を折り返し地点にする
					}
				}
			}
			else
			{// 下がり
				if (m_fTime >= m_fGoTime)
				{// 最初の出現座標に到達
					m_bMove = false;	// 移動終了
					GetComponent<Image> ().enabled = false;	// ポーズウィンドウを非表示にする

					// ポーズウィンドウのスライドアウトが終了したので、ポーズを完全に終了させる
					GameObject.Find("Pause").GetComponent<Pause>().PauseEnd();
				}
			}
		}

		// 座標移動
		recttransform.anchoredPosition = new Vector3 (recttransform.anchoredPosition.x, m_fPosY);
	}

	// ポーズウィンドウ描画処理開始
	public void DrawPause_window()
	{// スライドインの設定
		float fDistance = m_fReturnPos - m_fStartPos;	// 上がりの移動距離の計算
		m_fStartSpeed = fDistance * 2 / m_fGoTime;		// 上がりの初速度を計算
		m_fAccele = -m_fStartSpeed / m_fGoTime;			// 上がりの加速度を計算

		m_fTime = 0.0f;									// タイマーの初期化

		// 座標の初期化
		recttransform.anchoredPosition = new Vector3 (recttransform.anchoredPosition.x, m_fStartPos);

		m_bMove = true;		// 移動開始
		m_bIn = true;		// スライドイン
		m_bUp = true;		// 上にあがる
		m_KijunPos = m_fStartPos;	// 基準座標を開始地点にする

		GetComponent<Image> ().enabled = true;			// ポーズウィンドウを表示

		Active ();
	}
	
	// ポーズウィンドウ終了処理開始
	public void UnDrawPause_window()
	{// スライドアウトの設定
		m_fStartSpeed = 0.0f;		// 上がりの初速度は0
		m_fAccele = (m_fReturnPos / (m_fBackTime / 2)) / (m_fBackTime / 2); // 上がりの加速度を計算

		m_fTime = 0.0f;

		// 座標の初期化
		recttransform.anchoredPosition = new Vector3 (recttransform.anchoredPosition.x, 0.0f);

		m_bMove = true;		// 移動開始
		m_bIn = false;		// スライドアウト
		m_bUp = true;		// 上にあがる
		m_bHarf = true;		// 上がりの前半
		m_KijunPos = 0.0f;	// 基準座標は真ん中にする

		m_bActive = false;	// DrawSetumei_window()でのActiveのために, falseにしておく
	}
	
	// ポーズウィンドウをアクティブにする
	public void Active()
	{
		// 既にアクティブなら処理しない
		if (m_bActive)
			return;

		m_bActive = true;				// ポーズウィンドウをアクティブにする
		transform.SetSiblingIndex (2);	// ポーズウィンドウは手前に表示

		GetComponent<Image> ().enabled = true;		// ポーズウィンドウを表示
		GameObject.Find("Pause_back").GetComponent<Pause_back>().DrawPause_back();
		GameObject.Find("Pause_stageselect").GetComponent<Pause_stageselect>().DrawPause_stageselect();
	}
	
	// ポーズウィンドウをノンアクティブにする
	public void NonActive()
	{
		// 既にノンアクティブなら処理しない
		if (!m_bActive)
			return;

		m_bActive = false;				// ポーズウィンドウをノンアクティブにする
		transform.SetSiblingIndex (1);	// ポーズウィンドウは手前に表示

		GetComponent<Image> ().enabled = false;		// ポーズウィンドウを描画しない
		GameObject.Find("Pause_back").GetComponent<Pause_back>().UnDrawPause_back();
		GameObject.Find("Pause_stageselect").GetComponent<Pause_stageselect>().UnDrawPause_stageselect();
	}
}
