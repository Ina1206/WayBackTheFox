#include "CChara.h"

CChara::CChara()
	: m_ppCCollision_Detection(nullptr)
	, m_ppCDebug_Collision_Sphere(nullptr)
	, m_pvFootPos(nullptr)
	, m_pbGroundHit(nullptr)
	, m_pCSprite(nullptr)
{
}

CChara::~CChara()
{
}

//====================================.
//		初期化処理関数.
//====================================.
void CChara::Init()
{
	//配列自動取得.
	m_ppCCollision_Detection = new CCollision_Detection*[FOOT_MAX]();		//当たり判定用クラス.
	m_ppCDebug_Collision_Sphere = new CDebugCollisionSphere*[FOOT_SPHERE_MAX]();//デバッグ用当たり判定球体描画クラス取得.
	m_pvFootPos = new D3DXVECTOR3[FOOT_MAX]();					//両足の座標.
	m_pbGroundHit = new bool[FOOT_MAX]();							//地面に足がついたかのフラグ.

	//当たり判定のクラス.
	for (int collision = 0; collision < FOOT_MAX; collision++) {
		m_ppCCollision_Detection[collision] = new CCollision_Detection();
	}
	//当たり判定描画クラス.
	for (int collision = 0; collision < FOOT_SPHERE_MAX; collision++) {
		m_ppCDebug_Collision_Sphere[collision] = new CDebugCollisionSphere();
	}

	//当たり判定初期設定.
	for (int foot = 0; foot < FOOT_MAX; foot++) {
		m_ppCCollision_Detection[foot]->Init();
		m_ppCCollision_Detection[foot]->SetScale(0.2f, CCollision_Detection::enObject::Playre);
		m_ppCCollision_Detection[foot]->SetScale(0.8f, CCollision_Detection::enObject::Ground);
		m_pbGroundHit[foot] = false;
	}

}

//====================================.
//		解放処理関数.
//====================================.
void CChara::Destroy()
{
	//クラス解放.
	//当たり判定球体描画クラス.
	for (int collision = FOOT_SPHERE_MAX - 1; collision >= 0; collision--) {
		SAFE_DELETE(m_ppCDebug_Collision_Sphere[collision]);
	}
	//当たり判定クラス.
	for (int collision = FOOT_MAX - 1; collision >= 0; collision--) {
		SAFE_DELETE(m_ppCCollision_Detection[collision]);
	}

	//配列解放.
	SAFE_DELETE_ARRAY(m_pbGroundHit);
	SAFE_DELETE_ARRAY(m_pvFootPos);
	SAFE_DELETE_ARRAY(m_ppCDebug_Collision_Sphere);
	SAFE_DELETE_ARRAY(m_ppCCollision_Detection);


}

//====================================.
//		足音のSE.
//====================================.
void CChara::FootStepSE(CDX9SkinMesh* pSkinMesh, CSoundResource::enSoundSE enSoundSE)
{
	

	//ボーン座標の取得.
	pSkinMesh->GetPosFromBone("Left_foot", &m_pvFootPos[LEFT_FOOT_NUM]);	//左足.
	pSkinMesh->GetPosFromBone("Right_foot", &m_pvFootPos[RIGHT_FOOT_NUM]);	//右足.

	
	//足元の当たり判定の設定.
	for (int foot = 0; foot < FOOT_MAX; foot++) {
		//配置.
		m_ppCDebug_Collision_Sphere[foot]->SetPos(m_pvFootPos[foot]);
		//大きさ.
		m_ppCDebug_Collision_Sphere[foot]->SetScale(0.2f);
	}

	//地面の当たり判定の設定.
	//配置.
	m_ppCDebug_Collision_Sphere[HIT_GROUND_NUM]->SetPos(m_vFootDownPos);
	//大きさ.
	m_ppCDebug_Collision_Sphere[HIT_GROUND_NUM]->SetScale(0.8f);

	for (int foot = 0; foot < FOOT_MAX; foot++) {
		//プレイヤーの設定.
		CCollision_Detection::stObjectInfo stPlayer;
		stPlayer.Object = CCollision_Detection::enObject::Playre;
		stPlayer.vPos = m_pvFootPos[foot];

		//地面側の設定.
		CCollision_Detection::stObjectInfo stGround;
		stGround.Object = CCollision_Detection::enObject::Ground;
		stGround.vPos = m_vFootDownPos;

		if (m_ppCCollision_Detection[foot]->JugeHit(&stPlayer, &stGround)) {
			//SEの再生.
			if (m_pbGroundHit[foot] == false) {
				m_pCSEPlayManager->SetSEPlayFlag(enSoundSE, true);
				m_pbGroundHit[foot] = true;
			}
		}
		else {
			//当たってないとき.
			m_pbGroundHit[foot] = false;
		}
	}

}

//====================================.
//		デバッグ用描画.
//====================================.
void CChara::RenderDebug()
{
	for (int collision = 0; collision < FOOT_SPHERE_MAX; collision++) {
		m_ppCDebug_Collision_Sphere[collision]->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}
}

//=========================================.
//		影の描画処理関数.
//=========================================.
void CChara::RenderShadow()
{
	m_vShadowPos.y = 0.05f;
	m_pCSprite = CResourceManager::GetResourceManagerInstance()->GetSprite(CResourceSprite::enSprite::Shadow);
	m_pCSprite->SetPosition(m_vShadowPos);
	m_pCSprite->SetCancelRotationFlag(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
}