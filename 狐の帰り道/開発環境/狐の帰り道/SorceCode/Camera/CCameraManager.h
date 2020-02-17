#ifndef CCAMERA_MANAGER_H
#define CCAMERA_MANAGER_H

#include "StamderdCamera/CStanderdCamera.h"
#include "UpCamera/CUpCamera.h"
#include "CameraBoss/CBossBadCamera.h"
#include "CameraBoss/CBossGreatCamera.h"
#include "..\Command\enumCommand_Global.h"

/***************************************
*		カメラ管理クラス.
**/
class CCameraManager
{
public:
	CCameraManager();
	~CCameraManager();

	//===============列挙体=================//.
	//カメラの種類.
	enum class enCamera {
		Standerd = 0,	//基本位置.
		Up,				//上の位置.
		Boss,			//ボスの時.
	};

	//================関数==================//.
	void ChangeCamera();	//カメラ変更処理関数.
	void UpDate();			//更新処理関数.

	//===========情報獲得処理関数=============//.
	D3DXVECTOR3 GetvPos() { return m_vPos; }
	D3DXMATRIX	GetmView() { return m_mView; }

	//===========情報置換処理関数=============//.
	//長押し時のカメラ移動フラグ.
	void SetLongPush(bool flag) { m_bLongPush = flag; }
	//ボス戦の時のカメラ移動フラグ.
	void SetChangeCamera(bool flag) { m_bChangeMove = flag; }
	//ボス戦時用のコマンド判定.
	void SetInputDecision(enInput_Decision InputDecision) { m_enInput_Decision = InputDecision; }
	//カメラで映したい座標.
	void SetTargetPos(D3DXVECTOR3 vTargetPos) { m_vTargetPos = vTargetPos; }
private:
	//================関数==================//.
	void Release();			//解放処理関数.

	//================変数==================//.
	CCameraBase*		m_pCCamera;				//カメラ切り替え用.
	D3DXVECTOR3			m_vPos;					//座標.
	D3DXMATRIX			m_mView;				//ビュー行列.
	
	bool				m_bLongPush;			//長押しフラグ.
	bool				m_bOldLongPush;			//長押しフラグ差分.

	enInput_Decision	m_enInput_Decision;		//コマンドの判定.
	enInput_Decision	m_enOldInput_Decision;
	bool				m_bChangeMove;			//カメラの移動.

	D3DXVECTOR3			m_vTargetPos;			//カメラで映したい座標.
};

#endif	//#ifndef CCAMERA_MANAGER_H.