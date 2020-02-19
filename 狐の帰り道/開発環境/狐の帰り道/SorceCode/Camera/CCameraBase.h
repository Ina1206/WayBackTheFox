#ifndef CCAMERABASE_H
#define CCAMERABASE_H

#include "..\Drawing\3D_Object\CDX9Mesh.h"
#include "..\Global.h"

/*********************************************
*		カメラ基底クラス.
**/
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();

	//================定数====================//.
	//～カメラの座標～.
	const D3DXVECTOR3	STANDERD_CAMERA_POS		= D3DXVECTOR3(0.0f, 2.5f, 0.0f);					//ゲーム基準でのカメラ位置.
	const D3DXVECTOR3	UP_CAMERA_POS			= D3DXVECTOR3(0.0f, 6.0f, 3.5f);					//カメラが上に来た時のカメラ位置.
	const D3DXVECTOR3	BAD_BOSS_CAMERA_POS		= D3DXVECTOR3(0.0f, 1.0f, -1.5f);					//ボスの時のカメラ位置.
	//～注視点～.
	const D3DXVECTOR3	CAMERA_LOOK				= D3DXVECTOR3(0.0f, 1.0f, 6.0f);					//注視点.
	const D3DXVECTOR3	UP_CAMERA_LOOK			= D3DXVECTOR3(0.0f, 1.0f, 5.2f);					//カメラが上に来た時の注視点.
	const D3DXVECTOR3	BOSS_CAMERA_LOOK		= D3DXVECTOR3(0.0f, 1.0f, 5.0f);					//ボスの時の注視点.
	//～移動～.
	const float			MOVE_SPEED				= 0.08f;											//全体基準移動速度.
	const float			UP_ORIGINARU_NUM		= UP_CAMERA_POS.y - STANDERD_CAMERA_POS.y;			//上に上がるときの割合の元の数.
	const float			UP_RATIO_Z				= UP_CAMERA_POS.z / (UP_ORIGINARU_NUM);				//上がるときのZ軸の割合.
	const float			UP_RATIO_LOOK			= UP_CAMERA_LOOK.z / (UP_ORIGINARU_NUM);			//上に上がるとにの注視点の割合.
	const float			BAD_BOSS_ORIGINARU_NUM	= BAD_BOSS_CAMERA_POS.y - STANDERD_CAMERA_POS.y ;	//ボス戦の時の割合の元の数.
	const float			BAD_BOSS_RATIO_Z		= BAD_BOSS_CAMERA_POS.z / (BAD_BOSS_ORIGINARU_NUM);	//ボス戦の時のZ軸の割合.
	const float			BAD_BOSS_RATIO_LOOK		= BOSS_CAMERA_LOOK.z / (BAD_BOSS_ORIGINARU_NUM);	//ボス戦の時の注視点の割合.
	//～ビュー～.
	const D3DXVECTOR3	UP_VECTOR				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//上方ベクトル.


	//================関数====================//.
	void ChangeView();													//ビュー変換処理関数.
	virtual void Update(bool CameraFlag) = 0;							//更新処理関数.

	//===========情報取得処理関数==============//.
	D3DXVECTOR3 GetCameraPos() { return m_Camera.vPos; }				//カメラ座標.
	D3DXMATRIX	GetMatrixView() { return m_mView; }					//ビュー行列.
	bool		GetCameraChangeFlag() { return m_CameraChangeFlag; }	//カメラ種類変更フラグ.
	
	//===========情報置換処理関数==============//.
	void SetTargetPos(D3DXVECTOR3 vPos) { m_vTargetPos = vPos; }		//相手の座標.
protected:
	//================関数====================//.
	virtual void Move() = 0;											//移動処理関数.

	//================変数====================//.
	CAMERA					m_Camera;									//カメラ情報.
	D3DXMATRIX				m_mView;									//ビュー行列.
	bool					m_CameraChangeFlag;							//カメラの種類変更フラグ.

	D3DXVECTOR3				m_vTargetPos;								//カメラで映したい相手の座標.
private:
};

#endif //#ifndef CCAMERABASE_H.