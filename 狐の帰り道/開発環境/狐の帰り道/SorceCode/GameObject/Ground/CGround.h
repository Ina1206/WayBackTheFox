#ifndef GOURND_H
#define GOURND_H

#include "..\..\Command\enumCommand_Global.h"
#include "..\CGameObject.h"						//ゲームオブジェクト.
#include "..\..\Drawing\Resource\ResourceBordPolygon\ResourceParticle\CResourceParticle.h"
/*****************************************
*	地面クラス.
**/
class CGround
	: public CGameObject
{
public:
	CGround();
	virtual ~CGround();

	//==========定数=========//.
	const int	STAGE_MAX_BACK			= 8;			//ステージの奥行のオブジェクトの数.
	const int	STAGE_MAX_HORIZON		= 3;			//ステージの横のオブジェクト数.
	const int	CENTER_GROUND_NUM		= 1;			//中央の地面の番号.
	const float STANDERD_ROT_Y			= 3.14f;		//ステージのy軸の傾き.
	const float STAGE_DEPTH_WIDTH		= 7.8f;			//ステージの奥行の幅.
	const float GROUND_WIDTH			= 7.9f;			//地面の横幅.
	const float	GROUND_BACK_POSITION	= -15.0f;		//地面がまた後ろに戻る位置.
	const float GROUND_HIGHT_ADJUSTMENT = 0.0001f;		//地面の高さ調整.
	const float STAGE_START_POS			= -4.0f;		//ステージ開始時の位置.
	const float SET_POS					= 1.0f;			//ステージの位置.
	const float STANDERD_SPEED			= 0.05f;		//スクロールスピード.
	const float UP_LOOK_SPEED			= 0.04f;		//上にカメラが来た時のスクロールスピード.
	const float SCROLL_DECELETARATION	= 0.0008f;		//減速スピード.
	const float SWING_START_ROTATION	= -3.4f;		//揺れ始めるボスの角度.
	const float	SWING_UP_MAX			= 0.8f;			//上がる最大数.
	const float STANDERD_POS_HIGHT		= 0.0f;			//地面の基準の高さ最大数.
	const float SWING_SPEED				= 0.1f;			//揺れる速度.
	const int	SWING_MAX				= 5;			//揺れる回数最大数.
	const float	SWING_REDUCE_SPEED		= 0.4f;			//揺れる大きさを減らす速度.
	const float SWING_REDUCE_ADJU		= 0.08f;		//揺れる大きさの微調整.
	const float GOAL_DISTANCE			= 150.0f;		//ゴールの距離.
	const float	GAET_DISP_DISTANCE		= 25.0f;		//門の表示距離.

	//==========関数=========//.	
	void InitProcess();								//初期化処理関数.
	void Update();										//更新処理関数.
	void Render();										//描画処理関数.
	void Release();										//解放処理関数.

	//====情報獲得処理関数=====//.
	float GetMoveSpeed() { return m_fScroll_Speed; }
	float GetMovingDistance() { return m_fMoving_Distance; }
	float GetUpDistance() { return m_fUpDistance; }

	//====情報置換処理関数=====//.
	//カメラを上にあげるフラグ.
	void SetUpCamera(bool flag) { m_bMoveCamera = flag; }
	//スクロール速度減速開始フラグ.
	void SetDeceleration_StartFlag(bool flag) { m_bDeceleration_Start = flag; };
	//ボスの角度.
	void SetBossRotation(D3DXVECTOR3 vRot) { m_vBossRot = vRot; }
	//ボスの判定.
	void SetBossCommand(enInput_Decision enInput) { m_enInputDecision = enInput; }
	//ゲートの座標設定.
	void SetGatePosition(D3DXVECTOR3 vPos) { m_vInitGatePos.z = vPos.z + 5.0f; }
	

	//==========列挙体========//.
	//揺れの種類.
	enum class enSwingType {
		Up,			//上がる.
		Down,		//下がる.
		Nothing,	//無し.

		Max,		//最大数.
		Start = Up,	//最初.
	};
private:
	//===========関数=========//.
	void Move();										//移動処理関数.
	void ScrollSpeedDeceleration();					//スクロールスピードの減速処理関数.
	void Swing();										//揺れる処理関数.

	//=========クラス========//.
	CDX9Mesh**		m_ppGround;							//CDX9Meshクラス.
	CDX9Mesh*		m_pCGate;							//鳥居のCDX9Meshクラス.
	CDepth_Stencil	m_CDepth_Stencil;					//デプスステンシル.

	//===========変数===========//.
	D3DXVECTOR3*		m_pvPos;							//座標.
	float				m_fScroll_Speed;					//スクロール速度.
	bool				m_bDeceleration_Start;				//スクロール速度減速開始.
	bool				m_bMoveCamera;						//カメラが動いた時のフラグ.
	float				m_fMoving_Distance;					//移動距離.
	int					m_BackCnt;							//後ろに戻ったカウント.
	int					m_BackNum;							//一番後ろの番号.
	float				m_fSwingUpMax;						//揺れの最大数.

	D3DXVECTOR3			m_vBossRot;							//ボスの角度.
	enSwingType			m_enSwingType;						//揺れの種類.
	float				m_fUpDistance;						//上に上がる
	int					m_SwingCount;						//揺れるカウント.
	enInput_Decision	m_enInputDecision;					//コマンド結果.


	D3DXVECTOR3			m_vGatePos;							//ゲートの座標.
	D3DXVECTOR3			m_vInitGatePos;						//初期ゲート座標.
};

#endif	//#ifndef GOURND_H.