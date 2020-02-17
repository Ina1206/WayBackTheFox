#ifndef CDEBUG_TEXT_H
#define CDEBUG_TEXT_H
//UIなどの画面に貼り付けたいものは透視投影でなく平行投影のほうがいい.

#include "..\..\..\Global.h"

//デバッグテキストクラス.
class CDebugText
{
public:
	const float DIMENSION = 12.0f;
	const float WDIMENSION = 10.0f;
	const float TEX_DIMENSION = 128.0f;

	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//ワールド,ビュー,プロジェクションの合成変換行列.
		D3DXVECTOR4 vColor;		//カラー(RGBAの型に合わせる).
		D3DXVECTOR4 fAlpha;		//アルファ値(xのみ使用).
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
		D3DXVECTOR2 Tex;		//テクスチャ座標.
	};

	CDebugText();				//コンストラクタ.
	~CDebugText();				//デストラクタ.

	//初期化関数.
	HRESULT Init(ID3D11DeviceContext* pContext11,
		DWORD Width, DWORD Height, 
		float Scale, D3DXVECTOR4 vColor);

	//アルファブレンド切り替え設定.
	void SetBlend(bool EnableAlpha);

	//レンダリング関数.
	void Render(const char* text, int x, int y);

	//フォントレンダリング関数.
	void RenderFont(int FontIndex, int x, int y);

	static CDebugText* GetDebugTextInstance() 
	{
		static CDebugText s_Instance;
		return &s_Instance;
	}

private:
	//シェーダ作成.
	HRESULT InitShader();

	//ブレンドステート作成.
	HRESULT InitBlend();

	//↓アプリにひとつ.
	ID3D11Device*			m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;			//デバイスコンテキスト.

	//↓モデルの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pConstantBuffer;		//コンスタントバッファ.

	//↓モデルごとに用意.
	ID3D11Buffer*			m_pVertexBuffer[100];	//頂点バッファ.

	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.
	ID3D11ShaderResourceView*	m_pAsciiTexture;	//テクスチャ.

	ID3D11BlendState*		m_pAlphaBlend;			//アルファブレンド有効.
	ID3D11BlendState*		m_pNoAlphaBlend;		//アルファブレンド無効.

	DWORD					m_dwWindowWidth;		//ウィンドウ幅.
	DWORD					m_dwWindowHeight;		//ウィンドウ高さ.

	float					m_fKerning[100];		//カーニング（100個分）.
	float					m_fAlpha;				//透過値.
	float					m_fScale;				//拡縮値(25pixelを基準25pixel = 1.0f).
	D3DXVECTOR4				m_vColor;				//色.

	D3DXVECTOR3				m_vPos;					//位置.
	D3DXMATRIX				m_mView;				//ビュー行列.
	D3DXMATRIX				m_mProj;				//プロジェクション行列.
};

#endif	//#ifndef CDEBUG_TEXT_H