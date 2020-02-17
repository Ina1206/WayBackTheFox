#ifndef CEFFECT_H
#define CEFFECT_H
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//Xaudio2�֌W�̃R�[�h��L���ɂ���.
//#define ENABLE_XAUDIO2

//-----------------------------------------------------
//	��ɓǂݍ��ށA�w�b�_�A���C�u����.
//-----------------------------------------------------
#include <stdio.h>

#include <d3d11.h>
#ifdef ENABLE_XAUDIO2
#include <XAudio2.h>
#endif //#ifdef ENABLE_XAUDIO2.
#pragma comment(lib, "d3d11.lib")

//------------------------------------------------------
//	��������Effekseer�֌W �w�b�_�A���C�u�����ǂݍ���.
//------------------------------------------------------
//#include <Effekseer.h>
//#include <EffekseerRendererDX11.h>
#ifdef ENABLE_XAUDIO2
#include <EffekseerSoundXAudio2.h>
#endif //#ifdef ENABLE_XAUDIO2.

//_DEBUG�f�o�b�O�ł̂ݏo��.
#if _DEBUG
	//#pragma comment(lib, "VS2017\\Debug\\Effekseer.lib")
	//#pragma comment(lib, "VS2017\\Debug\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
	#pragma comment(lib, "VS2017\\Debug\\EffekseerSoundXAudio2.lib")
#endif //#ifdef ENABLE_XAUDIO2.
#else //#if _DEBUG
	#pragma comment(lib, "VS2017\\Release\\Effekseer.lib")
	#pragma comment(lib, "VS2017\\Release\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
	#pragma comment(lib, "VS2017\\Release\\EffekseerSoundXAudio2.lib")
#endif //#ifdef ENABLE_XAUDIO2.
#endif//#if _DEBUG

//�uD3DX�`�v�g�p�ŕK�{.
//����:Effekseer�֌W����œǂݍ��ނ���.
#include <D3DX10.h>
#pragma comment(lib, "d3dx10.lib")

/**************************************************
*	�t���[�\�t�g Effeksser�̃f�[�^���g���ׂ̃N���X.
**/
class CEffect 
{
public:
	~CEffect();	//�f�X�g���N�^.

	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//�|�C���^�ō��ꂽ���͕̂��ʂ�new���Ȃ�����g���Ȃ���.
	//static��t����ƃ�������łƂ��Ă��邽�߃A�N�Z�X�ł���.
	//��ʂł͎g��Ȃ��ق�������.
	static CEffect*	GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//(static�ō쐬���ꂽ�̂łQ��ڂ͖��������).
		//static�������̎擾���@��2��ڂ͖��������Ƃ�������.
		static CEffect s_Instance;
		return &s_Instance;
	}

	//������.
	HRESULT Init();
	//�\�z.
	HRESULT Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	//�j��.
	void Destroy();
	//�f�[�^�ǂݍ���.
	HRESULT LoadData();
	//�f�[�^���.
	void ReleaseData();
	//�`��֐�.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	////�Đ��֐�.
	//Effekseer::Handle Play(const D3DXVECTOR3& vPos) {
	//	//����A�G�t�F�N�g�͌Œ�.
	//	return m_pManager->Play(m_pEffect, vPos.x, vPos.y, vPos.z);
	//}
	////��~�֐�.
	//void Stop(Effekseer::Handle handle) {
	//	m_pManager->StopEffect(handle);
	//}
	////�S�Ē�~�֐�.
	//void StopAll() {
	//	m_pManager->StopAllEffects();
	//}
	////�ꎞ��~.
	//void Pause(Effekseer::Handle handle, bool bFlag) {
	//	m_pManager->SetPaused(handle, bFlag);
	//}

	////�ʒu���w�肷��.
	//void SetLocation(Effekseer::Handle handle, const D3DXVECTOR3& vPos) {
	//	m_pManager->SetLocation(handle, ConvertToVec3Efk(vPos));

	//	//m_pManager->AddLocation(); //���\������Ă���Ƃ��납��Ȃ�ڂ������Ă���.
	//}

	////�T�C�Y���w�肷��.
	//void SetScale(Effekseer::Handle handle, const D3DXVECTOR3& vScale) {
	//	m_pManager->SetScale(handle, vScale.x, vScale.y, vScale.z);
	//}

	////��]���w�肷��.
	//void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vRot) {
	//	m_pManager->SetRotation(handle, vRot.x, vRot.y, vRot.z);
	//}

	////��]���w�肷��(���ƃ��W�A��).
	//void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vAxis, float fRadian)
	//{
	//	m_pManager->SetRotation(handle, ConvertToVec3Efk(vAxis), fRadian);
	//}

	////�Đ����x��ݒ肷��.
	//void SetSpeed(Effekseer::Handle handle, float fSpeed) {
	//	m_pManager->SetSpeed(handle, fSpeed);
	//}

private:
	//������R�s�[���֎~����.
	CEffect();	//�R���X�g���N�^.
	CEffect(const CEffect& rhs) {};
	//C++..operator����.
	CEffect& operator = (const CEffect& rhs) { return *this; };

	//-------------------------------------------.
	//	DirectX <--> Effekseer �ϊ��֐�.
	//-------------------------------------------.
	//vector�ϊ�.
	//Effekseer::Vector3D ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx);
	//D3DXVECTOR3 ConvertToVec3Dx(const Effekseer::Vector3D& SrcVec3Efk);
	////matrix�ϊ�.
	//Effekseer::Matrix44 ConvertToMatEfk(const D3DXMATRIX& SrcMatDx);
	//D3DXMATRIX ConvertToMatDx(const Effekseer::Matrix44& SrcMatEfk);

	//�r���[�s���ݒ�.
	void SetViewMatrix(D3DXMATRIX& mView);
	//�v���W�F�N�V�����s���ݒ�.
	void SetProjectionMatrix(D3DXMATRIX& mProj);

	////�G�t�F�N�g�𓮍삳���邽�߂ɕK�v.
	//::Effekseer::Manager*			m_pManager;
	//::EffekseerRenderer::Renderer*	m_pRenderer;
#ifdef ENABLE_XAUDIO2
	//�G�t�F�N�g�f�[�^�Ɋ܂܂�鉹�̍Đ��ɕK�v.
	::EffekseerSound::Sound*		m_pSound;
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;
#endif	//#ifdef ENABLE_XAUDIO2.

	//�G�t�F�N�g�̎�ނ��Ƃɗp��.
	//::Effekseer::Effect*			m_pEffect;
	//�G�t�F�N�g���ƂɕK�v.
	//�������G�t�F�N�g�𓯎��ɂR�o���Ȃ�R�K�v.
	//::Effekseer::Handle				m_Handle;
};

#endif	//#ifndef CEFFECT_H.