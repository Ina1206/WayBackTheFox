#include "CEffect.h"
#include "Global.h"
//GoF:デザインパターン:シングルトン・ファクトリ.
//シングルトン：生成に関するデザインパターン.
//↑プログラム上に唯一無二のもの、かなり便利だが目的のための手段.

//定数宣言.
//描画用インスタンス（スプライト）最大数.
const int RENDER_SPRITE_MAX = 2000;
//エフェクト管理用インスタンス最大数.
const int EFFECT_INSTANCE_MAX = 1000;

//コンストラクタ.
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

//デストラクタ.
CEffect::~CEffect()
{
}

//初期化.
HRESULT CEffect::Init()
{


	return S_OK;
}

//構築.
HRESULT CEffect::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
#ifdef ENABLE_XAUDIO2
	//XAudio2の初期化を行う.
	if (FAILED(
		XAudio2Create(&m_pXA2)))
	{
		_ASSERT_EXPR(false, "XAudio2作成失敗");
		return E_FAIL;
	}
	if (FAILED(
		m_pXA2->CreateMasteringVoice(&m_pXA2Master)))
	{
		_ASSERT_EXPR(false, "MasteringVoice作成失敗");
		return E_FAIL;
	}
#endif	//#ifdef ENABLE_XAUDIO2.

	//描画用インスタンスの生成.
	//第三引数...スプライトの上限数.
	m_pRenderer 
		= ::EffekseerRendererDX11::Renderer::Create(
			pDevice11, pContext11, RENDER_SPRITE_MAX);

	//エフェクト管理用インスタンスの生成.
	//引数...エフェクト上限数.
	m_pManager
		= ::Effekseer::Manager::Create(EFFECT_INSTANCE_MAX);

	//描画用インスタンスから描画機能を設定.
	m_pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	m_pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	m_pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	m_pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	//描画用インスタンスからテクスチャの読み込み機能を設定.
	//独自拡張可能、現在はファイルから読み込んでいる.
	m_pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	m_pManager->SetModelLoader(m_pRenderer->CreateModelLoader());

#ifdef ENABLE_XAUDIO2
	//音の再生用インスタンスの生成.
	m_pSound = ::EffekseerSound::Sound::Create(m_pXA2, 16, 16);

	//音の再生用インスタンスから再生機能を設定.
	m_pManager->SetSoundPlayer(m_pSound->CreateSoundPlayer());

	//音の再生インスタンスからサウンドデータの読み込み機能を設定.
	//独自拡張可能、現在はファイルから読み込みんでいる.
	m_pManager->SetSoundLoader(m_pSound->CreateSoundLoader());
#endif //#ifdef ENABLE_XAUDIO2.

	return S_OK;
}

//破棄.
void CEffect::Destroy()
{
	//エフェクトデータの解放.
	ReleaseData();

	//先にエフェクト管理用インスタンスを破棄.
	m_pManager->Destroy();

#ifdef ENABLE_XAUDIO2
	//次に音の再生用インスタンスを破棄.
	m_pSound->Destroy();
#endif
	//次に描画用インスタンスを破棄.
	m_pRenderer->Destroy();

#ifdef ENABLE_XAUDIO2
	//XAudio2の解放.
	if (m_pXA2Master != nullptr) {
		m_pXA2Master->DestroyVoice();
		m_pXA2Master = nullptr;
	}
	SAFE_RELEASE(m_pXA2);
#endif //#ifdef ENABLE_XAUDIO2.
}

//データ読み込み.
HRESULT CEffect::LoadData()
{
	//エフェクトの読み込み.
	m_pEffect = Effekseer::Effect::Create(
		m_pManager, (const EFK_CHAR*)L"Data\\Effekseer\\test2.efk");
	if (m_pEffect == nullptr) {
		_ASSERT_EXPR(false, "エフェクト読み込み失敗");
		return E_FAIL;
	}

	return S_OK;
}

//データ解放.
void CEffect::ReleaseData()
{
	//エフェクトの解放.
	SAFE_RELEASE(m_pEffect);
}

//描画関数.
void CEffect::Render(D3DXMATRIX & mView, D3DXMATRIX & mProj)
{
	//ビュー行列を設定.
	SetViewMatrix(mView);

	//プロジェクション行列の設定.
	SetProjectionMatrix(mProj);

	//エフェクトの更新処理.
	m_pManager->Update();

	//------------------------------------------------.
	//	Effekseerレンダリング関係.
	//------------------------------------------------.
	//エフェクト描画開始処理.
	m_pRenderer->BeginRendering();

	//エフェクトの描画.
	m_pManager->Draw();

	//エフェクトの描画終了処理.
	m_pRenderer->EndRendering();
}

//DirectX D3DXVECTOR3 -> Effekseer Vector3 に変換する.
Effekseer::Vector3D CEffect::ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx)
{
	return Effekseer::Vector3D(
		SrcVec3Dx.x, SrcVec3Dx.y, SrcVec3Dx.z);
}

//Effekseer Vector3 -> DirectX D3DXVECTOR3 に変換する.
D3DXVECTOR3 CEffect::ConvertToVec3Dx(const Effekseer::Vector3D & SrcVec3Efk)
{
	return D3DXVECTOR3(SrcVec3Efk.X, SrcVec3Efk.Y, SrcVec3Efk.Z);
}

//DirectX D3DXMATRIX -> Effekseer Matrix44 に変換.
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
	//↑は↓の内部の動き.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DestMatEfk.Values[i][j] = SrcMatDx.m[i][j];
		}
	}

	return DestMatEfk;
}

//Effekseer Matrix44 -> DirectX D3DXMATRIX に変換.
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
//ビュー行列を設定.
void CEffect::SetViewMatrix(D3DXMATRIX& mView)
{
	Effekseer::Matrix44 mViewEfk = ConvertToMatEfk(mView);

	//カメラ行列を設定.
	m_pRenderer->SetCameraMatrix(mViewEfk);
}

//プロジェクション行列を設定.
void CEffect::SetProjectionMatrix(D3DXMATRIX& mProj)
{
	Effekseer::Matrix44 mProjEfk = ConvertToMatEfk(mProj);

	//プロジェクション行列を設定.
	m_pRenderer->SetProjectionMatrix(mProjEfk);
}
