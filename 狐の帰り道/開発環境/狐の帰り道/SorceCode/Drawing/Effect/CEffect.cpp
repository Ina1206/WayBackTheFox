#include "CEffect.h"
#include "Global.h"
//GoF:�f�U�C���p�^�[��:�V���O���g���E�t�@�N�g��.
//�V���O���g���F�����Ɋւ���f�U�C���p�^�[��.
//���v���O������ɗB�ꖳ��̂��́A���Ȃ�֗������ړI�̂��߂̎�i.

//�萔�錾.
//�`��p�C���X�^���X�i�X�v���C�g�j�ő吔.
const int RENDER_SPRITE_MAX = 2000;
//�G�t�F�N�g�Ǘ��p�C���X�^���X�ő吔.
const int EFFECT_INSTANCE_MAX = 1000;

//�R���X�g���N�^.
CEffect::CEffect()
	: m_pManager	(nullptr)
	, m_pRenderer	(nullptr)
#ifdef ENABLE_XAUDIO2
	, m_pSound		(nullptr)
	, m_pXA2		(nullptr)
	, m_pXA2Master	(nullptr)
#endif	//#ifdef ENABLE_XAUDIO2.
{
}

//�f�X�g���N�^.
CEffect::~CEffect()
{
}

//������.
HRESULT CEffect::Init()
{


	return S_OK;
}

//�\�z.
HRESULT CEffect::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
#ifdef ENABLE_XAUDIO2
	//XAudio2�̏��������s��.
	if (FAILED(
		XAudio2Create(&m_pXA2)))
	{
		_ASSERT_EXPR(false, "XAudio2�쐬���s");
		return E_FAIL;
	}
	if (FAILED(
		m_pXA2->CreateMasteringVoice(&m_pXA2Master)))
	{
		_ASSERT_EXPR(false, "MasteringVoice�쐬���s");
		return E_FAIL;
	}
#endif	//#ifdef ENABLE_XAUDIO2.

	//�`��p�C���X�^���X�̐���.
	//��O����...�X�v���C�g�̏����.
	m_pRenderer 
		= ::EffekseerRendererDX11::Renderer::Create(
			pDevice11, pContext11, RENDER_SPRITE_MAX);

	//�G�t�F�N�g�Ǘ��p�C���X�^���X�̐���.
	//����...�G�t�F�N�g�����.
	m_pManager
		= ::Effekseer::Manager::Create(EFFECT_INSTANCE_MAX);

	//�`��p�C���X�^���X����`��@�\��ݒ�.
	m_pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	m_pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	m_pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	m_pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	//�`��p�C���X�^���X����e�N�X�`���̓ǂݍ��݋@�\��ݒ�.
	//�Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���.
	m_pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	m_pManager->SetModelLoader(m_pRenderer->CreateModelLoader());

#ifdef ENABLE_XAUDIO2
	//���̍Đ��p�C���X�^���X�̐���.
	m_pSound = ::EffekseerSound::Sound::Create(m_pXA2, 16, 16);

	//���̍Đ��p�C���X�^���X����Đ��@�\��ݒ�.
	m_pManager->SetSoundPlayer(m_pSound->CreateSoundPlayer());

	//���̍Đ��C���X�^���X����T�E���h�f�[�^�̓ǂݍ��݋@�\��ݒ�.
	//�Ǝ��g���\�A���݂̓t�@�C������ǂݍ��݂�ł���.
	m_pManager->SetSoundLoader(m_pSound->CreateSoundLoader());
#endif //#ifdef ENABLE_XAUDIO2.

	return S_OK;
}

//�j��.
void CEffect::Destroy()
{
	//�G�t�F�N�g�f�[�^�̉��.
	ReleaseData();

	//��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��.
	m_pManager->Destroy();

#ifdef ENABLE_XAUDIO2
	//���ɉ��̍Đ��p�C���X�^���X��j��.
	m_pSound->Destroy();
#endif
	//���ɕ`��p�C���X�^���X��j��.
	m_pRenderer->Destroy();

#ifdef ENABLE_XAUDIO2
	//XAudio2�̉��.
	if (m_pXA2Master != nullptr) {
		m_pXA2Master->DestroyVoice();
		m_pXA2Master = nullptr;
	}
	SAFE_RELEASE(m_pXA2);
#endif //#ifdef ENABLE_XAUDIO2.
}

