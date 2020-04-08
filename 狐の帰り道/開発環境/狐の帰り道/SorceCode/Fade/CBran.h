#ifndef CBRAN_H
#define CBRAN_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"

#include "..\Sound\CSEPlayManager.h"

/*******************************************
*	�ӂ��܃N���X.
**/
class CBran
{
public:
	CBran();
	~CBran();
	//===============�񋓑�==================//.
	enum class enBran_Status
	{
		Open = 0,		//�J��.
		Close,			//�܂�.

		MAX,			//�ő吔.
		Start = Open,	//�ŏ�.
	};

	//===============�֐�==================//.
	void Init();		//�����������֐�.
	void UpDate();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

	//�`���u���֐��`.
	void SetBran_Open();
	void SetBran_Close();

	//�`���擾�����֐��`.
	bool GetBran_OpenEnd() { return m_bBran_OpenEndFlag; }
	bool GetBran_OpenFlag()	{ return m_bBran_OpenFlag; }
	bool GetBran_CloseFlag(){ return m_bBran_CloseFlag; }

private:
	//===============�萔==================//.
	const D3DXVECTOR3	LEFT_INIT_POSITION	= D3DXVECTOR3(   0.0f,  0.0f, 0.0f);	//�J�n�ʒu.
	const D3DXVECTOR3	RIGHT_INIT_POSITION	= D3DXVECTOR3(1280.0f,  0.0f, 0.0f);	//�J�n�ʒu.
	const D3DXVECTOR3	CLOSE_POSITION		= D3DXVECTOR3( 640.0f,  0.0f, 0.0f);	//�߂�ʒu.
	const D3DXVECTOR3	LEFT_ROTATION		= D3DXVECTOR3(   0.0f, 3.15f, 0.0f);	//��]�l.
	const D3DXVECTOR3	RIGHT_ROTATION		= D3DXVECTOR3(   0.0f,  0.0f, 0.0f);	//��]�l.
	const float			SPEED				= 30.0f;								//�J���x.
	const int			BRAN_MAX			= 2;									//�ӂ��܍ő吔.
	const int			CLOSE_TIME			= 20;									//���Ă��鎞��.
	const int			LEFT				= 0;
	const int			RIGHT				= 1;
	
	//===============�֐�==================//.
	void Bran_Open();	//�J��.
	void Bran_Close();	//�܂�.
	void Release();		//��������֐�.

	//===============�ϐ�==================//.
	CSpriteUI**			m_ppCSpriteUI;			//�X�v���C�gUI�N���X.
	CResourceManager*	m_pCResourceManager;	//���\�[�X�Ǘ��N���X.
	CDepth_Stencil*		m_pDepth_Srencil;		//�f�v�X�X�e���V���N���X.
	D3DXVECTOR3*		m_vPos;					//���W.
	D3DXVECTOR3*		m_vRot;					//���W.
	enBran_Status		m_enBran_State;			//�ӂ��܏�ԗ񋓑�.
	bool				m_bBran_OpenFlag;
	bool				m_bBran_OpenEndFlag;	//�J���I�������.
	bool				m_bBran_CloseFlag;
	int					m_WaitTime;

	CSEPlayManager*		m_pCSEPlayManager;
};

#endif//##ifndef CBRAN_H.
