#ifndef CPARTICLE_H
#define CPARTICLE_H
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning( disable:4005 )

#include "..\..\CCommon.h"


/********************************************
*	パーティクルクラス.
**/
class CParticle
	: public CCommon	//共通クラスを継承.
{
public:
	//関数のオーバーロード.
	CParticle();	//コンストラクタ（引数なしコンストラクタまたはデフォルトコンストラクタともいう）.
	~CParticle();	//デストラクタ.

	//初期化.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName);

	//解放.
	void Release();

	//シェーダ作成.
	HRESULT InitShader();

	//モデル作成.
	HRESULT InitModel();

	//テクスチャ読み込み＆作成.
	HRESULT InitTexture(const char* fileName);

	//レンダリング用.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCamPos);


	//シェーダを外す関数.
	void DetachShader();

	//位置情報を設定.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//回転情報を設定.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//回転情報を取得.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
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
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
	};

	//パーティクル用構造体.
	struct PART
	{
		D3DXVECTOR3 vPos;		//位置.
		D3DXVECTOR3 vDir;		//方向.
		float		Speed;		//速度.
		int			BirthFrame;	//開始フレーム.
		//構造体の初期化(コンストラクタ).
		PART()
			: vPos(0.0f, 0.0f, 0.0f)
			, vDir(0.0f, 0.0f, 0.0f)
			, Speed(0.0f)
			, BirthFrame(0)
		{};
	};
	
	//↓モデルの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11GeometryShader*	m_GeometryShader;		//ジオメトリシェーダ.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pConstantBuffer;		//コンスタントバッファ.

	//↓モデルごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.

	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.
	ID3D11ShaderResourceView*	m_pTexture;			//テクスチャ.

	int						m_AnimCount;			//カウンタ.
	D3DXVECTOR2				m_UV;					//テクスチャUV座標.

	D3DXVECTOR3				m_vPos;					//位置.
	float					m_Scale;				//拡縮値.

	PART*					m_pParticleArray;		//パーティクル配列.
	int						m_Frame;				//フレーム数.


	D3DXVECTOR3				m_vRot;					//回転値(x,y,z).

};

#endif//#ifndef CPARTICLE_H