#include "CClearUIManager.h"

CClearUIManager::CClearUIManager()
	: m_pCInput				(nullptr)
	, m_pCUI_Base			(nullptr)
	, m_Frame				(0.0f)
	, m_PointSum			(0)
	, m_ButtonDispFlag		(true)
	, m_PushButtonNum		(0)
	, m_DispNum				(0)
{
}

CClearUIManager::~CClearUIManager()
{
	Release();
}

//------------------------------------------.
//	�����ݒ菈���֐�.
//------------------------------------------.
void CClearUIManager::Init_Process()
{
	//���I�m��.
	m_pCInput					 = new clsXInput();
	m_pCUI_Base					 = new CUI_Base*[UI_MAX];

	m_pCUI_Base[CLEAR_UI]		 = new CClearUI();
	m_pCUI_Base[CHAR_EVALUATION] = new CChar_Evaluation();
	m_pCUI_Base[PUSH_BUTTON]	 = new CPushButton();
}

//------------------------------------------.
//	�X�V�����֐�.
//------------------------------------------.
void CClearUIManager::UpDate()
{
	m_pCInput->UpdateStatus();//�������Ȃ��Ɠ����Ȃ�.

	for (int ui = 0; ui < PUSH_BUTTON; ui++)
	{
		//---�|�C���g�̍��v���擾---.
		m_pCUI_Base[ui]->SetPointSum(m_PointSum);
		//---�X�V����---.
		m_pCUI_Base[ui]->UpDate();
	}

	//---�X�V����---.
	if (m_pCUI_Base[CHAR_EVALUATION]->GetMoveEndFlag() == true) {
		m_Frame++;

		if (m_Frame > DISP_PUSH_BUTTON) {
			m_pCUI_Base[PUSH_BUTTON]->UpDate();


			//UI�̕`�揈��.
			if (m_pCInput->IsPress(XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				if (m_DispNum == 0) {
					if (m_PushButtonNum == 0) {
						m_ButtonDispFlag = false;
					}
					else {
						m_ButtonDispFlag = true;
					}
					m_PushButtonNum++;

					if (m_PushButtonNum >= SWITCH_MAX) {
						m_PushButtonNum = 0;
					}
				}
				m_DispNum++;
			}
			else
			{
				m_DispNum = 0;
			}
		}
	}
}

//------------------------------------------.
//	�`�揈���֐�.
//------------------------------------------.
void CClearUIManager::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	if (m_Frame > 10) {
		m_pCUI_Base[CLEAR_UI]->Value_Set(mView, mProj, vCamePos);
		m_pCUI_Base[CLEAR_UI]->Render();
	}

	if (m_ButtonDispFlag == true)
	{
		for (int ui = CLEAR_UI; ui < UI_MAX; ui++) {
			m_pCUI_Base[ui]->Value_Set(mView, mProj, vCamePos);
			m_pCUI_Base[ui]->Render();
		}
	}
}

//------------------------------------------.
//	��������֐�.
//------------------------------------------.
void CClearUIManager::Release()
{
	for (int ui = UI_MAX - 1; ui >= 0; ui--)
	{
		m_pCUI_Base[ui]->Release();
		SAFE_DELETE(m_pCUI_Base[ui]);
	}
	SAFE_DELETE_ARRAY(m_pCUI_Base);
	SAFE_DELETE(m_pCInput);
}
