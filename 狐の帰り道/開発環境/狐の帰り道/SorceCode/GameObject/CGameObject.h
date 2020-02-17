#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H


//---描画---//.
#include "..\Drawing\3D_Object\CDX9Mesh.h"
#include "..\Drawing\Resource\CResourceManager.h"

#include "..\Sound\CSEPlayManager.h"

#include "..\Effect\HitEffect\CHitEffect.h"
#include "..\Effect\SparkleEffect\GreatEffect\CGreatEffect.h"
#include "..\Effect\FlyEffect\EnemyFlyEffect\CEnemyFlyEffect.h"
#include "..\Effect\FlyEffect\BossFlyEffect\CBossFlyEffect.h"
#include "..\Effect\FallDownEffect\CFallDownEffect.h"
#include "..\Effect\SparkleEffect\PunchEffect\CPunchEffect.h"
#include "..\Effect\SparkleEffect\StepEffect\CStepEffect.h"
#include "..\Effect\\LndingEffect\CLandingEffect.h"
#include "..\Effect\HorizonMoveEffect\CHorizonMoveEffect.h"

/***************************************
*		ゲームオブジェクトクラス.
**/
class CGameObject
{
public:
	//=============定数==================//.
	const float SCALE_SIZE = 0.02f;		//スケールサイズ.

	CGameObject();
	virtual ~CGameObject();
	//=============関数==================//.
	void Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);		//値セット処理関数.
	virtual void Init_Process() = 0;																		//初期化処理関数.
	virtual void UpDate() = 0;																				//更新処理関数.
	virtual void Render() = 0;																				//描画処理関数.
	virtual void Release() = 0;																				//解放処理関数.
	
protected:

	D3DXVECTOR3				m_vLight;						//ライトの方向.
	D3DXVECTOR3				m_vCameraPos;					//カメラ位置.
	D3DXMATRIX				m_mView;						//ビュー行列.
	D3DXMATRIX				m_mProj;						//プロジェクション行列.

	CSEPlayManager*			m_pCSEPlayManager;				//サウンド再生管理クラス.
	CEffectBase*			m_pCEffectBase;					//エフェクトクラス.	(あとで削除)
	CEffectBase**			m_ppCEffectBase;				//エフェクトクラス.

private:

};

#endif //#ifndef CGAMEOBJECT_H.