#ifndef CRESOURCE_SPRITE_UI_H
#define CRESOURCE_SPRITE_UI_H

#include "..\..\CResourceBase.h"

#include "..\..\..\Bord_Polygon\GameSprite\CSpriteUI.h"

/*************************************************
*	SpriteUI�ǂݍ��݃N���X.
**/
class CResourceSpriteUI
	: public CResourceBase
{
public:
	CResourceSpriteUI();
	~CResourceSpriteUI();

	//====================�萔=======================//.
	const int           ICON_SPRITE_MAX			= 4;							//�A�C�R���̃X�v���C�g�̍ő吔.
	const float			ICON_SIZE				= 200.0f;						//�A�C�R���摜���T�C�Y.
	const float			ICON_DISP_SIZE			= 125.0f;						//�A�C�R���摜�\���T�C�Y.
	const D3DXVECTOR2	TIME_BASE				= D3DXVECTOR2(500.0f, 200.0f);	//���Ԃ̉摜���T�C�Y.		
	const D3DXVECTOR2	TIME_IMAGE_DELIMITER	= D3DXVECTOR2(5.0f, 2.0f);		//�摜�̋�؂�.
	const D3DXVECTOR2	TIME_DISP				= D3DXVECTOR2(80.0f, 80.0f);	//���ԉ摜�\���T�C�Y.
	const D3DXVECTOR2	BARRAGE_BASE_SIZE		= D3DXVECTOR2(552.0f, 107.0f);	//�Q�[�W�̘g�̌�.
	const D3DXVECTOR2	GAGE_BASE_SIZE			= D3DXVECTOR2(488.0f, 38.0f);	//�Q�[�W�̌��摜�T�C�Y.
	const float			GAGE_DISP_SIZE_W		= 800.0f;						//�Q�[�W�̕\�����̒���.
	const float			GAGE_DISP_SIZE_H		= 80.0f;						//�Q�[�W�̕\�������̒���.
	const int			FACE_SPRITE_MAX			= 3;
	const float			FACE_SIZE				= 600.0f;						//��A�C�R�����T�C�Y.
	const float			FACE_DISP_SIZE			= 240.0f;						//��A�C�R���\���T�C�Y.
	const float			FACE_AMOUNT_SIZE		= 400.0f;						//��A�C�R���z�����T�C�Y.
	const float			FACE_AMOUNT_DISP_SIZE	= 330.0f;						//��A�C�R���z���\���T�C�Y.


	//===================�񋓑�======================//.
	//Sprite�̎��.
	enum class enSpriteUI {
		MeatIcon = 0,		//���A�C�R��.
		FishIcon,			//���A�C�R��.
		VegetableIcon,		//��؃A�C�R��.
		RiceIcon,			//�ăA�C�R��.
		TimerNum,			//���Ԃ̔ԍ�.
		GageGround,			//�Q�[�W���n.
		BarratGage,			//�Q�[�W.
		faceIcom_Normal,	//��A�C�R���m�[�}��.
		faceIcom_Smile,		//��A�C�R���X�}�C��.
		faceIcom_MaxSmile,	//��A�C�R���ő勉�̃X�}�C��.
		faceIcom_Amount,	//��A�C�R���z��.
		Goal,				//�S�[��.
		Kitune,				//��.
		No,					//��.
		kae,				//�A.
		Ri,					//��.
		Miti,				//��.
		Line,				//��.
		Maple,				//���݂�.
		PushButton,			//�{�^���������w��.
		Clear_High,			//�N���A��.
		Clear_Middle,		//�N���A��.
		Clear_Low,			//�N���A��.
		Bran,				//�ӂ���.
		Start_Char,			//�X�^�[�g.
		Face_High_Back,		//��A�C�R���w�i.
		Face_Middle_Back,	//��A�C�R���w�i.
		Face_Low_Back,		//��A�C�R���w�i.
		Point_Bar_Back,		//�|�C���g�o�[.
		Point_BlueBar,		//�o�[.
		Point_RedBar,		//�ԃo�[.
		Point_RainbowBar,	//���o�[.

		Max,				//�ő吔.
		Start = MeatIcon,	//�ŏ�.
	};


	//====================�֐�======================//.
	HRESULT Init();													//�����ݒ菈���֐�.
	HRESULT Load();													//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();										//��������Ăяo���֐�.

	//===============���l�������֐�================//.
	CSpriteUI*	GetSpriteUI(enSpriteUI SpriteUI);
private:
	//====================�֐�======================//.
	HRESULT Create(enSpriteUI SpriteUI, const char* pfileName);		//�쐬�����֐�.
	HRESULT Release(enSpriteUI SpriteUI);							//��������֐�.
	HRESULT Check_SpriteUIRnge(enSpriteUI SpriteUI);				//SpriteUI�͈̔͂𒲂ׂ�֐�.
	CSpriteUI::SPRITE_STATE GetSpriteUIState(enSpriteUI SpriteUI);

	//===================�N���X=====================//.
	CSpriteUI**	m_ppSpriteUI;										//���b�V���N���X.
	CSpriteUI::SPRITE_STATE* m_pSpriteUI_State;
};

#endif	//#ifndef CRESOURCE_SPRITE_UI_H.