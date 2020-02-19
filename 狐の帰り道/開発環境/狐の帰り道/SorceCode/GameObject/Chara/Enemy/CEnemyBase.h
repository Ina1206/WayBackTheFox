#ifndef CENEMY_BASE_H
#define CENEMY_BASE_H

#include "..\..\Chara\CChara.h"
#include "..\..\..\Command\enumCommand_Global.h"
#include "..\..\..\Sound\CSEPlayManager.h"
#include "..\..\..\Command\CCommand_Base.h"

/*****************************************
*	敵の元クラス.
**/
class CEnemyBase
	: public CChara
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();
	//================定数=====================//.
	const float	DISP_DISTANCE			= 50.0f;	//表示する範囲.
	const float	ANIM_SPEED				= 0.02f;	//アニメーション速度.

	//================関数=====================//.
	void  FitMoveGround();				//グラウンドの動きに合わせる処理関数.
	void  DecisionDisp();				//表示判定処理関数.


	//～情報獲得処理関数～.
	D3DXVECTOR3			GetPostion()	{ return m_vPos; }												//位置獲得処理.			//Boss.
	bool				GetDispFlag()		{ return m_bDispFlag; }											//表示フラグ獲得処理.

	//～情報置換処理関数～.
	void SetInitPosition	(D3DXVECTOR3 vPos)							{ m_vInitPos = vPos; }					//初期位置.
	void SetPlayerPos		(D3DXVECTOR3 vPlayerPos)					{ m_vPlayerPos = vPlayerPos; }			//プレイヤー座標.
	void SetSpeed			(float Speed)								{ m_fSpeed = Speed; }					//地面のスクロール速度.
	void SetCommandType		(enCommandType enType)						{ m_enCommandType = enType; }			//入力ボタン情報.
	void SetJudgePossible	(bool JudgePossible)						{ m_bJudgePossible = JudgePossible; }	//判定可能フラグ.
	void SetLongPushCnt		(int LongPush)								{ m_LongPushCnt = LongPush; }			//長押しカウント.
	
protected:
	
	D3DXVECTOR3			m_vPos;				//位置座標.
	D3DXVECTOR3			m_vInitPos;			//初期位置.
	D3DXVECTOR3			m_vPlayerPos;		//プレイヤーの座標.
	D3DXVECTOR3			m_vRot;				//傾き.

	float				m_fSpeed;			//移動速度.

	CCommand_Base*		m_pCCommand_Base;	//コマンド基底クラス.
	enCommandType		m_enCommandType;	//入力ボタン情報.
	bool				m_bJudgePossible;	//コマンド判定可能フラグ.
	int					m_LongPushCnt;		//長押しカウント.

	bool				m_bDispFlag;		//表示フラグ.

	CSEPlayManager*		m_pCSEPlayManager;	//SE再生管理クラス.

private:
};

#endif	//#ifndef CENEMY_BASE_H.