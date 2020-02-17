#ifndef CTITLE_CHARACTER_H
#define CTITLE_CHARACTER_H

#include"CUI_Base.h"
//�R���g���[���N���X.
#include"..\..\Controller\CXInput.h"

class CTitle_Character
	: public CUI_Base
{
public:
	//------------------------------------------.
	//	�萔.
	//------------------------------------------.
	const float		TITLE_MOVE_SPEED	= 0.1f;		//�^�C�g���ړ����x.
	const float		TITLE_ALPHA_SPEED	= 0.01f;	//�^�C�g�����ߑ��x.
	const float		TITLE_ALPHA_MAX		= 1.0f;		//�^�C�g�����ߍő�.
	const int		SPRITEUI_MAX		= 7;		//spriteUI�̍ő吔.
	const int		KITUNE_NUM			= 1;
	const int		NO_NUM				= 2;
	const int		KAE_NUM				= 3;
	const int		RI_NUM				= 4;
	const int		MITI_NUM			= 5;
	const int		LINE_NUM			= 6;
	const int		MAPLE_NUM			= 0;
	const float     SCALE_MAX			= 1.0f;
	const float		SCALE_SPEED			= 0.007f;
	const float		POSITION_Y			= 5.0f;
	const int		INPUT_OK			= 3;		//����\����.
	const int		DISPLAY_TIME		= 20;		//�^�C�g�������\������.

	const D3DXVECTOR2 KITUNE_POS	= D3DXVECTOR2(180.0f, 85.0f);
	const D3DXVECTOR2 NO_POS		= D3DXVECTOR2(510.0f, 180.0f);
	const D3DXVECTOR2 KAE_POS		= D3DXVECTOR2(620.0f, 200.0f);
	const D3DXVECTOR2 RI_POS		= D3DXVECTOR2(785.0f, 230.0f);
	const D3DXVECTOR2 MITI_POS		= D3DXVECTOR2(880.0f, 150.0f);
	const D3DXVECTOR2 LINE_POS		= D3DXVECTOR2(160.0f, 370.0f);
	const D3DXVECTOR2 MAPLE_POS		= D3DXVECTOR2(650.0f, -15.0f);

	const double PI					= 3.14159265358979;

	CTitle_Character();
	~CTitle_Character();

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//------------------------------------------.
	//	�񋓑�.
	//------------------------------------------.
	enum class enTitle_Status
	{
		Character_Display = 0,	//�����\��.
		Draw_Line,				//��������.
		Maple_Display,			//���݂��\��.
	};

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();					//��������֐�.
	void TitleMove();				//�^�C�g���������쏈���֐�.
	void TitleFade(int num);		//�^�C�g���������ߏ����֐�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	clsXInput*		m_pCInput;				//�R���g���[���N���X.
	CSpriteUI**		m_ppCTitleSpriteUI;
	enTitle_Status	m_enTitle_Status;		//�^�C�g���̏��.
	D3DXVECTOR2*	m_vTitlePos;			//�^�C�g���ʒu.
	float*			m_fTitleAlpha;			//�^�C�g���̓��ߒl.
	int				m_Frame;				//�^�C�g���t�F�[�h����.
	bool			*m_DispFlag;			//�`��t���O.
	int				m_DispNum;				//�`��ԍ�.
	float			m_LineSCale;			//���̑傫��.
};

#endif //#ifndef CTITLE_CHARACTER_H