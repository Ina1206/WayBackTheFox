#ifndef CMAINUIMANAGER_H
#define CMAINUIMANAGER_H

#include "CItemIcon.h"
#include "CFaceIcon.h"
#include "CStartCount.h"
#include "CItemCount.h"
#include "CItemPoint_Bar.h"

class CMainUIManager
{
public:
	CMainUIManager();
	~CMainUIManager();

	//=================�֐�===================//.
	void Init_Process();	//�������֐�.
	void UpDate();			//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.

	//�`���u�������֐��`.
	void SetItemPointSum(int num) { m_PointSum = num; }									//�|�C���g�̍��v�擾.
	void SetItemCount(int num, int count) { m_pCItemCount->SetItemCount(num, count); }	//�A�C�e���̌��擾.

	//���擾�����֐�.
	bool GetStartCountDispFlag() { return m_pCStartCount->GetDispFlag(); }				//�X�^�[�g�J�E���g�̕`��t���O�擾.

private:
	//=================�萔===================//.
	const int ITEM_TYPE_MAX = static_cast<int>(enItemType::MAX);

	//=================�֐�===================//.
	void Release();			//��������֐�.

	//=================�ϐ�===================//.
	CItemIcon*		m_pCItemIcon;
	CFaceIcon*		m_pCFaceIcon;
	CStartCount*	m_pCStartCount;
	CItemCount*		m_pCItemCount;
	CItemPoint_Bar* m_pCtemPoint_Bar;

	int m_PointSum;
};

#endif	//#ifndef CMAINUIMANAGER_H
