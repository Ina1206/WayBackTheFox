#ifndef CPLAYER_H
#define CPLAYER_H

#include "..\CChara.h"
#include "..\..\..\Drawing\CCommon.h"
#include "..\..\..\Command\enumCommand_Global.h"
#include "..\..\..\Sound\CSEPlayManager.h"
//当たり判定クラス.
#include"..\..\Collider_Detection\CCollision_Detection.h"

//コントローラクラス.
#include"..\..\..\Controller\CXInput.h"

//プレイヤークラス.
class CPlayer
	: public CChara
{
public:
	//================列挙体==================//.
	//アクション状態.
	enum class enPlyAct
	{
		Attack = 0,		//攻撃.
		Jump,			//ジャンプ.
		TwoRowJump,		//二段ジャンプ.	
		Run,			//立ち.
		Wait,			//待機.
		Panic,			//パニック.

		Max,			//最大.
		Start = Attack,	//最初.
	};


	CPlayer();	//コンストラクタ.
	~CPlayer();	//デストラクタ.

	//=============関数==================//.
	void InitProcess();			//初期設定関数.
	void Update();					//更新処理関数.
	void Render();					//描画処理関数.
	void Release();					//解放処理関数.
	void Progress();				//前進処理.
	void Flashing(int count);		//点滅処理.
	void SetAnim(enPlyAct Act);		//アニメーション再生設定;

	//～情報取得処理関数～.
	//位置.
	float GetPositionX() { return m_PlayerParam.m_vPos.x; }
	float GetPositionY() { return m_PlayerParam.m_vPos.y; }
	float GetPositionZ() { return m_PlayerParam.m_vPos.z; }
	D3DXVECTOR3 GetPosition() { return m_PlayerParam.m_vPos; }
	//プレイヤーの状態,
	void SetPlayerAction(enPlyAct Act) { m_PlayerParam.m_Action = Act; }
	enPlyAct GetPlayerAction() { return m_PlayerParam.m_Action; }
	//ジャンプフラグ.
	void SetJumpFlag(bool flag) { m_PlayerParam.m_bJumpFlag = flag; }
	bool GetJumpFlag() { return m_PlayerParam.m_bJumpFlag; }

	//敵の位置設定関数.
	void SetEnemyPosition(D3DXVECTOR3 vPos) { m_vEnemyPosition = vPos; }
	//長押しされているか.
	void SetLongCommand(bool flag) { m_bLongCommandFlag = flag; }
	//位置を固定していいか.
	void SetFixedPosFlag(bool flag) { m_bFixedPosFlag = flag; }
	//開始時間は過ぎたか.
	void SetStartCountFlag(bool flag) { m_bStartCountFlag = flag; }
	void SetOperation(bool flag) { m_OperationFlag = flag; }
	//ジャンプが終わったか.
	bool GetJunpEndFlag() { return m_bJumpEndFlag; }
	//ゲームの終わりを取得.
	bool GetEndFlag() { return m_bEndFlag; }


private:
	//================列挙体==================//.
	//行動制御用.
	enum class enOperation
	{
		Possible = 0,		//可能.
		Impossible,			//不可能.

		Max,				//最大.
		Start = Possible,	//最初.
	};

	//================構造体==================//.
	//プレイヤーパラメータ.
	struct stPLAYER_PARAM
	{
		D3DXVECTOR3	m_vPos;			//位置情報.
		D3DXVECTOR3 m_vOldPos;		//移動前位置情報.
		bool		m_bDispFlag;	//表示フラグ.
		float		m_fAcc;			//加速(Acceleration).
		bool		m_bJumpFlag;	//ジャンプフラグ.
		enPlyAct	m_Action;		//アクション.
		enPlyAct	m_Old_Action;	//過去アクション.
		int			m_MoveCount_R;	//移動制御用カウント.
		int			m_MoveCount_L;	//移動制御用カウント.
		bool		m_SetAnimFlag;	//アニメーションセット用フラグ.
		int			m_Count;		//カウント.
		float		m_AnimSpeed;	//アニメーションの速さ.

		stPLAYER_PARAM()
			: m_vPos(0.0f, 0.0f, 4.0f)
			, m_vOldPos()
			, m_bDispFlag(false)
			, m_fAcc(0.0f)
			, m_bJumpFlag(false)
			, m_Action(enPlyAct::Max)
			, m_Old_Action(enPlyAct::Max)
			, m_MoveCount_R(0)
			, m_MoveCount_L(0)
			, m_SetAnimFlag(false)
			, m_Count(0)
			, m_AnimSpeed(0.0f)
		{}
	};

	//=====================定数======================//.
	const float POISITION_Z		= 4.0f;		//z座標.
	const float JUMP_POWER		= 0.13f;	//ジャンプ力.
	const float GRAVITY			= 0.01f;	//重力(加速度).
	const float	MOVING_RANGE	= 1.5f;		//移動範囲.
	const float MOVE_SPEED		= 0.035f;	//移動速度.
	const float ROTATION		= 3.15f;	//回転値.
	const float ANIM_SPEED		= 0.02f;	//アニメーション再生速度.
	const int   FIRST_MOVETIME	= 1;		//移動する時間.
	const int   SECOND_MOVETIME = 10;		//移動する時間.
	const int   ANIM_RUN		= 4;		//走るアニメーション.
	const int   ANIM_JUMP		= 3;		//ジャンプアニメーション.
	const int   ANIM_WAIT		= 1;		//待機アニメーション.
	const int   ANIM_ATTACK		= 2;		//攻撃アニメーション.
	const int   ANIM_PANIC		= 0;		//攻撃アニメーション.
	const int	SECONDS_COUNT	= 60;		//60フレームで割る.
	const int   FLASH_DIVIDE	= 120;		//点滅時間を割るフレーム.
	const int   TWO_DIVIDE		= 2;		//2で割る.
	const int   WAIT_END		= 8;		//待機戦の終わり時間.
	const int	GAME_END		= 10;		//ゲーム終わり時間.
	const float POSITION_ADJ	= 0.5f;		//位置調整.
	const int	EFFECT_MAX		= 2;		//エフェクト最大数.
	const int	STEP_EFFECT_NUM = 0;		//タヌキを踏むときのエフェクト番号.
	const int	LAND_EFFECT_NUM = 1;		//地面に着地したときのエフェクト番号.
	const float	ENEMY_DEPTH		= 1.5f;		//敵の高さ.
	const int   MOVE_START		= 240;		//動き始める時間.
	//============================.
	//		追加.
	const float	SHADOW_HIGHT = 0.03f;		//影の高さ.

	//=====================関数======================//.
	void Move(float range, int count);					//移動関数.
	void Jump();										//ジャンプ処理.

	//=====================変数======================//.
	clsXInput*								m_pCInput;				//コントローラクラス.
	stPLAYER_PARAM							m_PlayerParam;
	CDX9SkinMesh*							m_pCPlayerAnim;			//プレイヤーアニメーション.
	CResourceManager*						m_pCResourceManager;
	CSEPlayManager*							m_pCSEPlayManager;
	enOperation								m_enOperation;
	CDX9SkinMesh::CHANGE_TEXTURE*			m_pChangeTexture;		//テクスチャ切り替え.

	D3DXVECTOR3								m_vEnemyPosition;		//敵位置.
	bool									m_bEndFlag;				//ゲーム終了フラグ.
	int										m_frame;				//経過時間.
	int										m_WaitTime;				//待機時間.
	bool									m_bFixedPosFlag;		//位置固定フラグ.
	bool									m_bLongCommandFlag;		//長押しされているか.
	bool									m_OperationFlag;		//操作フラグ.
	bool									m_bJumpEndFlag;			//ジャンプが終わったか.
	bool									m_bStartCountFlag;		//ゲーム開始フラグ.
	int										m_StartCount;			//開始時間.
	int										m_FlashTime;			//点滅時間.
	//===============.
	//		追加.
	CSprite*								m_pCShadow;				//影.
};

#endif	//#ifndef CPLAYER_H
