#ifndef CSTART_COUNT_H
#define CSTART_COUNT_H

#include "CUI_Base.h"

class CStartCount
	: public CUI_Base
{
public:
	CStartCount();
	~CStartCount();

	//=================�֐�===================//.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

	//���u�������֐�.
	void SetDispFlag(bool flag) { m_bDispFlag = flag; }
	//���擾�֐�.
	bool GetDispFlag() { return m_bDispFlag; }


private:
	//=================�萔===================//.
	const D3DXVECTOR3 POSITION = D3DXVECTOR3(600.0f, 300.0f, 0.0f);
	const D3DXVECTOR3 START_POSITION = D3DXVECTOR3(450.0f, 300.0f, 0.0f);
	const int IMAGE_WIDTH_MAX = 5;
	const int IMAGE_HIGH_MAX = 5;

	//=================�֐�===================//.
	void Release();							//��������֐�.
	void Move();

	//=================�ϐ�===================//.
	CSpriteUI*		m_pCStartCount;		//SpriteUI�N���X.
	CSpriteUI*		m_pCStart;			//SpriteUI�N���X.

	D3DXVECTOR2		m_vPattarn;			//�����̃p�^�[��.
	int				m_Frame;			//�o�ߎ���.
	int				m_Second;			//�o�ߕb��.
	bool			m_bDispFlag;		//�`��t���O.

};

#endif//#ifndef CSTART_COUNT_H