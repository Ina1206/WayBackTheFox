#ifndef CBOSS_GREAT_CAMERA_H
#define CBOSS_GREAT_CAMERA_H

#include "..\CCameraBase.h"

/*********************************************
*		ボスのGreat判定時のクラス.s
**************/
class CBossGreatCamera
	: public CCameraBase
{
public:
	CBossGreatCamera();
	~CBossGreatCamera();

	//==================定数====================//.
	const float			RETURN_SPEED			= 0.05f;										//戻る速度.
	const float			MOVE_START_HEIGHT		= 3.0f;											//カメラの注視点が動き出す高さ.
	const float			TARGET_DIFFERENCE		= 2.0f;											//映す目標の高さを少し低くする.
	const float			MOVE_HEIGHT_MIN			= 0.1f;											//移動するカメラの高さの最小値.
	const D3DXVECTOR3	PLAYER_CAMERA_POS		= D3DXVECTOR3(2.0f, 1.3f, 6.0f);				//プレイヤーに向くときのカメラ座標.
	const D3DXVECTOR3	PLAYER_LOOK_ASSIST		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//プレイヤーに向く注視点の補助.
	const float			CAMERA_MOVE_ORIGIN		= PLAYER_CAMERA_POS.x - STANDERD_CAMERA_POS.x;	//カメラ移動の割合の元.
	const float			PLAYER_RATIO_HORIZON	= PLAYER_CAMERA_POS.x / CAMERA_MOVE_ORIGIN;		//カメラのx軸の移動割合.
	const float			PLAYER_RATIO_HEIGHT		= PLAYER_CAMERA_POS.y / CAMERA_MOVE_ORIGIN;		//カメラのy軸の移動割合.
	const float			PLAYER_RATIO_BACK		= PLAYER_CAMERA_POS.z / CAMERA_MOVE_ORIGIN;		//カメラのz軸の移動割合.
	const int			WAIT_TIME				= 120;											//待機する時間.
	const float			START_SWING_MAX			= 0.05f;										//揺れる距離の初めの最大値.
	const float			SWING_CAMERA_SPEED		= 0.05f;										//カメラが揺れる速度.
	const int			UP_DIRECTION_NUM		= 1;											//上方向の番号.
	const int			CHANGE_DIRECTION_NUM	= -1;											//カメラの方向変更数値.
	const float			PLAYER_LOOK_SPEED		= 0.02f;										//プレイヤーの見る速度.

	//=================列挙体===================//.
	//カメラの種類.
	enum class enCameraType {
		Boss,		//ボスを見ているとき.
		Player,		//プレイヤーを見ているとき.
		Return,		//カメラを戻す.
	};

	//=================関数====================//.
	void UpDate(bool CameraFlag);	//更新処理関数.
private:
	//=================関数====================//.
	void Move();					//移動処理関数.
	void Return();					//戻る処理.
	void BossFlyMove();				//ボスが飛ぶ時のカメラ移動.
	void PlayerLook();				//プレイヤーを見るカメラ移動.
	bool BossFlySwing();			//ボスが飛ぶ時の揺れ.

	//=================変数====================//.
	enCameraType	m_enCameraType;			//カメラの種類.
	D3DXVECTOR3		m_vOldTargetPos;		//前回の映す相手の座標.
	D3DXVECTOR3		m_fCameraChangeBefore;	//カメラが移動する前の座標.
	float			m_fTargetLook;			//目標の注視点.
	int				m_WaitTime;				//待機時間.
	
	D3DXVECTOR3		m_vSwingBeforePos;		//揺れる前の位置.
	D3DXVECTOR3		m_vSwingBeforeLook;		//揺れる前の注視点.
	int				m_SwingDirection;		//揺れる方向.
	float			m_SwingDistanceMax;		//揺れる距離の最大数.
	bool			m_bSwingFinish;			//揺れるの終了.
	bool			m_bCenterPassing;		//中心を通過したフラグ.
};

#endif	//#ifndef CBOSS_GREAT_CAMERA_H.