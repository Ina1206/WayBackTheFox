#include "CResourceSprite.h"

CResourceSprite::CResourceSprite()
	: m_ppSprite(nullptr)
	, m_pSprite_State(nullptr)
{
}

CResourceSprite::~CResourceSprite()
{
	//�X�v���C�g�N���X�̉��.
	if (m_ppSprite != nullptr) {

		for (int i = static_cast<int>(enSprite::Max) - 1; i >= 0; i--) {
			if (m_ppSprite[i] != nullptr) {
				Release(static_cast<enSprite>(i));
			}
		}
		delete[] m_ppSprite;
		m_ppSprite = nullptr;
	}

	//�X�v���C�g�̏�Ԃ̉��.
	if (m_pSprite_State != nullptr) {
		delete[] m_pSprite_State;
	}
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
HRESULT CResourceSprite::Init()
{
	//�e�N�X�`���̍ő�l.
	const int MaxSprite = static_cast<int>(enSprite::Max);

	//CSprite�̃N���X�̔z�񓮓I�m��.
	m_ppSprite = new CSprite*[MaxSprite];
	m_pSprite_State = new CSprite::SPRITE_STATE[MaxSprite];

	//������.
	for (int Tex_No = 0; Tex_No < MaxSprite; Tex_No++) {
		m_ppSprite[Tex_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
HRESULT CResourceSprite::Load()
{
	//�t�@�C���p�X.
	const char fileName[][256] =
	{
		"Data\\Texture\\Item\\vegetables.png",
		"Data\\Texture\\Item\\meat.png",
		"Data\\Texture\\Item\\fish.png",
		"Data\\Texture\\Item\\rice.png",
		"Data\\Texture\\Command\\Timing.png",			//�^�C�~���O�R�}���h�p.
		"Data\\Texture\\Command\\LongPush_Spher.png",	//�������R�}���h�̍ŏ�.
		"Data\\Texture\\Command\\LongPush.png",			//�������R�}���h�����̐^�񒆎l�p.
		"Data\\Texture\\Command\\A.png",				//A�{�^��.
		"Data\\Texture\\Command\\B.png",				//B�{�^��.
		"Data\\Texture\\Command\\X.png",				//X�{�^��.
		"Data\\Texture\\Command\\Y.png",				//Y�{�^��.
		"Data\\Texture\\Command\\Down.png",				//���{�^��.
		"Data\\Texture\\Command\\Right.png",			//�E�{�^��.
		"Data\\Texture\\Command\\Left.png",				//���{�^��.
		"Data\\Texture\\Command\\Up.png",				//��{�^��.
		"Data\\Texture\\Command\\WhiteButton.png",		//�{�^���������Ƃ�.
		"Data\\Texture\\Effect\\shock.png",				//�����鎞.
		"Data\\Texture\\Effect\\Punch.png",				//�L���L��.
		"Data\\Texture\\Effect\\Sparkle.png",			//�L���L��.
		"Data\\Texture\\Effect\\Sparkle_2.png",			//�L���L��.
		"Data\\Texture\\Effect\\Smoke.png",				//��.
		"Data\\Texture\\Clear\\Char_High.png",			//��.
		"Data\\Texture\\Clear\\Char_Middle.png",		//��.
		"Data\\Texture\\Clear\\Char_Low.png",			//��.
		"Data\\Texture\\Clear\\Char_Evaluation.png",	//�]��.
		"Data\\Texture\\Shadow.png",					//�e.
	};

	//�ǂݍ��ݏ���.
	for (int Tex_No = 0; Tex_No < static_cast<int>(enSprite::Max); Tex_No++) {
		Create(static_cast<enSprite>(Tex_No), fileName[Tex_No]);
	}

	return S_OK;
}

//=======================================.
//		��������Ăяo���֐�.
//=======================================.
HRESULT CResourceSprite::ReleaseCalling()
{
	for (int Tex_No = static_cast<int>(enSprite::Max) - 1; Tex_No >= 0; Tex_No--) {
		Release(static_cast<enSprite>(Tex_No));
	}
	return S_OK;
}

//=======================================.
//		���l�������֐�.
//=======================================.
CSprite* CResourceSprite::GetSprite(CResourceSprite::enSprite Sprite)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteRnge(Sprite))) {
		return nullptr;
	}
	//���b�V���ԍ��ݒ�.
	const int Tex_No = static_cast<int>(Sprite);

	//���f�����Ȃ���ΏI��.
	if (m_ppSprite[Tex_No] == nullptr) {
		return nullptr;
	}

	return m_ppSprite[Tex_No];
}

//========================================.
//		�쐬�����֐�.
//========================================.
HRESULT CResourceSprite::Create(CResourceSprite::enSprite Sprite, const char* pfileName)
{
	const int TEX_NO = static_cast<int>(Sprite);
	//const char TEX_NO = static_cast<int>(Sprite);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteRnge(Sprite))) {
		return E_FAIL;
	}

	//���f�������ɂ���ꍇ�͏I��.
	if (m_ppSprite[TEX_NO] != nullptr) {
		return E_FAIL;
	}

	//���f���̓ǂݍ���.
	m_ppSprite[TEX_NO] = new CSprite();

	CSprite::SPRITE_STATE ss;

	ss = stSpriteState(Sprite);

	if (FAILED(m_ppSprite[TEX_NO]->Init(m_pDevice11, m_pContext11, pfileName, &ss))) {
		return E_FAIL;
	}

	return S_OK;
}