//�f�[�^�ǂݍ���.
HRESULT CEffect::LoadData()
{
	//�G�t�F�N�g�̓ǂݍ���.
	m_pEffect = Effekseer::Effect::Create(
		m_pManager, (const EFK_CHAR*)L"Data\\Effekseer\\test2.efk");
	if (m_pEffect == nullptr) {
		_ASSERT_EXPR(false, "�G�t�F�N�g�ǂݍ��ݎ��s");
		return E_FAIL;
	}

	return S_OK;
}

//�f�[�^���.
void CEffect::ReleaseData()
{
	//�G�t�F�N�g�̉��.
	SAFE_RELEASE(m_pEffect);
}

//�`��֐�.
void CEffect::Render(D3DXMATRIX & mView, D3DXMATRIX & mProj)
{
	//�r���[�s���ݒ�.
	SetViewMatrix(mView);

	//�v���W�F�N�V�����s��̐ݒ�.
	SetProjectionMatrix(mProj);

	//�G�t�F�N�g�̍X�V����.
	m_pManager->Update();

	//------------------------------------------------.
	//	Effekseer�����_�����O�֌W.
	//------------------------------------------------.
	//�G�t�F�N�g�`��J�n����.
	m_pRenderer->BeginRendering();

	//�G�t�F�N�g�̕`��.
	m_pManager->Draw();

	//�G�t�F�N�g�̕`��I������.
	m_pRenderer->EndRendering();
}

//DirectX D3DXVECTOR3 -> Effekseer Vector3 �ɕϊ�����.
Effekseer::Vector3D CEffect::ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx)
{
	return Effekseer::Vector3D(
		SrcVec3Dx.x, SrcVec3Dx.y, SrcVec3Dx.z);
}

//Effekseer Vector3 -> DirectX D3DXVECTOR3 �ɕϊ�����.
D3DXVECTOR3 CEffect::ConvertToVec3Dx(const Effekseer::Vector3D & SrcVec3Efk)
{
	return D3DXVECTOR3(SrcVec3Efk.X, SrcVec3Efk.Y, SrcVec3Efk.Z);
}

//DirectX D3DXMATRIX -> Effekseer Matrix44 �ɕϊ�.
Effekseer::Matrix44 CEffect::ConvertToMatEfk(const D3DXMATRIX & SrcMatDx)
{
	Effekseer::Matrix44 DestMatEfk;

	//DestMatEfk.Values[0][0] = SrcMatDx._11;
	//DestMatEfk.Values[0][1] = SrcMatDx._12;
	//DestMatEfk.Values[0][2] = SrcMatDx._13;
	//DestMatEfk.Values[0][3] = SrcMatDx._14;

	//DestMatEfk.Values[1][0] = SrcMatDx._21;
	//DestMatEfk.Values[1][1] = SrcMatDx._22;
	//DestMatEfk.Values[1][2] = SrcMatDx._23;
	//DestMatEfk.Values[1][3] = SrcMatDx._24;

	//DestMatEfk.Values[2][0] = SrcMatDx._31;
	//DestMatEfk.Values[2][1] = SrcMatDx._32;
	//DestMatEfk.Values[2][2] = SrcMatDx._33;
	//DestMatEfk.Values[2][3] = SrcMatDx._34;

	//DestMatEfk.Values[3][0] = SrcMatDx._41;
	//DestMatEfk.Values[3][1] = SrcMatDx._42;
	//DestMatEfk.Values[3][2] = SrcMatDx._43;
	//DestMatEfk.Values[3][3] = SrcMatDx._44;
	//���́��̓����̓���.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DestMatEfk.Values[i][j] = SrcMatDx.m[i][j];
		}
	}

	return DestMatEfk;
}

//Effekseer Matrix44 -> DirectX D3DXMATRIX �ɕϊ�.
D3DXMATRIX CEffect::ConvertToMatDx(const Effekseer::Matrix44& SrcMatEfk)
{
	D3DXMATRIX DestMatDx;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DestMatDx.m[i][j] = SrcMatEfk.Values[i][j];
		}
	}

	return DestMatDx;
}
//�r���[�s���ݒ�.
void CEffect::SetViewMatrix(D3DXMATRIX& mView)
{
	Effekseer::Matrix44 mViewEfk = ConvertToMatEfk(mView);

	//�J�����s���ݒ�.
	m_pRenderer->SetCameraMatrix(mViewEfk);
}

//�v���W�F�N�V�����s���ݒ�.
void CEffect::SetProjectionMatrix(D3DXMATRIX& mProj)
{
	Effekseer::Matrix44 mProjEfk = ConvertToMatEfk(mProj);

	//�v���W�F�N�V�����s���ݒ�.
	m_pRenderer->SetProjectionMatrix(mProjEfk);
}
