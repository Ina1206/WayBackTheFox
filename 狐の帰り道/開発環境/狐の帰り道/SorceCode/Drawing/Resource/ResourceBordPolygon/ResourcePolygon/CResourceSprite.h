#ifndef CRESOURCE_SPRITE_H
#define CRESOURCE_SPRITE_H

#include "..\..\..\Bord_Polygon\GameSprite\CSprite.h"

#include "..\..\CResourceBase.h"

/**********************************************************
*		�X�v���C�g�N���X.
***/
class CResourceSprite 
	: public CResourceBase
{
public:
	CResourceSprite();
	~CResourceSprite();

	//====================�萔=======================//.
	const float			BUTTON_BASE_SIZE	= 250.0f;						//�{�^���x�[�X�̈�ӂ̒���.
	const float			BUTTON_DISP_SIZE	= 0.5f;							//�{�^���\�����̈�ӂ̒���.
	const float			MARU_BASE_SIZE		= 800.0f;						//�ۃx�[�X�̈�ӂ̒���.
	const float			MARU_DISP_SIZE		= 1.0f;							//�ە\�����̈�ӂ̒���.
	const D3DXVECTOR2	HIT_BASE_SIZE		= D3DXVECTOR2(100.0f, 200.0f);	//�����������̌��摜�̑傫��.
	const D3DXVECTOR2	HIT_DISP_SIZE		= D3DXVECTOR2(1.0f, 2.0f);		//�����������̕\���摜�̑傫��.
	const float			EFFECT_BASE_SIZE	= 200.0f;						//�G�t�F�N�g�̉摜�̃T�C�Y.
	const float			EFFECT_DISP_SIZE	= 0.8f;							//�G�t�F�N�g�̕\���T�C�Y.
	const float			CCHAR_DISP_SIZE		= 0.025f;							//�����̕\���T�C�Y.	
	const float			CCHAR_HIGH_DISP_SIZE = 0.020f;						//�����̕\���T�C�Y.	
	const D3DXVECTOR2	LONG_SQUARE_BASE	= D3DXVECTOR2(600.0f, 1200.0f);	//�ʏ�̒������l�p�X�v���C�g�̈�ӂ̒���.
	const D3DXVECTOR2	LONG_SQUARE_DISP	= D3DXVECTOR2(1.0f, 5.0f);		//�������l�p�̕\������.
	const float			SHADOW_BASE_SIZE	= 250.0f;						//�e�̌��̃T�C�Y.
	const float			SHADOW_DISP_SIZE	= 1.0f;							//�e�̕\���T�C�Y.

	//===================�񋓑�======================//.
	//Sprite�̎��.
	enum class enSprite {
		Vegetable = 0,			//���.
		Meat,					//��.
		Fish,					//��.
		Rice,					//��.
		TimingCommand,			//�^�C�~���O�R�}���h�p.
		LongPushCircle,			//�������R�}���h�̉~.
		Long_Square,			//�������R�}���h�����̐^�񒆎l�p.
		AButton,				//A�{�^��.
		BButton,				//B�{�^��.
		XButton,				//X�{�^��.
		YButton,				//Y�{�^��.
		HitButton,				//�{�^�����������Ƃ�.
		Hit,					//�����鎞.
		Punch,					//�p���`.
		Sparkle,				//�L���L��.
		Sparkle_Blue,			//�L���L��(��).
		Smoke,					//��.
		Char_High,				//��.
		Char_Middle,			//��.
		Char_Low,				//��.
		Char_Evaluation,		//�]��.
		Shadow,					//�e.

		Max,					//�ő吔.
		Start = Vegetable,		//�n��2��.//�ŏ�.
		ItemStart = Vegetable,	//�A�C�e���摜�̍ŏ�.
		CommandStart = AButton, //�R�}���h�̉摜�̍ŏ�.
	};

	//====================�֐�======================//.
	HRESULT Init();													//�����ݒ菈���֐�.
	HRESULT Load();													//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();										//��������Ăяo���֐�.

	//===============���l�������֐�================//.
	CSprite*	GetSprite(enSprite Sprite);
private:
	//====================�֐�======================//.
	HRESULT Create(enSprite Sprite, const char* pfileName);	//�쐬�����֐�.
	HRESULT Release(enSprite Sprite);						//��������֐�.
	HRESULT Check_SpriteRnge(enSprite Sprite);				//�X�v���C�g�͈̔͂𒲂ׂ�֐�.
	CSprite::SPRITE_STATE stSpriteState(enSprite Sprite);		//�X�v���C�g���ݒ�.

	//===================�N���X=====================//.
	CSprite**	m_ppSprite;										//�X�v���C�g�N���X.
	CSprite::SPRITE_STATE* m_pSprite_State;						//�X�v���C�g�̏��.

};

#endif //#ifndef CRESOURCE_SPRITE_H.