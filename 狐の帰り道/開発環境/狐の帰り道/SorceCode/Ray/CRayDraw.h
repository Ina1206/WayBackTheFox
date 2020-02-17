#ifndef CRAY_DRAW_H
#define CRAY_DRAW_H

#include "..\Drawing\CCommon.h"
#include "RayStruct.h"

//レイ表示クラス.
class CRayDraw
	: public CCommon
{
public:

	CRayDraw();
	~CRayDraw();

	//初期化.
	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	//描画.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	//情報置換処理関数.
	void SetRay(RAY Ray) { m_Ray = Ray; }

	//================シングルトン=================//.
	static CRayDraw* GetRayDrawInstance()
	{
		static CRayDraw s_Instance;
		return &s_Instance;
	}


private:
	//シェーダ作成.
	HRESULT InitShader();

	//レイ初期化.
	HRESULT InitModel();

	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//ワールド,ビュー,プロジェクションの合成変換行列.
		D3DXVECTOR4 vColor;		//カラー(RGBAの型に合わせる).
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
	};

	//↓モデルの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pConstantBuffer;		//コンスタントバッファ.

	//↓モデルごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.

	//レイ構造体.
	RAY		m_Ray;

};

#endif //#ifndef CRAY_DRAW_H.