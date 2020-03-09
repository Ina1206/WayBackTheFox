#ifndef CCHARA_H
#define CCHARA_H

#include "..\CGameObject.h"
#include "..\Collider_Detection/CCollision_Detection.h"
#include "..\Collider_Detection/CDebugCollisionSphere.h"


/********************************************
*		キャラクタクラス.
*****/
class CChara
	: public CGameObject
{
public:
	CChara();
	virtual ~CChara();

	//===================定数========================//.
	const int	FOOT_MAX			= 2;		//足の最大数.
	const float	HIT_FOOT_SCALE		= 0.2f;		//足の当たり判定大きさ.
	const float	HIT_GROUND_SCALE	= 0.8f;		//地面の当たり判定大きさ.
	const int	LEFT_FOOT_NUM		= 0;		//左足番号.
	const int	RIGHT_FOOT_NUM		= 1;		//右足番号.
	const int	HIT_GROUND_NUM		= 2;		//地面の番号.
	const int	FOOT_SPHERE_MAX		= 3;		//デバッグ用球体の最大数.
	const float GROUND_HIT_H		= -0.25f;	//地面の当たり判定の高さ.
	const float	SHADOW_HIGHT		= 0.05f;	//影の高さ.

	//===================関数========================//.
	void Init();																		//初期化処理関数.
	void Destroy();																		//解放処理関数.
	void FootStepSE(CDX9SkinMesh* pSkinMesh, CSoundResource::enSoundSE enSoundSE);	//足音のSE.
	void RenderDebug();																	//デバッグ用描画.

protected:
	void RenderShadow();									//影の描画処理関数.

	//===================変数========================//.
	CCollision_Detection**	m_ppCCollision_Detection;		//当たり判定のクラス.
	CDebugCollisionSphere**	m_ppCDebug_Collision_Sphere;	//当たり判定デバッグ用球体.
	D3DXVECTOR3*			m_pvFootPos;					//両足の座標.
	bool*					m_pbGroundHit;					//地面に足がついたかのフラグ.
	D3DXVECTOR3				m_vFootDownPos;					//足下の座標.
	D3DXVECTOR3				m_vShadowPos;		//影の座標.

private:
	CSprite*			m_pCSprite;			//スプライトクラス.

};

#endif	//#ifndef CCHARA_H.