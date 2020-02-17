#ifndef CITEM_MOVE_H
#define CITEM_MOVE_H

#include "CItem_Base.h"
#include "..\..\Sound\CSoundResource.h"

class CItemMove
{
public:
	CItemMove();
	~CItemMove();
	//=================関数===================//.
	void Init_Process(D3DXVECTOR3 vPos);		//初期化処理関数.
	void UpDate(bool disp, enItemJudge judge, D3DXVECTOR3 IconPos);				//更新処理関数.
	void Collection();			//アイテム回収関数.
	void Collection_Boss();		//ボスアイテム回収関数.
	void Drop();				//アイテム落とす関数.
	void Drop_Boss();			//ボスアイテム落とす関数.

								//～情報置換処理関数～.
	void SetItemPosition(D3DXVECTOR3 vPos)	{ m_vPos = vPos; }				//アイテム位置.
	void SetIconPosition(D3DXVECTOR3 vPos)	{ m_vIconPos = vPos; }			//アイコン位置.
	void SetDispFlag(bool flag)				{ m_bDispFlag = flag; }			//描画フラグ.
	void SetItemJudge(enItemJudge enJudge)	{ m_enItemJudge = enJudge; }	//アイテムの判定.
	void SetNumber(int Num)					{ m_Num = Num; }				//アイテム番号.
	void SetItemSum(int num)				{ m_Sum = num; }				//アイテムの合計.
	void SetBossFlag(bool flag)				{ m_BossFlag = flag; }			//ボスのコマンドが失敗したか.

	//～情報取得関数～
	D3DXVECTOR3 GetItemPosition()	{ return m_vPos; }						//位置情報.
	bool GetCollectionItem()		{ return m_CollectionItem; }			//回収したアイテムの個数.

private:
	//=================関数===================//.
	void Release();			//解放処理関数.
	void Bounce();				//アイテムバウンド関数.
	void Absorption();			//アイコンに吸収される関数.


	//アクション状態.
	enum class enItemAct {
		Bounce = 0,		//バウンド.
		Absorption,		//吸収.
		Flow,			//流れていく.
		Wait,			//待機.

		MAX,
		Start = Bounce,
	};

	//================定数==================//.
	const D3DXVECTOR3 DROP_ITEMPOS	= D3DXVECTOR3(0.0f, 0.2f, 0.07f);
	const float DISP_POS			= -1.0f;							//描画位置最大.
	const float BOUNCE_POS			= -1.0f;							//バウンド最低y座標.
	const float BOUNCE_SPEED		= 0.013f;							//バウンド速度.
	const float BOUNCESPEED_BOSS_S	= 0.02f;							//バウンド速度.
	const float BOUNCESPEED_BOSS_F	= 0.008f;							//バウンド速度.
	const float FJUMP_POWER			= 0.05f;							//ジャンプ力.
	const float FGRAVITY			= 0.007f;							//重力(加速度).
	const float SPEED				= 0.1f;								//速度.
	const float ROTATION			= 10.0f;							//回転角.
	const double M_PI				= 3.14159265358979323846;			//円周率.
	const float VECTOR_SPEED		= -1.0f;							//ベクトル速度.
	const float DEGREE				= 180.0f;							//度数.
	const int	BOUNCE_COUNR_MAX	= 50;								//バウンドの最大時間.
	const int	COLLITION_NUMBER	= 1;								//落としたアイテムの個数.
	const float SPEED_ADJ			= 0.008f;							//速さ調整.
	const float BOSS_SPEED_ADJ		= 0.0f;							//速さ調整.
	const int	WAIT_TIME			= 250;								//待機時間.

	//================変数==================//.	
	D3DXVECTOR3			m_vPos;					//アイテムの位置.
	D3DXVECTOR3			m_vIconPos;				//アイコンの位置.
	bool				m_bDispFlag;			//描画フラグ.
	enItemJudge			m_enItemJudge;			//アイテムの判定.
	//---ジャンプ関連---.
	bool				m_bBounceFlag;			//跳ねるフラグ.
	int					m_BounceCount;			//跳ねた回数カウント.
	float				m_fAcc;					//加速.
	float				m_fSpeed;				//吸収される速度.
	float				m_fDirect;				//吸収される方向.
	float				m_fSpdSpin;				//回転角.

	enItemAct			m_enAction;				//アクション状態.
	int					m_Num;					//アイテム番号;
	bool				m_CollectionFlag;		//アイテムを回収したか.
	int					m_CollectionItem;		//アイテムを回収したか.
	int					m_Sum;					//アイテムの合計.
	bool				m_BossFlag;				//ボスフラグ.

	//---SE関連---.
	CSEPlayManager*		m_pCSEPlayManager;
	bool				m_bCheckSE;

};		

#endif//#ifndef CITEM_MOVE_H
