#include "CResourceSpriteUI.h"

CResourceSpriteUI::CResourceSpriteUI()
	: m_ppSpriteUI(nullptr)
	, m_pSpriteUI_State(nullptr)
{
}

CResourceSpriteUI::~CResourceSpriteUI()
{
	if (m_ppSpriteUI != nullptr) {

		for (int i = static_cast<int>(enSpriteUI::Max) - 1; i >= 0; i--) {
			if (m_ppSpriteUI[i] != nullptr) {
				Release(static_cast<enSpriteUI>(i));
			}
		}
		delete[] m_ppSpriteUI;
		m_ppSpriteUI = nullptr;
	}
	delete[] m_pSpriteUI_State;
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
HRESULT CResourceSpriteUI::Init()
{
	//���b�V���̍ő�l.
	const int MaxStaticMesh = static_cast<int>(enSpriteUI::Max);

	//CDX9Mesh�̃N���X�̔z�񓮓I�m��.
	m_ppSpriteUI = new CSpriteUI*[MaxStaticMesh];
	m_pSpriteUI_State = new CSpriteUI::SPRITE_STATE[MaxStaticMesh];

	//������.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppSpriteUI[Mesh_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
HRESULT CResourceSpriteUI::Load()
{
	//�t�@�C���p�X.
	const char fileName[][256] =
	{
		"Data\\Texture\\Item\\meat.png",			//��.
		"Data\\Texture\\Item\\fish.png",			//��.
		"Data\\Texture\\Item\\vegetables.png",		//���.
		"Data\\Texture\\Item\\rice.png",			//��.
		"Data\\Texture\\Command\\font.png",			//���Ԃ̐���.
		"Data\\Texture\\Command\\Barrage.png",		//�Q�[�W�̉��n.
		"Data\\Texture\\Command\\Barrage_Gage.png",	//�A�ŃQ�[�W.
		"Data\\Texture\\FaceIcon\\face_1.png",		//��A�C�R���m�[�}��.
		"Data\\Texture\\FaceIcon\\face_2.png",		//��A�C�R���X�}�C��.
		"Data\\Texture\\FaceIcon\\face_3.png",		//��A�C�R���ő勉�̃X�}�C��.
		"Data\\Texture\\FaceIcon\\face_frame.png",	//��A�C�R���z��.
		"Data\\Texture\\SceneUI\\goal.png",			//�S�[��.
		"Data\\Texture\\Title\\Kitune.png",			//��.
		"Data\\Texture\\Title\\No.png",				//��.
		"Data\\Texture\\Title\\Kae.png",			//�A.
		"Data\\Texture\\Title\\Ri.png",				//��.
		"Data\\Texture\\Title\\Miti.png",			//��.
		"Data\\Texture\\Title\\background1.png",	//��.
		"Data\\Texture\\Title\\background2.png",	//���݂�.
		"Data\\Texture\\SceneUI\\Push_Title.png",	//�{�^���������w��.
		"Data\\Texture\\Clear\\Score_High.png",		//�N���A��.
		"Data\\Texture\\Clear\\Score_Middle.png",	//�N���A��.
		"Data\\Texture\\Clear\\Score_Low.png",		//�N���A��.
		"Data\\Texture\\Bran.png",					//�ӂ���.
		"Data\\Texture\\SceneUI\\start.png",		//�X�^�[�g.
		"Data\\Texture\\FaceIcon\\High_Back.png",	//��A�C�R���w�i.
		"Data\\Texture\\FaceIcon\\Middle_Back.png",	//��A�C�R���w�i.
		"Data\\Texture\\FaceIcon\\Low_Back.png",	//��A�C�R���w�i.
		"Data\\Texture\\ItemBar\\Bar.png",			//�o�[.
		"Data\\Texture\\ItemBar\\Blue_Bar.png",		//�o�[.
		"Data\\Texture\\ItemBar\\Red_Bar.png",		//�ԃo�[.
		"Data\\Texture\\ItemBar\\Rainbow_Bar.png",	//���o�[.

	};

	//�ǂݍ��ݏ���.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enSpriteUI::Max); Mesh_No++) {
		Create(static_cast<enSpriteUI>(Mesh_No), fileName[Mesh_No]);
	}

	return S_OK;
}

//=======================================.
//		��������Ăяo���֐�.
//=======================================.
HRESULT CResourceSpriteUI::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enSpriteUI::Max) - 1; Mesh_No >= 0; Mesh_No--) {
		Release(static_cast<enSpriteUI>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		���l�������֐�.
//=======================================.
CSpriteUI* CResourceSpriteUI::GetSpriteUI(CResourceSpriteUI::enSpriteUI SpriteUI)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteUIRnge(SpriteUI))) {
		return nullptr;
	}
	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(SpriteUI);

	//���f�����Ȃ���ΏI��.
	if (m_ppSpriteUI[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppSpriteUI[Mesh_No];
}

//========================================.
//		�쐬�����֐�.
//========================================.
HRESULT CResourceSpriteUI::Create(CResourceSpriteUI::enSpriteUI SpriteUI, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(SpriteUI);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteUIRnge(SpriteUI))) {
		return E_FAIL;
	}

	//���f�������ɂ���ꍇ�͏I��.
	if (m_ppSpriteUI[MESH_NO] != nullptr) {
		return E_FAIL;
	}

	CSpriteUI::SPRITE_STATE ss = GetSpriteUIState(SpriteUI);
	_ASSERT_EXPR(ss.Base.w != 0.0f, L"ss.Base.w == 0.0f");
	//���f���̓ǂݍ���.
	m_ppSpriteUI[MESH_NO] = new CSpriteUI();
	if (FAILED(m_ppSpriteUI[MESH_NO]->Init(m_pDevice11, m_pContext11, pfileName, &ss))) {
		return E_FAIL;
	}

	return S_OK;
}

