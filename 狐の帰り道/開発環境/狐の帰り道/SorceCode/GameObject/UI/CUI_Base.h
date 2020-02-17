#ifndef CUI_BASE_H
#define CUI_BASE_H

#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\Drawing\Bord_Polygon\CDepth_Stencil.h"

extern bool g_BranOpenFlag;

/***************************************************
*		UI�̌��ƂȂ�N���X.
**/
class CUI_Base
{
public:
	//=================�萔===================//.
	const int MIDDLE_POINT	= 24;
	const int HIGH_POINT	= 48;

	//------------------------------------------.
	//	�񋓑�.
	//------------------------------------------.
	enum class enFade
	{
		Fade_In = 0,		//�t�F�[�h�C��.
		Fade_Out,			//�t�F�[�h�A�E�g.

	};

	//�N���A�̏��.
	enum class enClear_Status
	{
		High = 0,		//��.
		Middle,			//��.
		Low,			//��.

		Max,			//�ő�.
		Start = High,	//�ŏ�.

	};

	CUI_Base();
	~CUI_Base();

	//=================�֐�===================//.
	void Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);
	virtual void UpDate() = 0;		//�X�V�����֐�.
	virtual void Render() = 0;		//�`�揈���֐�.
	virtual void Release() = 0;		//��������֐�.

	void SetPointSum(int num) { m_PointSum = num; }

	//�`���擾�֐��`.
	bool GetMoveEndFlag() { return m_bMoveEndFlag; }


protected:
	//=================�ϐ�===================//.
	D3DXVECTOR3			m_vCameraPos;			//�J�����ʒu.
	D3DXMATRIX			m_mView;				//�r���[�s��.
	D3DXMATRIX			m_mProj;				//�v���W�F�N�V�����s��.

	CResourceManager*	m_pCResourceManager;	//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*		m_pCDepth_Stencil;		//�f�v�X�X�e���V���N���X.

	D3DXVECTOR3			m_vPos;					//�ʒu���.
	int					m_PointSum;				//�|�C���g�̍��v.
	bool				m_bMoveEndFlag;		    //��~�m�F�p�t���O.

private:
};

#endif//#ifndef CUI_BASE_H.
