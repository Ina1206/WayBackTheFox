#include "CCameraManager.h"

CCameraManager::CCameraManager()
	: m_pCCamera			(nullptr)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_mView				()
	, m_bLongPush			(false)
	, m_bOldLongPush		(false)
	, m_enInput_Decision	(enInput_Decision::Max)
	, m_enOldInput_Decision	(enInput_Decision::Max)
	, m_bChangeMove			(false)
	, m_vTargetPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�J�n���͕W���J������.
	m_pCCamera = new CStanderdCamera();
}

CCameraManager::~CCameraManager()
{
	Release();
}

//================================.
//		�J�����ύX�����֐�.
//================================.
void CCameraManager::ChangeCamera()
{
	//==================���������̃J�����ړ�====================//.
	if (m_bLongPush != m_bOldLongPush) {
		//�����������Ƃ��ɃJ��������Ɉړ�����N���X��.
		if (m_bLongPush == true) {
			SAFE_DELETE(m_pCCamera);
			m_pCCamera = new CUpCamera();
		}
	}

	//===================�{�X�펞�̃J�����ړ�====================//.
	if (m_enInput_Decision == enInput_Decision::Bad && m_enInput_Decision != m_enOldInput_Decision) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CBossBadCamera();
	}
	if (m_enInput_Decision == enInput_Decision::Great && m_enInput_Decision != m_enOldInput_Decision) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CBossGreatCamera();
	}

	//======================�ʏ펞�̃N���X��=====================//.
	if (m_pCCamera->GetCameraChangeFlag() == true && m_enInput_Decision == enInput_Decision::Max) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CStanderdCamera();
	}

	//�t���O����.
	m_bOldLongPush = m_bLongPush;				//�������p�t���O.
	m_enOldInput_Decision = m_enInput_Decision;	//���菈��.
}

//================================.
//		�X�V�����֐�.
//================================.
void CCameraManager::UpDate()
{
	//�r���[�s��ϊ������֐�.
	m_pCCamera->Change_mView();

	m_pCCamera->SetTargetPos(m_vTargetPos);
	m_pCCamera->UpDate(m_bChangeMove);

	//�l�擾.
	m_vPos = m_pCCamera->GetCameraPos();
	m_mView = m_pCCamera->GetMATRIX_View();
}

//================================.
//		��������֐�.
//================================.
void CCameraManager::Release()
{
	SAFE_DELETE(m_pCCamera);
}