#ifndef CSPRITE_H
#define CSPRITE_H
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning( disable:4005 )
#include "..\..\CCommon.h"
#define ALINGN16 _declspec(align(16))


/********************************************
*	スプライトクラス.
**/
class CSprite
	: public CCommon
{
public:
	CSprite();	//コンストラクタ.
	~CSprite();	//デストラクタ.

	//===================定数=========================//.
	const D3DXVECTOR3	STANDERD_SCALE	= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//初期の大きさ.
	const float			ALPHA_MAX		= 1.0f;

		//幅高さ構造体(float型).
	struct WHSIZE_FLOAT
	{
		float w;
		float h;
		float z;

		WHSIZE_FLOAT()
			: w(0.0f)
			, h(0.0f)
			, z(0.0f)
		{}
	};

	//ｽﾌﾟﾗｲﾄ構造体.
	struct SPRITE_STATE
	{
		WHSIZE_FLOAT	Disp;	//表示幅高さ.
		WHSIZE_FLOAT	Base;	//元画像幅高さ.
		WHSIZE_FLOAT	Stride;	//１コマ当たりの幅高さ.
	};


	//初期化.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName, SPRITE_STATE* pSs);

	//解放.
	void Release();

	//シェーダ作成.
	HRESULT InitShader();

	//モデル作成.
	HRESULT InitModel(const char* fileName);

	//レンダリング用.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCamPos);

	//位置情報を設定.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}

	//大きさを設定.
	void SetScale(D3DXVECTOR3 Scale) {
		m_vScale = Scale;
	}

	//角度.
	void SetRotation(D3DXVECTOR3 Rot) {
		m_vRot = Rot;
	}
	//透過値を設定.
	void SetAlpha(float Alpha) {
		m_fAlpha = Alpha;
	}
	//CancelRotationのフラグの設定.
	void SetCancelRotationFlag(bool flag) {
		m_bCancelRotation = flag;
	}

private:
	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//ワールド,ビュー,プロジェクションの合成変換行列.
		D3DXVECTOR4 vColor;		//カラー(RGBAの型に合わせる).
		ALINGN16 float		Alpha;
		D3DXVECTOR4 vUV;		//UV座標(x,yのみ使用).
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
		D3DXVECTOR2 Tex;		//テクスチャ座標.
	};
	

	//↓モデルの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pConstantBuffer;		//コンスタントバッファ.

	//↓モデルごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.

	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.
	ID3D11ShaderResourceView*	m_pTexture;			//テクスチャ.

	int						m_AnimCount;			//カウンタ.
	D3DXVECTOR2				m_UV;					//テクスチャUV座標.

	D3DXVECTOR3				m_vPos;					//位置.
	D3DXVECTOR3				m_vScale;				//大きさ.
	D3DXVECTOR3				m_vRot;					//角度.
	float					m_fAlpha;				//透過値.
	bool					m_bCancelRotation;		//CancelRotationを入れるかどうかのフラグ.

	SPRITE_STATE	m_SState;	//ｽﾌﾟﾗｲﾄ情報.
	POINT			m_PatternNo;//ﾊﾟﾀｰﾝ番号.

};

#endif//#ifndef CSPRITE_H