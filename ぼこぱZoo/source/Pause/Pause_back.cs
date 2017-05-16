using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Pause_back : MonoBehaviour {
	RectTransform recttransform;

	public float m_fMinScale;		// 最小の拡大率
	public float m_fMaxScale;		// 最大の拡大率
	float m_fScaleDifference;		// 最小拡大率と最大拡大率の差
	float m_fSita;					// 現在の角度
	public float m_fOneInterval;	// 1回の拡大縮小にかける時間
	float m_fAddSita;				// 1ループあたりの角度の増加量

	public bool m_bUpdate;			// 更新していいかどうかのフラグ
	public float m_fWaitTime;		// 拡大縮小の1ループが終わってから、もう片方のボタンの更新を有効にするまでの時間
	public float m_fTime;			// m_fWaitTimeのための経過時間

	// Use this for initialization
	void Start ()
	{
		m_fScaleDifference = m_fMaxScale - m_fMinScale;	// 小拡大率と最大拡大率の差を計算
		m_fAddSita = (180.0f / m_fOneInterval) / 30.0f;	// 1ループあたりの角度の増加量を計算

		recttransform = GetComponent<RectTransform>();
		GetComponent<Image> ().enabled = false;			// バックボタンを描画しない
	}
	
	// Update is called once per frame
	public void Up ()
	{
		// 更新フラグがfalseの場合はreturn
		if (!m_bUpdate)
			return;

		float fScale;

		m_fSita += m_fAddSita;
		if (m_fSita < 180.0f)
		{
			fScale = m_fMinScale + (m_fScaleDifference * Mathf.Sin (m_fSita * Mathf.Deg2Rad));
		}
		else
		{
			fScale = m_fMinScale;	// 拡大率は最小拡大率で固定

			m_fTime += 1.0f / 30.0f;
			if(m_fTime >= m_fWaitTime)
			{
				m_bUpdate = false;	// 自身を更新できなくする

				// ステセレボタンの更新を有効にする
				GameObject.Find("Pause_stageselect").GetComponent<Pause_stageselect>().UpdateActivate();
			}
		}

		// 拡大率の設定
		recttransform.localScale = new Vector3 (fScale, fScale, recttransform.localScale.z);
	}
	
	public void OnTapButton()
	{
		// ポーズウィンドウが移動中ならタップは無効
		if (GameObject.Find ("Pause_window").GetComponent<Pause_window> ().m_bMove)
			return;
		
		// フェード中ならタップは無効
		if (GameObject.Find ("Fade").GetComponent<Fade> ().m_bFade)
			return;

		GameObject.Find ("Pause").GetComponent<Pause>().ChangePause();
		
		// ボタンがタップされた音を鳴らす
		Sound.PlaySe ("SE_Enter");
	}
	
	// バックボタンを描画
	public void DrawPause_back()
	{
		m_fSita = 0.0f;							// 角度を初期化
		GetComponent<RectTransform>().localScale = 
			new Vector3 (m_fMinScale, m_fMinScale, m_fMinScale);	// 拡大率を初期化

		m_bUpdate = false;						// バックボタンの更新を無効にする
		m_fTime = 0.0f;							// m_fWaitTimeのための経過時間を初期化

		GetComponent<Image> ().enabled = true;
	}
	
	// バックボタンを描画しない
	public void UnDrawPause_back()
	{
		GetComponent<Image> ().enabled = false;
	}

	// 更新を有効化する
	public void UpdateActivate()
	{
		m_fSita = 0.0f;		// 角度の初期化
		m_fTime = 0.0f;		// m_fWaitTimeのための経過時間を初期化
		m_bUpdate = true;
	}
}
