#include "CFaceIcon.h"

CFaceIcon::CFaceIcon()
	: m_ppCFaceIcon	(nullptr)
	, m_pCSEPlayManager(nullptr)
{
	m_ppCFaceIcon = new CSpriteUI*[FACE_SPRITEUI_MAX];
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CFaceIcon::~CFaceIcon()
{
	Release();
}

//---------------------------------------.
//	�X�V�����֐�.
//---------------------------------------.
void CFaceIcon::UpDate()
{
	int m_UpFaceType = m_OldFaceType + 1;	//���̊�̎��.
	int m_DownFaceType = m_OldFaceType - 1;	//����̊�̎��.
	//�\���i�K�オ��������SE.
	if (m_FaceType == m_UpFaceType) {
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Facial_UpChange, true);
	}
	//�\���i�K������������SE.
	if (m_FaceType == m_DownFaceType) {
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Facial_DownChange, true);
	}

	m_OldFaceType = m_FaceType;
}

//---------------------------------------.
//	�`�揈���֐�.
//---------------------------------------.
void CFaceIcon::Render()
{
	for (int icon = 0; icon < FACE_MAXSMILE_BACK; icon++)
	{
		int IconNum = static_cast<int>(CResourceSpriteUI::enSpriteUI::faceIcom_Normal) + icon;
		m_ppCFaceIcon[icon] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(IconNum));
	}
	for (int icon = 0; icon < 3; icon++)
	{
		int IconNum = static_cast<int>(CResourceSpriteUI::enSpriteUI::Face_High_Back) + icon;
		m_ppCFaceIcon[ FACE_MAXSMILE_BACK + icon ] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(IconNum));
	}

	//�A�C�R���ʒu.
	D3DXVECTOR3 m_vFace_Pos = FACEICON_POS;
	D3DXVECTOR3 m_vFace_Back_Pos = FACEICON_POS;
	m_vPos.x = FACEICON_AMOUNT_POS.x;
	m_vPos.y = FACEICON_AMOUNT_POS.y;

	for (int face = 0; face < FACE_SPRITEUI_MAX; face++)
	{
		if (face < FACE_AMOUNT) {
			m_ppCFaceIcon[face]->SetPosition(m_vFace_Pos);
		}
		else if(face == FACE_AMOUNT) {
			m_ppCFaceIcon[face]->SetPosition(m_vPos);
		}
		else
		{
			m_ppCFaceIcon[face]->SetPosition(m_vFace_Back_Pos);
		}
	}

	for (int icon = 0; icon < FACE_SPRITEUI_MAX; icon++)
	{
		//�`��.
		m_pCDepth_Stencil->SetDepth(false);
		if (m_PointSum < MIDDLE_POINT)
		{
			m_ppCFaceIcon[FACE_NORMAL_BACK]->Render();
			m_ppCFaceIcon[FACE_NORMAL]->Render();
			m_FaceType = FACE_NORMAL;
		}
		else if (m_PointSum >= MIDDLE_POINT && m_PointSum < HIGH_POINT)
		{
			m_ppCFaceIcon[FACE_SMILE_BACK]->Render();
			m_ppCFaceIcon[FACE_SMILE]->Render();
			m_FaceType = FACE_SMILE;

		}
		else
		{
			m_ppCFaceIcon[FACE_MAXSMILE_BACK]->Render();
			m_ppCFaceIcon[FACE_MAXSMILE]->Render();

			m_FaceType = FACE_MAXSMILE;
		}
		m_ppCFaceIcon[FACE_AMOUNT]->Render();
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//---------------------------------------.
//	��������֐�.
//---------------------------------------.
void CFaceIcon::Release()
{
	SAFE_DELETE_ARRAY(m_ppCFaceIcon);
}