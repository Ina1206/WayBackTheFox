#ifndef CITEM_BASE
#define CITEM_BASE

#include "..\..\GameObject\CGameObject.h"
#include "..\..\Command\enumCommand_Global.h"
#include "enItemType.h"

/******************************************************
*		アイテムの元となるクラス.
*/
class CItem_Base
{
public:
	//====================定数======================//.
	const int ITEM_MIN = 1;
	const int ITEM_MAX = 2;
	const float BOSS_ITEM_POSITION_X = 2.0f;
	const float BOSS_ITEM_POSITION_Z = 1.0f;

	CItem_Base();
	virtual ~CItem_Base();

	//=================関数===================//.
	void Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);
	virtual void Init_Process()	= 0;	//初期化関数.
	virtual void UpDate()		= 0;	//更新処理関数.
	virtual void Render()		= 0;	//描画処理関数.
	virtual void Release()		= 0;	//解放処理関数.
	virtual void ItemCount()	= 0;	//アイテムの合計処理関数.

	//～情報獲得関数～.
	D3DXVECTOR3		GetPosition() { return m_vPos; }
	int				GetPointSum() { return m_Point; }
	bool			GetDispFlag() { return m_bDispFlag; }
	int				GetDropNum() { return m_DropNum; }
	int				GetCollitionNum() { return m_CollitionNum; }
	enInput_Decision GetInput_Decision(){ return m_enInputDecision; }
	enItemJudge     GetItemJudge() { return m_enItemJudge; }

	//～情報置換処理関数～.
	void SetPotition(D3DXVECTOR3 vPos)			{ m_vPos = vPos; }									//位置.
	void SetPlayerPos(D3DXVECTOR3 vPlayerPos)	{ m_vPlayerPos = vPlayerPos; }				//プレイヤー位置.
	void SetIconPos(D3DXVECTOR3 vIconPos)		{ m_vIconPos = vIconPos; }						//アイコン位置.
	void SetInputDecision(enInput_Decision enDecision) { m_enInputDecision = enDecision; }	//コマンド判定結果.
	void SetItemJudge(enItemJudge enJudge)		{ m_enItemJudge = enJudge; }
	void SetDispFlag(bool flag)					{ m_bDispFlag = flag; }										//表示判定.
	void SetItemSum(int num)					{ m_Sum = num; }
	void SetBossFlag(bool flag)					{ m_BossFlag = flag; }										//ボスフラグ.

protected:

	//=================変数===================//.
	D3DXVECTOR3			m_vCameraPos;			//カメラ位置.
	D3DXMATRIX			m_mView;				//ビュー行列.
	D3DXMATRIX			m_mProj;				//プロジェクション行列.

	CResourceManager*	m_pCResourceManager;	//読み込み管理クラス.
	CSprite**			m_pCSprite;				//スプライトクラス.
	CDepth_Stencil*		m_pCDepth_Stencil;		//デプスステンシルクラス.

	D3DXVECTOR3			m_vPos;					//位置情報.
	D3DXVECTOR3			m_vInitPos;				//初期値.
	D3DXVECTOR3			m_vPlayerPos;			//プレイヤー座標.
	D3DXVECTOR3			m_vIconPos;				//アイコン座標.

	enInput_Decision	m_enInputDecision;		//判定結果.
	enItemJudge			m_enItemJudge;
	int					m_DropNum;				//アイテムの落ちる数.
	int					m_CollitionNum;			//回収したアイテムの数.
	bool				m_bDispFlag;			//表示フラグ.
	int					m_Sum;					//個数合計.
	int					m_Point;				//ポイント.
	bool				m_BossFlag;				//ボスのコマンド失敗したか.
	bool				m_bCheckBossFlag;		//ボスフラグのチェック.


private:
};

#endif//#ifndef CITEM_BASE