//========================================.
//		��������֐�.
//========================================.
HRESULT CResourceSpriteUI::Release(CResourceSpriteUI::enSpriteUI SpriteUI)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SpriteUIRnge(SpriteUI))) {
		return E_FAIL;
	}

	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(SpriteUI);

	//���f�����Ȃ���ΏI��.
	if (m_ppSpriteUI[Mesh_No] == nullptr) {
		return S_OK;
	}

	//���.
	m_ppSpriteUI[Mesh_No]->Release();
	delete m_ppSpriteUI[Mesh_No];
	m_ppSpriteUI[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		���b�V���͈̔͂𒲂ׂ�֐�.
//========================================.
HRESULT CResourceSpriteUI::Check_SpriteUIRnge(CResourceSpriteUI::enSpriteUI SpriteUI)
{
	//�͈͊O�Ȃ�I��.
	if (SpriteUI < enSpriteUI::Start || enSpriteUI::Max <= SpriteUI)
	{
		return E_FAIL;
	}
	return S_OK;
}

//=========================================.
//		�X�v���C�gUI�̏��ݒ�.
//=========================================.
CSpriteUI::SPRITE_STATE CResourceSpriteUI::GetSpriteUIState(CResourceSpriteUI::enSpriteUI SpriteUI) 
{

	for (int icon = 0; icon < ICON_SPRITE_MAX; icon++)
	{
		int IconNum = static_cast<int>(enSpriteUI::MeatIcon) + icon;

		//----------------�A�C�R��-------------------//.
		m_pSpriteUI_State[IconNum].Base.w = ICON_SIZE;
		m_pSpriteUI_State[IconNum].Base.h = ICON_SIZE;
		m_pSpriteUI_State[IconNum].Stride.w = m_pSpriteUI_State[IconNum].Base.w;
		m_pSpriteUI_State[IconNum].Stride.h = m_pSpriteUI_State[IconNum].Base.h;
		m_pSpriteUI_State[IconNum].Disp.w = ICON_DISP_SIZE;
		m_pSpriteUI_State[IconNum].Disp.h = ICON_DISP_SIZE;
	}

	//----------------���Ԃ̔ԍ�-------------------//.
	int TimeNum = static_cast<int>(enSpriteUI::TimerNum);
	m_pSpriteUI_State[TimeNum].Base.w = TIME_BASE.x;
	m_pSpriteUI_State[TimeNum].Base.h = TIME_BASE.y;
	m_pSpriteUI_State[TimeNum].Stride.w = m_pSpriteUI_State[TimeNum].Base.w / TIME_IMAGE_DELIMITER.x;
	m_pSpriteUI_State[TimeNum].Stride.h = m_pSpriteUI_State[TimeNum].Base.h / TIME_IMAGE_DELIMITER.y;
	m_pSpriteUI_State[TimeNum].Disp.w = TIME_DISP.x;
	m_pSpriteUI_State[TimeNum].Disp.h = TIME_DISP.y;
	
	//------------�Q�[�W�̉��n-------------------//.
	int GageGroundNum = static_cast<int>(enSpriteUI::GageGround);
	m_pSpriteUI_State[GageGroundNum].Base.w = BARRAGE_BASE_SIZE.x;
	m_pSpriteUI_State[GageGroundNum].Base.h = BARRAGE_BASE_SIZE.y;
	m_pSpriteUI_State[GageGroundNum].Stride.w = m_pSpriteUI_State[GageGroundNum].Base.w;
	m_pSpriteUI_State[GageGroundNum].Stride.h = m_pSpriteUI_State[GageGroundNum].Base.h;
	m_pSpriteUI_State[GageGroundNum].Disp.w = BARRAGE_BASE_SIZE.x;
	m_pSpriteUI_State[GageGroundNum].Disp.h = BARRAGE_BASE_SIZE.y;

	//------------�Q�[�W-------------------//.
	int GageNum = static_cast<int>(enSpriteUI::BarratGage);
	m_pSpriteUI_State[GageNum].Base.w = GAGE_BASE_SIZE.x;
	m_pSpriteUI_State[GageNum].Base.h = GAGE_BASE_SIZE.y;
	m_pSpriteUI_State[GageNum].Stride.w = m_pSpriteUI_State[GageGroundNum].Base.w;
	m_pSpriteUI_State[GageNum].Stride.h = m_pSpriteUI_State[GageGroundNum].Base.h;
	m_pSpriteUI_State[GageNum].Disp.w = GAGE_BASE_SIZE.x;
	m_pSpriteUI_State[GageNum].Disp.h = GAGE_BASE_SIZE.y;

	//----------------��A�C�R��-------------------//.
	for (int icon = 0; icon < FACE_SPRITE_MAX; icon++)
	{
		int FaceIconNum = static_cast<int>(enSpriteUI::faceIcom_Normal) + icon;

		m_pSpriteUI_State[FaceIconNum].Base.w = FACE_SIZE;
		m_pSpriteUI_State[FaceIconNum].Base.h = FACE_SIZE;
		m_pSpriteUI_State[FaceIconNum].Stride.w = m_pSpriteUI_State[FaceIconNum].Base.w;
		m_pSpriteUI_State[FaceIconNum].Stride.h = m_pSpriteUI_State[FaceIconNum].Base.h;
		m_pSpriteUI_State[FaceIconNum].Disp.w = FACE_DISP_SIZE;
		m_pSpriteUI_State[FaceIconNum].Disp.h = FACE_DISP_SIZE;
	}

	//----------------��A�C�R���z��-------------------//.
	int FaceAmountNum = static_cast<int>(enSpriteUI::faceIcom_Amount);
	m_pSpriteUI_State[FaceAmountNum].Base.w = FACE_AMOUNT_SIZE;
	m_pSpriteUI_State[FaceAmountNum].Base.h = FACE_AMOUNT_SIZE;
	m_pSpriteUI_State[FaceAmountNum].Stride.w = m_pSpriteUI_State[FaceAmountNum].Base.w;
	m_pSpriteUI_State[FaceAmountNum].Stride.h = m_pSpriteUI_State[FaceAmountNum].Base.h;
	m_pSpriteUI_State[FaceAmountNum].Disp.w = FACE_AMOUNT_DISP_SIZE;
	m_pSpriteUI_State[FaceAmountNum].Disp.h = FACE_AMOUNT_DISP_SIZE;

	//----------------�S�[��-------------------//.
	int GoalNum = static_cast<int>(enSpriteUI::Goal);
	m_pSpriteUI_State[GoalNum].Base.w = 1096;
	m_pSpriteUI_State[GoalNum].Base.h = 317;
	m_pSpriteUI_State[GoalNum].Stride.w = m_pSpriteUI_State[GoalNum].Base.w;
	m_pSpriteUI_State[GoalNum].Stride.h = m_pSpriteUI_State[GoalNum].Base.h;
	m_pSpriteUI_State[GoalNum].Disp.w = 1096;
	m_pSpriteUI_State[GoalNum].Disp.h = 317;

	//------------�^�C�g��-------------------//.
	//��.
	int KituneNum = static_cast<int>(enSpriteUI::Kitune);
	m_pSpriteUI_State[KituneNum].Base.w = 374;
	m_pSpriteUI_State[KituneNum].Base.h = 287;
	m_pSpriteUI_State[KituneNum].Stride.w = m_pSpriteUI_State[KituneNum].Base.w;
	m_pSpriteUI_State[KituneNum].Stride.h = m_pSpriteUI_State[KituneNum].Base.h;
	m_pSpriteUI_State[KituneNum].Disp.w = 374;
	m_pSpriteUI_State[KituneNum].Disp.h = 287;

	//��.
	int NoNum = static_cast<int>(enSpriteUI::No);
	m_pSpriteUI_State[NoNum].Base.w = 119;
	m_pSpriteUI_State[NoNum].Base.h = 144;
	m_pSpriteUI_State[NoNum].Stride.w = m_pSpriteUI_State[NoNum].Base.w;
	m_pSpriteUI_State[NoNum].Stride.h = m_pSpriteUI_State[NoNum].Base.h;
	m_pSpriteUI_State[NoNum].Disp.w = 119;
	m_pSpriteUI_State[NoNum].Disp.h = 144;

	//�A.
	int KaeNum = static_cast<int>(enSpriteUI::kae);
	m_pSpriteUI_State[KaeNum].Base.w = 169;
	m_pSpriteUI_State[KaeNum].Base.h = 176;
	m_pSpriteUI_State[KaeNum].Stride.w = m_pSpriteUI_State[KaeNum].Base.w;
	m_pSpriteUI_State[KaeNum].Stride.h = m_pSpriteUI_State[KaeNum].Base.h;
	m_pSpriteUI_State[KaeNum].Disp.w = 169;
	m_pSpriteUI_State[KaeNum].Disp.h = 176;

	//��.
	int RiNum = static_cast<int>(enSpriteUI::Ri);
	m_pSpriteUI_State[RiNum].Base.w = 108;
	m_pSpriteUI_State[RiNum].Base.h = 147;
	m_pSpriteUI_State[RiNum].Stride.w = m_pSpriteUI_State[RiNum].Base.w;
	m_pSpriteUI_State[RiNum].Stride.h = m_pSpriteUI_State[RiNum].Base.h;
	m_pSpriteUI_State[RiNum].Disp.w = 108;
	m_pSpriteUI_State[RiNum].Disp.h = 147;

	//��.
	int MitiNum = static_cast<int>(enSpriteUI::Miti);
	m_pSpriteUI_State[MitiNum].Base.w = 178;
	m_pSpriteUI_State[MitiNum].Base.h = 182;
	m_pSpriteUI_State[MitiNum].Stride.w = m_pSpriteUI_State[MitiNum].Base.w;
	m_pSpriteUI_State[MitiNum].Stride.h = m_pSpriteUI_State[MitiNum].Base.h;
	m_pSpriteUI_State[MitiNum].Disp.w = 178;
	m_pSpriteUI_State[MitiNum].Disp.h = 182;

	//����.
	int LineNum = static_cast<int>(enSpriteUI::Line);
	m_pSpriteUI_State[LineNum].Base.w = 980;
	m_pSpriteUI_State[LineNum].Base.h = 12;
	m_pSpriteUI_State[LineNum].Stride.w = m_pSpriteUI_State[LineNum].Base.w;
	m_pSpriteUI_State[LineNum].Stride.h = m_pSpriteUI_State[LineNum].Base.h;
	m_pSpriteUI_State[LineNum].Disp.w = 980;
	m_pSpriteUI_State[LineNum].Disp.h = 12;

	//���݂�.
	int MapleNum = static_cast<int>(enSpriteUI::Maple);
	m_pSpriteUI_State[MapleNum].Base.w = 382;
	m_pSpriteUI_State[MapleNum].Base.h = 373;
	m_pSpriteUI_State[MapleNum].Stride.w = m_pSpriteUI_State[MapleNum].Base.w;
	m_pSpriteUI_State[MapleNum].Stride.h = m_pSpriteUI_State[MapleNum].Base.h;
	m_pSpriteUI_State[MapleNum].Disp.w = 382;
	m_pSpriteUI_State[MapleNum].Disp.h = 373;

	//--------------�{�^���������w��-----------------//.
	int PushButtonNum = static_cast<int>(enSpriteUI::PushButton);
	m_pSpriteUI_State[PushButtonNum].Base.w = 917;
	m_pSpriteUI_State[PushButtonNum].Base.h = 116;
	m_pSpriteUI_State[PushButtonNum].Stride.w = m_pSpriteUI_State[PushButtonNum].Base.w;
	m_pSpriteUI_State[PushButtonNum].Stride.h = m_pSpriteUI_State[PushButtonNum].Base.h;
	m_pSpriteUI_State[PushButtonNum].Disp.w = 917;
	m_pSpriteUI_State[PushButtonNum].Disp.h = 116;

	//--------------�N���A�摜-----------------//.
	for (int clear = 0; clear < 3; clear++) {
		int ClearNum = static_cast<int>(enSpriteUI::Clear_High) + clear;
		m_pSpriteUI_State[ClearNum].Base.w = WND_W;
		m_pSpriteUI_State[ClearNum].Base.h = WND_H;
		m_pSpriteUI_State[ClearNum].Stride.w = m_pSpriteUI_State[ClearNum].Base.w;
		m_pSpriteUI_State[ClearNum].Stride.h = m_pSpriteUI_State[ClearNum].Base.h;
		m_pSpriteUI_State[ClearNum].Disp.w = WND_W;
		m_pSpriteUI_State[ClearNum].Disp.h = WND_H;
	}

	//------------�t�F�[�h-------------------//.
	int BranNum = static_cast<int>(enSpriteUI::Bran);
	m_pSpriteUI_State[BranNum].Base.w = 640;
	m_pSpriteUI_State[BranNum].Base.h = 720;
	m_pSpriteUI_State[BranNum].Stride.w = m_pSpriteUI_State[BranNum].Base.w;
	m_pSpriteUI_State[BranNum].Stride.h = m_pSpriteUI_State[BranNum].Base.h;
	m_pSpriteUI_State[BranNum].Disp.w = 640;
	m_pSpriteUI_State[BranNum].Disp.h = 720;

	//----------------�X�^�[�g-------------------//.
	int StartNum = static_cast<int>(enSpriteUI::Start_Char);
	m_pSpriteUI_State[StartNum].Base.w = 1427;
	m_pSpriteUI_State[StartNum].Base.h = 310;
	m_pSpriteUI_State[StartNum].Stride.w = m_pSpriteUI_State[StartNum].Base.w;
	m_pSpriteUI_State[StartNum].Stride.h = m_pSpriteUI_State[StartNum].Base.h;
	m_pSpriteUI_State[StartNum].Disp.w = 400;
	m_pSpriteUI_State[StartNum].Disp.h = 100;

	for (int icon = 0; icon < FACE_SPRITE_MAX; icon++)
	{
		int IconBackNum = static_cast<int>(enSpriteUI::Face_High_Back) + icon;

		//----------------��A�C�R���w�i-------------------//.
		m_pSpriteUI_State[IconBackNum].Base.w = 253;
		m_pSpriteUI_State[IconBackNum].Base.h = 253;
		m_pSpriteUI_State[IconBackNum].Stride.w = m_pSpriteUI_State[IconBackNum].Base.w;
		m_pSpriteUI_State[IconBackNum].Stride.h = m_pSpriteUI_State[IconBackNum].Base.h;
		m_pSpriteUI_State[IconBackNum].Disp.w = 240;
		m_pSpriteUI_State[IconBackNum].Disp.h = 240;
	}


	//----------------�o�[-------------------//.
	int Bar_BackNum = static_cast<int>(enSpriteUI::Point_Bar_Back);

	m_pSpriteUI_State[Bar_BackNum].Base.w = 300;
	m_pSpriteUI_State[Bar_BackNum].Base.h = 75;
	m_pSpriteUI_State[Bar_BackNum].Stride.w = m_pSpriteUI_State[Bar_BackNum].Base.w;
	m_pSpriteUI_State[Bar_BackNum].Stride.h = m_pSpriteUI_State[Bar_BackNum].Base.h;
	m_pSpriteUI_State[Bar_BackNum].Disp.w = 300;
	m_pSpriteUI_State[Bar_BackNum].Disp.h = 75;


	for (int bar = 0; bar < 3; bar++) {
		int Bar_Num = static_cast<int>(enSpriteUI::Point_BlueBar) + bar;

		m_pSpriteUI_State[Bar_Num].Base.w = 242;
		m_pSpriteUI_State[Bar_Num].Base.h = 23;
		m_pSpriteUI_State[Bar_Num].Stride.w = m_pSpriteUI_State[Bar_Num].Base.w;
		m_pSpriteUI_State[Bar_Num].Stride.h = m_pSpriteUI_State[Bar_Num].Base.h;
		m_pSpriteUI_State[Bar_Num].Disp.w = 242;
		m_pSpriteUI_State[Bar_Num].Disp.h = 23;
	}


	return m_pSpriteUI_State[static_cast<int>(SpriteUI)];
}
