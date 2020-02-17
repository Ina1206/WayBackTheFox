#ifndef CCOMMAND_BASE_H
#define CCOMMAND_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Command\enumCommand_Global.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"
#include "..\Sound\CSEPlayManager.h"


#include "..\Effect\SparkleEffect\GreatEffect\CGreatEffect.h"
#include "..\Effect\SparkleEffect\GoodEffect\CGoodEffect.h"

/************************************************
*		コマンドの元となるクラス.
**/
class CCommand_Base
{
public:
	CCommand_Base();
	virtual ~CCommand_Base();

	//===================定数=======================//.
	const int	COMMAND_DECISION_MAX	= 2;			//コマンド判定最大数.
	const int	STANDERD_COMMAND_USE	= 0;			//基本的に使うコマンドの要素番号.
	const float ALPHA_MAX			= 1.0f;				//透過値最大.
	const float ALPHA_MIN			= 0.6f;				//透過値最小.
	const float	LIGHT_SCALE_MAX		= 2.0f;				//ボタンの光の大きさ最大数.			
	const float LIGHT_SCALE_MIN		= 1.0f;				//ボタンの光の大きさ最小値.
	const float LIGHT_ALPHA_MAX		= 1.0f;				//ボタンの光の透過値最大値.
	const float LIGHT_ALPHA_MIN		= 0.0f;				//ボタンの光の透過値最小値.

	//===================関数=======================//.
	void	Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//値設定処理関数.
	virtual void UpDate(enCommandType CommandType) = 0;								//更新処理関数.
	virtual void Render() = 0;														//描画処理関数.
	void	EffectAndSE_Play();														//SE再生処理関数.
	void	EffectRender();															//エフェクト描画.

	//～情報置換処理関数～.
	//敵の個人の座標.
	void	SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }												
	//通常敵のボタン.
	void	SetButtonNum(int ButtonNum) { m_ButtonNum = ButtonNum; }								
	//ボスのボタン.
	void	SetMultipleButtonNum(int ButtonNum, int Button) { m_pButtonNum[Button] = ButtonNum; }	
	//Playerの座標.
	void	SetPlayerPos(D3DXVECTOR3 PlayerPos) { m_vPlayerPos = PlayerPos; }						
	//ボスコマンド表示フラグ.
	void	SetDispFlag(bool flag) { m_bDispFlag = flag; }											
	//コマンド判定可能フラグ.
	void	SetJudgePossible(bool flag) { m_bJudgePossible = flag; }								
	//タイミング字のコマンドの座標.
	void	SetDispHight(float Pos) { m_fDispHight = Pos; }											
	//長押しカウント.
	void	SetLongPushCnt(int Cnt) { m_LongPushCnt = Cnt; }										
	//～情報取得処理関数～.
	enInput_Decision GetInput_Deision(int command = 0) { return m_penInput_Decision[command]; }		
	bool GetButtonLightFinish() { return m_bButtonLightFinish; }

protected:
	//===================関数========================//.
	virtual void Release() = 0;														//解放処理関数.
	virtual void DispDecision() = 0;												//表示判定処理関数.
	virtual void CommandDecision(enCommandType CommandType) = 0;					//コマンド判定処理関数.

	void	Init();																	//初期設定処理関数.
	void	Button_Render();														//ボタン描画処理関数.

	//===================変数========================//.
	D3DXVECTOR3			m_vCameraPos;			//カメラ位置.
	D3DXMATRIX			m_mView;				//ビュー行列.
	D3DXMATRIX			m_mProj;				//プロジェクション行列.

	CResourceManager*	m_pCResourceManager;	//読み込み管理クラス.
	CSprite*			m_pCSprite;				//スプライトクラス.
	CDepth_Stencil*		m_pCDepth_Stencil;		//デプスステンシルクラス.
	float				m_fAlpha;				//透過値.

	D3DXVECTOR3			m_vPos;					//位置情報.
	D3DXVECTOR3			m_vInitPos;				//初期位置.
	float				m_fDispHight;			//表示高さ.
	int					m_ButtonNum;			//ボタン番号.
	int*				m_pButtonNum;			//ボタン番号(複数の場合).
	enInput_Decision*	m_penInput_Decision;	//成功判定.
	enInput_Decision*	m_penOld_Decision;		//前回の判定.
	bool				m_bDispFlag;			//表示フラグ.
	bool				m_bJudgePossible;		//判定可能フラグ.
	int					m_LongPushCnt;			//長押し防止カウント.

	D3DXVECTOR3			m_vPlayerPos;			//プレイヤーの位置情報.

	CSEPlayManager*		m_pCSEPlayManager;		//SE再生クラス.

	CEffectBase**		m_ppCEffectBase;		//エフェクトベースクラス.

	CSprite*			m_pCButtonLightSprite;	//ボタンの光のスプライトクラス.
	float				m_fButtonLightAlpha;	//ボタンの光透過値.
	float				m_fButtonLightScale;	//ボタンの光大きさ.

	bool				m_bButtonLightFinish;	//ボタンの光終了.

private:
};

#endif	//#ifndef CCOMMAND_BASE_H.