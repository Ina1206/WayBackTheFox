#ifndef CSCENEBASE_H
#define CSCENEBASE_H

//-----描画------//.
#include "..\Drawing\Bord_Polygon\DebugText\CDebugText.h"	//デバッグテキストクラス.

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Sound\CSEPlayManager.h"

/**********************************
*	シーンベースクラス.
**/
class CSceneBase 
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===========関数=============//.
	void Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos);	//値設定.
	void Value(D3DXMATRIX& mProj, D3DXVECTOR3& vLight);

	virtual void Init_Process() = 0;		//初期設定処理関数.
	virtual void UpDate()		= 0;		//更新処理関数.
	virtual void Render()		= 0;		//描画処理関数.
	virtual void Release()		= 0;		//解放処理関数.

	void SetEndGameMain(bool flag) { m_bEndGameMainFlag = flag; }
	bool GetEndGameMain() { return m_bEndGameMainFlag; }
	void SetPointSum(int num) { m_PointSum = num; }
	int  GetPointSum() { return m_PointSum; };
	bool GetUIDrawEndFlag() { return m_bUIDrawEnd; }

	void SetControllerFlag(bool flag) {	m_bControllerFlag = flag; }//コントローラフラグ取得処理関数.
protected:
	D3DXVECTOR3		m_vLight;		//ライトの方向.
	D3DXVECTOR3		m_vCamPos;		//カメラ位置.
	D3DXMATRIX		m_mView;		//ビュー行列.
	D3DXMATRIX		m_mProj;		//プロジェクション行列.

	bool			m_bEndGameMainFlag;
	static int		m_PointSum;
	bool			m_bUIDrawEnd;

	bool			m_bControllerFlag;	//コントローラフラグ.

private:

};


#endif	//#ifndef CSCENEBASE_H.