//========================================.
//		��������֐�.
//========================================.
HRESULT CResourceSprite::Release(CResourceSprite::enSprite Sprite)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteRnge(Sprite))) {
		return E_FAIL;
	}

	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(Sprite);

	//���f�����Ȃ���ΏI��.
	if (m_ppSprite[Mesh_No] == nullptr) {
		return S_OK;
	}

	//���.
	m_ppSprite[Mesh_No]->Release();
	delete m_ppSprite[Mesh_No];
	m_ppSprite[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		�X�v���C�g�͈̔͂𒲂ׂ�֐�.
//========================================.
HRESULT CResourceSprite::Check_SpriteRnge(CResourceSprite::enSprite Sprite)
{
	//�͈͊O�Ȃ�I��.
	if (Sprite < enSprite::Start || enSprite::Max <= Sprite)
	{
		return E_FAIL;
	}
	return S_OK;
}

//========================================.
//		�X�v���C�g���ݒ�.
//========================================.
CSprite::SPRITE_STATE CResourceSprite::stSpriteState(CResourceSprite::enSprite Sprite)
{
	int MeatNum = static_cast<int>(enSprite::Meat);
	m_pSprite_State[MeatNum].Base.w = 200.0f;
	m_pSprite_State[MeatNum].Base.h = 200.0f;
	m_pSprite_State[MeatNum].Stride.w = m_pSprite_State[MeatNum].Base.w;
	m_pSprite_State[MeatNum].Stride.h = m_pSprite_State[MeatNum].Base.h;
	m_pSprite_State[MeatNum].Disp.w = 1;
	m_pSprite_State[MeatNum].Disp.h = 1;

	int FishNum = static_cast<int>(enSprite::Fish);
	m_pSprite_State[FishNum].Base.w = 200.0f;
	m_pSprite_State[FishNum].Base.h = 200.0f;
	m_pSprite_State[FishNum].Stride.w = m_pSprite_State[FishNum].Base.w;
	m_pSprite_State[FishNum].Stride.h = m_pSprite_State[FishNum].Base.h;
	m_pSprite_State[FishNum].Disp.w = 1;
	m_pSprite_State[FishNum].Disp.h = 1;

	int VegetableNum = static_cast<int>(enSprite::Vegetable);
	m_pSprite_State[VegetableNum].Base.w = 200.0f;
	m_pSprite_State[VegetableNum].Base.h = 200.0f;
	m_pSprite_State[VegetableNum].Stride.w = m_pSprite_State[VegetableNum].Base.w;
	m_pSprite_State[VegetableNum].Stride.h = m_pSprite_State[VegetableNum].Base.h;
	m_pSprite_State[VegetableNum].Disp.w = 1;
	m_pSprite_State[VegetableNum].Disp.h = 1;

	int RiceNum = static_cast<int>(enSprite::Rice);
	m_pSprite_State[RiceNum].Base.w = 200.0f;
	m_pSprite_State[RiceNum].Base.h = 200.0f;
	m_pSprite_State[RiceNum].Stride.w = m_pSprite_State[RiceNum].Base.w;
	m_pSprite_State[RiceNum].Stride.h = m_pSprite_State[RiceNum].Base.h;
	m_pSprite_State[RiceNum].Disp.w = 1;
	m_pSprite_State[RiceNum].Disp.h = 1;

	//--------------------��---------------------//.
	int MaruNum = static_cast<int>(enSprite::TimingCommand);
	m_pSprite_State[MaruNum].Base.w		= MARU_BASE_SIZE;
	m_pSprite_State[MaruNum].Base.h		= MARU_BASE_SIZE;
	m_pSprite_State[MaruNum].Stride.w	= m_pSprite_State[MaruNum].Base.w;
	m_pSprite_State[MaruNum].Stride.h	= m_pSprite_State[MaruNum].Base.h;
	m_pSprite_State[MaruNum].Disp.w		= MARU_DISP_SIZE;
	m_pSprite_State[MaruNum].Disp.h		= MARU_DISP_SIZE;

	//-----------------���������[-----------------//.
	int Circle = static_cast<int>(enSprite::LongPushCircle);
	m_pSprite_State[Circle].Base.w = MARU_BASE_SIZE;
	m_pSprite_State[Circle].Base.h = MARU_BASE_SIZE;
	m_pSprite_State[Circle].Stride.w = m_pSprite_State[Circle].Base.w;
	m_pSprite_State[Circle].Stride.h = m_pSprite_State[Circle].Base.h;
	m_pSprite_State[Circle].Disp.w = MARU_DISP_SIZE * 1.2f;
	m_pSprite_State[Circle].Disp.z = MARU_DISP_SIZE * 1.2f;
	

	//-----------------�������l�p-----------------//.
	int Square = static_cast<int>(enSprite::Long_Square);
	m_pSprite_State[Square].Base.w		= LONG_SQUARE_BASE.x;
	m_pSprite_State[Square].Base.h		= LONG_SQUARE_BASE.y;
	m_pSprite_State[Square].Stride.w	= m_pSprite_State[Square].Base.w;
	m_pSprite_State[Square].Stride.h	= m_pSprite_State[Square].Base.h;
	m_pSprite_State[Square].Disp.w		= LONG_SQUARE_DISP.x;
	m_pSprite_State[Square].Disp.z		= LONG_SQUARE_DISP.y;


	//-------------------�{�^��-------------------//.
	for (int ButtonNum = static_cast<int>(enSprite::AButton); ButtonNum <= static_cast<int>(enSprite::HitButton); ButtonNum++) {
		m_pSprite_State[ButtonNum].Base.w	= BUTTON_BASE_SIZE;
		m_pSprite_State[ButtonNum].Base.h	= BUTTON_BASE_SIZE;
		m_pSprite_State[ButtonNum].Stride.w = m_pSprite_State[ButtonNum].Base.w;
		m_pSprite_State[ButtonNum].Stride.h = m_pSprite_State[ButtonNum].Base.h;
		m_pSprite_State[ButtonNum].Disp.w	= BUTTON_DISP_SIZE;
		m_pSprite_State[ButtonNum].Disp.h	= BUTTON_DISP_SIZE;
	}

	//------------------����������-------------------//.
	int Hit = static_cast<int>(enSprite::Hit);
	m_pSprite_State[Hit].Base.w		= HIT_BASE_SIZE.x;
	m_pSprite_State[Hit].Base.h		= HIT_BASE_SIZE.y;
	m_pSprite_State[Hit].Stride.w	= m_pSprite_State[Hit].Base.w;
	m_pSprite_State[Hit].Stride.h	= m_pSprite_State[Hit].Base.h;
	m_pSprite_State[Hit].Disp.w		= HIT_DISP_SIZE.x;
	m_pSprite_State[Hit].Disp.h		= HIT_DISP_SIZE.y;

	//-------------------�G�t�F�N�g---------------------//.
	for (int EffectType = static_cast<int>(enSprite::Punch); EffectType <= static_cast<int>(enSprite::Smoke); EffectType++) {
		m_pSprite_State[EffectType].Base.w = EFFECT_BASE_SIZE;
		m_pSprite_State[EffectType].Base.h = EFFECT_BASE_SIZE;
		m_pSprite_State[EffectType].Stride.w = m_pSprite_State[EffectType].Base.w;
		m_pSprite_State[EffectType].Stride.h = m_pSprite_State[EffectType].Base.h;
		m_pSprite_State[EffectType].Disp.w = EFFECT_DISP_SIZE;
		m_pSprite_State[EffectType].Disp.h = EFFECT_DISP_SIZE;
	}

	//----------------�]������-------------------//.
	//��.
	int Char_HighNum = static_cast<int>(enSprite::Char_High);
	m_pSprite_State[Char_HighNum].Base.w = 262;
	m_pSprite_State[Char_HighNum].Base.h = 300;
	m_pSprite_State[Char_HighNum].Stride.w = m_pSprite_State[Char_HighNum].Base.w;
	m_pSprite_State[Char_HighNum].Stride.h = m_pSprite_State[Char_HighNum].Base.h;
	m_pSprite_State[Char_HighNum].Disp.w = CCHAR_HIGH_DISP_SIZE;
	m_pSprite_State[Char_HighNum].Disp.h = CCHAR_HIGH_DISP_SIZE;

	//��.
	int Char_MiddleNum = static_cast<int>(enSprite::Char_Middle);
	m_pSprite_State[Char_MiddleNum].Base.w = 252;
	m_pSprite_State[Char_MiddleNum].Base.h = 303;
	m_pSprite_State[Char_MiddleNum].Stride.w = m_pSprite_State[Char_MiddleNum].Base.w;
	m_pSprite_State[Char_MiddleNum].Stride.h = m_pSprite_State[Char_MiddleNum].Base.h;
	m_pSprite_State[Char_MiddleNum].Disp.w = CCHAR_DISP_SIZE;
	m_pSprite_State[Char_MiddleNum].Disp.h = CCHAR_DISP_SIZE;

	//��.
	int Char_LowNum = static_cast<int>(enSprite::Char_Low);
	m_pSprite_State[Char_LowNum].Base.w = 305;
	m_pSprite_State[Char_LowNum].Base.h = 290;
	m_pSprite_State[Char_LowNum].Stride.w = m_pSprite_State[Char_LowNum].Base.w;
	m_pSprite_State[Char_LowNum].Stride.h = m_pSprite_State[Char_LowNum].Base.h;
	m_pSprite_State[Char_LowNum].Disp.w = CCHAR_DISP_SIZE;
	m_pSprite_State[Char_LowNum].Disp.h = CCHAR_DISP_SIZE;

	//�]��.
	int Char_EvaluationNum = static_cast<int>(enSprite::Char_Evaluation);
	m_pSprite_State[Char_EvaluationNum].Base.w = 428;
	m_pSprite_State[Char_EvaluationNum].Base.h = 227;
	m_pSprite_State[Char_EvaluationNum].Stride.w = m_pSprite_State[Char_EvaluationNum].Base.w;
	m_pSprite_State[Char_EvaluationNum].Stride.h = m_pSprite_State[Char_EvaluationNum].Base.h;
	m_pSprite_State[Char_EvaluationNum].Disp.w = 0.028f;
	m_pSprite_State[Char_EvaluationNum].Disp.h = 0.015f;

	//�e.
	int ShadowNum = static_cast<int>(enSprite::Shadow);
	m_pSprite_State[ShadowNum].Base.w = SHADOW_BASE_SIZE;
	m_pSprite_State[ShadowNum].Base.h = SHADOW_BASE_SIZE;
	m_pSprite_State[ShadowNum].Stride.w = m_pSprite_State[ShadowNum].Base.w;
	m_pSprite_State[ShadowNum].Stride.h = m_pSprite_State[ShadowNum].Base.h;
	m_pSprite_State[ShadowNum].Disp.w = SHADOW_DISP_SIZE;
	m_pSprite_State[ShadowNum].Disp.z = SHADOW_DISP_SIZE;

	return m_pSprite_State[static_cast<int>(Sprite)];
}