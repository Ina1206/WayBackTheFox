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
//		�����������֐�.
//====================================.
void CChara::Init()
{
	//�z�񎩓��擾.
	m_ppCCollision_Detection = new CCollision_Detection*[FOOT_MAX]();		//�����蔻��p�N���X.
	m_ppCDebug_Collision_Sphere = new CDebugCollisionSphere*[FOOT_SPHERE_MAX]();//�f�o�b�O�p�����蔻�苅�̕`��N���X�擾.
	m_pvFootPos = new D3DXVECTOR3[FOOT_MAX]();					//�����̍��W.
	m_pbGroundHit = new bool[FOOT_MAX]();							//�n�ʂɑ����������̃t���O.

	//�����蔻��̃N���X.
	for (int collision = 0; collision < FOOT_MAX; collision++) {
		m_ppCCollision_Detection[collision] = new CCollision_Detection();
	}
	//�����蔻��`��N���X.
	for (int collision = 0; collision < FOOT_SPHERE_MAX; collision++) {
		m_ppCDebug_Collision_Sphere[collision] = new CDebugCollisionSphere();
	}

	//�����蔻�菉���ݒ�.
	for (int foot = 0; foot < FOOT_MAX; foot++) {
		m_ppCCollision_Detection[foot]->Init();
		m_ppCCollision_Detection[foot]->SetScale(0.2f, CCollision_Detection::enObject::Playre);
		m_ppCCollision_Detection[foot]->SetScale(0.8f, CCollision_Detection::enObject::Ground);
		m_pbGroundHit[foot] = false;
	}

}

//====================================.
//		��������֐�.
//====================================.
void CChara::Destroy()
{
	//�N���X���.
	//�����蔻�苅�̕`��N���X.
	for (int collision = FOOT_SPHERE_MAX - 1; collision >= 0; collision--) {
		SAFE_DELETE(m_ppCDebug_Collision_Sphere[collision]);
	}
	//�����蔻��N���X.
	for (int collision = FOOT_MAX - 1; collision >= 0; collision--) {
		SAFE_DELETE(m_ppCCollision_Detection[collision]);
	}

	//�z����.
	SAFE_DELETE_ARRAY(m_pbGroundHit);
	SAFE_DELETE_ARRAY(m_pvFootPos);
	SAFE_DELETE_ARRAY(m_ppCDebug_Collision_Sphere);
	SAFE_DELETE_ARRAY(m_ppCCollision_Detection);


}

//====================================.
//		������SE.
//====================================.
void CChara::FootStepSE(CDX9SkinMesh* pSkinMesh, CSoundResource::enSoundSE enSoundSE)
{
	

	//�{�[�����W�̎擾.
	pSkinMesh->GetPosFromBone("Left_foot", &m_pvFootPos[LEFT_FOOT_NUM]);	//����.
	pSkinMesh->GetPosFromBone("Right_foot", &m_pvFootPos[RIGHT_FOOT_NUM]);	//�E��.

	
	//�����̓����蔻��̐ݒ�.
	for (int foot = 0; foot < FOOT_MAX; foot++) {
		//�z�u.
		m_ppCDebug_Collision_Sphere[foot]->SetPos(m_pvFootPos[foot]);
		//�傫��.
		m_ppCDebug_Collision_Sphere[foot]->SetScale(0.2f);
	}

	//�n�ʂ̓����蔻��̐ݒ�.
	//�z�u.
	m_ppCDebug_Collision_Sphere[HIT_GROUND_NUM]->SetPos(m_vFootDownPos);
	//�傫��.
	m_ppCDebug_Collision_Sphere[HIT_GROUND_NUM]->SetScale(0.8f);

	for (int foot = 0; foot < FOOT_MAX; foot++) {
		//�v���C���[�̐ݒ�.
		CCollision_Detection::stObjectInfo stPlayer;
		stPlayer.Object = CCollision_Detection::enObject::Playre;
		stPlayer.vPos = m_pvFootPos[foot];

		//�n�ʑ��̐ݒ�.
		CCollision_Detection::stObjectInfo stGround;
		stGround.Object = CCollision_Detection::enObject::Ground;
		stGround.vPos = m_vFootDownPos;

		if (m_ppCCollision_Detection[foot]->JugeHit(&stPlayer, &stGround)) {
			//SE�̍Đ�.
			if (m_pbGroundHit[foot] == false) {
				m_pCSEPlayManager->SetSEPlayFlag(enSoundSE, true);
				m_pbGroundHit[foot] = true;
			}
		}
		else {
			//�������ĂȂ��Ƃ�.
			m_pbGroundHit[foot] = false;
		}
	}

}

//====================================.
//		�f�o�b�O�p�`��.
//====================================.
void CChara::RenderDebug()
{
	for (int collision = 0; collision < FOOT_SPHERE_MAX; collision++) {
		m_ppCDebug_Collision_Sphere[collision]->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}
}

//=========================================.
//		�e�̕`�揈���֐�.
//=========================================.
void CChara::RenderShadow()
{
	m_vShadowPos.y = 0.05f;
	m_pCSprite = CResourceManager::GetResourceManagerInstance()->GetSprite(CResourceSprite::enSprite::Shadow);
	m_pCSprite->SetPosition(m_vShadowPos);
	m_pCSprite->SetCancelRotationFlag(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
}