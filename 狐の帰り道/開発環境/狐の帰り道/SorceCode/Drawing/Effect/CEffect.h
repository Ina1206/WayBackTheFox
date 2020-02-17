#ifndef CEFFECT_H
#define CEFFECT_H
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning(disable:4005)

//Xaudio2関係のコードを有効にする.
//#define ENABLE_XAUDIO2

//-----------------------------------------------------
//	先に読み込む、ヘッダ、ライブラリ.
//-----------------------------------------------------
#include <stdio.h>

#include <d3d11.h>
#ifdef ENABLE_XAUDIO2
#include <XAudio2.h>
#endif //#ifdef ENABLE_XAUDIO2.
#pragma comment(lib, "d3d11.lib")

//------------------------------------------------------
//	ここからEffekseer関係 ヘッダ、ライブラリ読み込み.
//------------------------------------------------------
//#include <Effekseer.h>
//#include <EffekseerRendererDX11.h>
#ifdef ENABLE_XAUDIO2
#include <EffekseerSoundXAudio2.h>
#endif //#ifdef ENABLE_XAUDIO2.

//_DEBUGデバッグ版のみ出力.
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

//「D3DX～」使用で必須.
//注意:Effekseer関係より後で読み込むこと.
#include <D3DX10.h>
#pragma comment(lib, "d3dx10.lib")

/**************************************************
*	フリーソフト Effeksserのデータを使う為のクラス.
**/
class CEffect 
{
public:
	~CEffect();	//デストラクタ.

	//インスタンス取得(唯一のアクセス経路).
	//ポインタで作られたものは普通はnewしない限り使えないが.
	//staticを付けるとメモリ上でとられているためアクセスできる.
	//一般では使わないほうがいい.
	static CEffect*	GetInstance()
	{
		//唯一のインスタンスを作成する.
		//(staticで作成されたので２回目は無視される).
		//staticメモリの取得方法で2回目は無視されるということ.
		static CEffect s_Instance;
		return &s_Instance;
	}

	//初期化.
	HRESULT Init();
	//構築.
	HRESULT Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	//破棄.
	void Destroy();
	//データ読み込み.
	HRESULT LoadData();
	//データ解放.
	void ReleaseData();
	//描画関数.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	////再生関数.
	//Effekseer::Handle Play(const D3DXVECTOR3& vPos) {
	//	//今回、エフェクトは固定.
	//	return m_pManager->Play(m_pEffect, vPos.x, vPos.y, vPos.z);
	//}
	////停止関数.
	//void Stop(Effekseer::Handle handle) {
	//	m_pManager->StopEffect(handle);
	//}
	////全て停止関数.
	//void StopAll() {
	//	m_pManager->StopAllEffects();
	//}
	////一時停止.
	//void Pause(Effekseer::Handle handle, bool bFlag) {
	//	m_pManager->SetPaused(handle, bFlag);
	//}

	////位置を指定する.
	//void SetLocation(Effekseer::Handle handle, const D3DXVECTOR3& vPos) {
	//	m_pManager->SetLocation(handle, ConvertToVec3Efk(vPos));

	//	//m_pManager->AddLocation(); //←表示されているところからなんぼずつ増えていく.
	//}

	////サイズを指定する.
	//void SetScale(Effekseer::Handle handle, const D3DXVECTOR3& vScale) {
	//	m_pManager->SetScale(handle, vScale.x, vScale.y, vScale.z);
	//}

	////回転を指定する.
	//void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vRot) {
	//	m_pManager->SetRotation(handle, vRot.x, vRot.y, vRot.z);
	//}

	////回転を指定する(軸とラジアン).
	//void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vAxis, float fRadian)
	//{
	//	m_pManager->SetRotation(handle, ConvertToVec3Efk(vAxis), fRadian);
	//}

	////再生速度を設定する.
	//void SetSpeed(Effekseer::Handle handle, float fSpeed) {
	//	m_pManager->SetSpeed(handle, fSpeed);
	//}

private:
	//生成やコピーを禁止する.
	CEffect();	//コンストラクタ.
	CEffect(const CEffect& rhs) {};
	//C++..operator検索.
	CEffect& operator = (const CEffect& rhs) { return *this; };

	//-------------------------------------------.
	//	DirectX <--> Effekseer 変換関数.
	//-------------------------------------------.
	//vector変換.
	//Effekseer::Vector3D ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx);
	//D3DXVECTOR3 ConvertToVec3Dx(const Effekseer::Vector3D& SrcVec3Efk);
	////matrix変換.
	//Effekseer::Matrix44 ConvertToMatEfk(const D3DXMATRIX& SrcMatDx);
	//D3DXMATRIX ConvertToMatDx(const Effekseer::Matrix44& SrcMatEfk);

	//ビュー行列を設定.
	void SetViewMatrix(D3DXMATRIX& mView);
	//プロジェクション行列を設定.
	void SetProjectionMatrix(D3DXMATRIX& mProj);

	////エフェクトを動作させるために必要.
	//::Effekseer::Manager*			m_pManager;
	//::EffekseerRenderer::Renderer*	m_pRenderer;
#ifdef ENABLE_XAUDIO2
	//エフェクトデータに含まれる音の再生に必要.
	::EffekseerSound::Sound*		m_pSound;
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;
#endif	//#ifdef ENABLE_XAUDIO2.

	//エフェクトの種類ごとに用意.
	//::Effekseer::Effect*			m_pEffect;
	//エフェクトごとに必要.
	//※同じエフェクトを同時に３つ出すなら３つ必要.
	//::Effekseer::Handle				m_Handle;
};

#endif	//#ifndef CEFFECT_H.