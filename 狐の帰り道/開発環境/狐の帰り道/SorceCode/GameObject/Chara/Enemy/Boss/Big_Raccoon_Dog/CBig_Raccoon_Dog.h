#ifndef CBIG_RACCOON_DOG_H
#define CBIG_RACCOON_DOG_H

#include "..\..\CEnemyBase.h"
#include "..\..\..\..\..\Command\BarrageCommand\CBarrageCommand.h"

/***************************************
*	デカタヌキクラス.
**/
class CBig_Raccoon_Dog
	: public CEnemyBase
{
public:
	CBig_Raccoon_Dog();
	~CBig_Raccoon_Dog();

	//=======================定数========================//.
	//タイム.
	const float			MAX_TIME			= 15.0f;							//タイムの最大値.
	const float			FRAME				= 60.0f;							//フレーム.
	//動き.
	const int			WAIT_TIME			= 120;								//待機時間.
	const float			STANDERD_POS_H		= 0.8f;								//デカタヌキの基準高さ.
	const float			BEHINE_DOWN_SPEED	= 0.002f;							//後ろに倒れる速度.
	const float			PREVIOUS_DOWN_SPEED = 0.005f;							//前に倒れる速度.
	const float			ADJUSTMENT_HIGHT	= 0.003f;							//調整高さ.
	const float			ROTATION_MIN		= -1.7f;							//回転角度の最小値.
	const float			ROTATION_MAX		= -1.2f;							//回転角度の最大値.
	const float			START_ROTATION		= -1.5f;							//初めの角度.
	const float			ANIM_CHANGE_ROT		= -1.6f;							//アニメーションを変更する角度.
	const float			ANIM_SPEED_MAX		= 0.005f;							//アニメーション速度の最大値.
	const float			ANIM_SPEED_MIN		= 0.0f;								//アニメーション速度最小値.
	//ポコポコ鳴らす用.
	const int			HANDLE_MAX			= 2;								//手の合計数.
	const int			LEFT_HANDLE_NUM		= 0;								//左手の番号.
	const int			RIGHT_HANDLE_NUM	= 1;								//右手の番号.
	const int			HIT_TARGET_MAX		= 1;								//当たる相手側の最大値.
	const int			HIT_TARGET_NUM		= 2;								//当たる相手側の番号.
	const float			PLAYER_HIT_SCALE	= 0.2f;								//プレイヤーの手の当たり判定の大きさ.
	const float			BOSS_HIT_SCALE		= 1.5f;								//ボスの当たり判定の大きさ.
	const D3DXVECTOR3	HIT_BOSSPOS_ADJUST	= D3DXVECTOR3(0.0f, 1.0f, -1.5f);	//ボス側の当たり判定の微調整.
	//当たって回転していく.
	const float			HIT_ROTATION_SPEED	= 0.01f;							//当たって回転する速度.
	const float			HIT_ROT_SPEED_UP	= 0.005f;							//回転速度を増やす.
	const float			HIT_MOVE_SPEED		= 0.04f;							//当たって飛んでいくスピード.
	const float			FLY_MAX				= 5.5f;								//飛ぶ高さ最大数.
	const float			CENTER_AXIS_DIFF	= -50.0f;							//現在の中心軸と希望している中心軸の差.
	const float			ONE_ROTATION_MIN	= 6.2f;							//一回転の最小値.
	const float			BACK_SPEED			= 0.0001f;							//少し奥に移動する速度.
	//倒れるとき.
	const int			FALL_DOWN_WAIT_TIME = 50;								//倒れるときの待ち時間.
	const float			FALL_DOWN_ROT_MIN	= -3.5f;							//倒れるときの角度最小値.
	const D3DXVECTOR3	ADJUST_MOVE_SPEED	= D3DXVECTOR3(0.0f, 0.025f, 0.15f);	//倒れるときの調整速度.
	const float			FALL_DOWN_SPEED_UP	= 0.012f;							//倒れるときの速度を上げていく速度.
	//エフェクト.
	const int			EFFECT_MAX			= 3;								//エフェクトの最大数.
	const int			HIT_FLY_EFFECT_NUM	= 0;								//飛んでいくエフェクト番号.
	const int			FALLDOWN_EFFECT_NUM = 1;								//倒れるときのエフェクト番号.
	const int			PUNCH_EFFECT_NUM	= 2;								//パンチが当たった時のエフェクト.
	const float			ALPHA_MAX			= 1.0f;								//透過値最大数.
	const float			STAR_SCALE_SPEED	= 0.07f;								//星の拡縮速度.
	const float			STAR_MAX			= 1.2f;								//星の大きさの最大値.
	const float			STAR_MIN			= 0.0f;								//星の大きさの最小値.
	//コマンド.
	const int			COMMAND_BUTTON_MAX	= 3;								//コマンドボタン最大値.

	//======================列挙体=======================//.
	//デカタヌキのアニメーション種類.
	enum class enAnimType {
		Finish = 0,		//終了後.
		Swing,			//揺れる.
		Noting,			//無し.

		Max,			//最大.
		Start = Finish,	//開始.
	};
	//回転時のZ移動.
	enum class enRotation_Move {
		Previous = 0,		//前.
		Behind,				//後ろ.

		Max,				//最大値.
		Start = Previous,	//始まり.
	};
	//星の拡縮.
	enum class enStarScaling {
		Scale = 0,	//拡大.
		Scale_Down,	//縮小.
		Finish,		//終了.
	};

	//=======================関数========================//.
	void InitProcess();	//初期化処理関数.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.
	void Release();			//解放処理関数.

	//～情報獲得処理関数～.
	D3DXVECTOR3			GetRotation() { return m_vRot; }										//角度獲得処理.
	bool				GetCommandStart() { return m_bCommandDispStart; }						//コマンド表示開始フラグ獲得処理.
	enInput_Decision	GetInputDecision() { return m_pCCommand_Base->GetInputDeision(); }		//コマンド判定結果.
	bool				GetMoveStart() { return m_bMoveStart; }									//行動開始フラグ獲得処理.

	//～情報置換処理関数～.
	void SetMove(bool flag) { m_bMoveStart = flag; }											//行動開始フラグ.	
	void SetUpDistance(float Distance) { m_fUpDistance = Distance; }							//上に上がる距離.	
	void SetButtonNum(int ButtonNum, int Num) { m_pButtonNum[Num] = ButtonNum; }				//ボタン番号.

	void SetInputDecision(enInput_Decision InputDecision) { m_enInputDecision = InputDecision; }

private:
	//=======================定数========================//.
	void MoveJudgement();			//行動処理関数.
	void MoveHit();					//当たった時の処理関数.
	void Falldown();				//倒れるときの処理関数.
	void HitSound();				//殴られた時の音処理関数.
	void FlyAfter();				//飛んだあとの処理関数.

	//=======================変数========================//.
	CDX9Mesh*			m_pCStaticMesh;		//メッシュ.
	CDX9Mesh*			m_pCMesh;			//メッシュ.
	CDX9SkinMesh*		m_pCSkinMesh;		//アニメーションメッシュ.
	CSprite*			m_pCStar;			//星のスプライト用クラス.

	int*				m_pButtonNum;		//ボタン番号.
	enInput_Decision	m_enInputDecision;	//入力結果.
	enInput_Decision	m_enOldInDecision;	//前回の入力結果.
	bool				m_bCommandDispStart;//コマンド表示開始フラグ.

	enRotation_Move		m_enRotation_Move;	//回転時の移動.
	enRotation_Move		m_enRotationType;	//傾く種類.
	float				m_fFall_Down_Speed;	//倒れる速度.
	D3DXVECTOR3			m_vSwingBefore_Pos;	//地面が揺れる前の座標.
	float				m_fScale;			//大きさ.

	bool				m_bInputSE_Check;	//コマンド入力終了時のSE.
	bool				m_bMoveStart;		//タイマー.				
	float				m_fUpDistance;		//上に上がる距離.			
	float				m_fAnimSpeed;		//アニメーション速度.
	enAnimType			m_enAnimType;		//アニメーションの種類.
	bool				m_bAnimChange;		//アニメーション変更フラグ.

	D3DXVECTOR3*		m_pvPlayerHandlePos;//プレイヤーの手の位置.
	bool*				m_pbHitHandleFlag;	//手が当たった時のフラグ.

	int					m_Cnt;				//カウント.
	int					m_WaitCnt;			//時間のカウント.

	float				m_fHitRotation;		//回転.

	D3DXVECTOR3			m_vStarPos;			//星の位置.
	float				m_fStarScale;		//星の大きさ.
	enStarScaling		m_enStarScaling;	//星の拡縮タイプ.
	D3DXVECTOR3			m_vPrePos;			//表示ズレ.
};

#endif	//#ifndef CBIG_RACCOON_DOG_H.