#ifndef CDX9MESH_H
#define CDX9MESH_H
//警告につてのコード分析を無効にする. 4005:再定義.
#pragma warning( disable:4005)

#include <Windows.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//「D3DX～」の定義使用時に必要.
#include <D3D10.h>
#include "..\..\MyMacro.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx10.lib")	//「D3DX～」の定義使用時に必要になる.

#define ALIGN16 _declspec(align(16))

const int SHADOW_MAX = 10;

//スフィア構造体.
struct SPHERE
{
	D3DXVECTOR3 vCenter;	//中心.
	float		fRadius;	//半径.
};
//バウンディングボックス構造体.
struct BBOX
{
	D3DXVECTOR3 vPosMax;	//最大頂点.
	D3DXVECTOR3 vPosMin;	//最小頂点.
	D3DXVECTOR3 vAxisX;		//x軸.
	D3DXVECTOR3 vAxisY;		//y軸.
	D3DXVECTOR3 vAxisZ;		//z軸.
	FLOAT		LenghtX;	//X長さ.
	FLOAT		LenghtY;	//Y長さ.
	FLOAT		LenghtZ;	//Z長さ.

	//初期化.
	BBOX()
		: vPosMax(), vPosMin()
		, vAxisX(1.0f, 0.0f, 0.0f)
		, vAxisY(0.0f, 1.0f, 0.0f)
		, vAxisZ(0.0f, 0.0f, 1.0f)
		, LenghtX(0.0f), LenghtY(0.0f), LenghtZ(0.0f)
	{}
};

//カメラ情報.
//今回はY軸回転のみ対応.
struct CAMERA
{
	D3DXVECTOR3	vPos;	//位置.
	D3DXVECTOR3 vLook;	//注視位置.
	float		fYaw;	//Y軸回転.
	D3DXMATRIX	mRot;	//回転行列.
};

//影情報.
struct SHADOW
{
	D3DXVECTOR3 vCasterPos;	//キャスター位置.
	bool		bDispFlag;	//表示切替フラグ.

	SHADOW(const D3DXVECTOR3& vPos, bool bDisp)
		: vCasterPos	(vPos)
		, bDispFlag		(bDisp)
	{}

	SHADOW()
		: SHADOW(D3DXVECTOR3(0.0f, 0.0f, 0.0f), false)
	{}
};

//メッシュデータをファイルから取り出す為だけにDirectX9を使用する.
//※レンダリング(描画)は、DirectX11で行う.
class CDX9Mesh
{
public:
	CDX9Mesh();		//コンストラクタ.
	~CDX9Mesh();	//デストラクタ.

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName);
	//メッシュ読み込み.
	HRESULT LoadXMesh(const char* fileName);
	//解放関数.
	void Release();

	//シェーダ作成.
	HRESULT InitShader();

	//レンダリング用.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos);

	//位置情報を設定.
	//inline void のinlineは関数自体を直接展開するため速度が上がる.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//位置情報を取得.
	D3DXVECTOR3 GetPosition()
	{
		return m_vPos;
	}
	//回転情報を設定.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//回転情報を取得.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
	}
	//拡縮情報を設定.
	void SetScale(float Scale)	{ m_fScale = Scale; }
	//拡縮情報を取得.
	float GetScale()			{ return m_fScale; }

	//初期位置をずらす.
	void SetPrePos(D3DXVECTOR3 vPrePos) { m_vPrePos = vPrePos; }

	//メッシュを取得.
	LPD3DXMESH GetMesh() {
		return m_pMesh;
	}

	SPHERE m_Sphere;			//スフィア構造体.
	BBOX   m_BBox;				//Bボックス構造体.


	LPD3DXMESH	m_pMeshForRay;	//レイとメッシュ用.

private:
	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//ワールド行列.
		D3DXMATRIX	mWVP;		//ワールド,ビュー,プロジェクションの合成変換行列.
	};
	struct CBUFFER_PRE_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//アンビエント色(環境色).
		D3DXVECTOR4	vDiffuse;	//ディフューズ色(拡散反射色).
		D3DXVECTOR4 vSpecular;	//スペキュラ色(鏡面反射色).
	};
	//フレーム単位で渡す情報.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4			vCamPos;				//カメラ位置(視点位置).
		D3DXVECTOR4			vLightDir;				//ライト方向.
		ALIGN16 D3DXVECTOR4 vCasterToLight;			//影を落とすモデルとライトを結ぶベクトル.
		ALIGN16	D3DXVECTOR4 vCasterPos[SHADOW_MAX];	//影を落とすキャスターの位置.
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
		D3DXVECTOR3 Normal;		//法線(陰影計算に必須).
		D3DXVECTOR2 Tex;		//テクスチャ座標.
	};
	//マテリアル構造体.
	struct MY_MATERIAL
	{
		D3DXVECTOR4					Ambient;			//アンビエント.
		D3DXVECTOR4					Diffuse;			//ディフューズ.
		D3DXVECTOR4					Specular;			//スペキュラー.
		char						szTextureName[128];	//テクスチャファイル名.
		ID3D11ShaderResourceView*	pTexture;			//テクスチャ.
		DWORD						dwNumFace;			//そのマテリアルのポリゴン数.
		//コンストラクタ.
		MY_MATERIAL()
			:Ambient(),Diffuse(),Specular(), szTextureName()
			,pTexture(nullptr), dwNumFace(0)
		{
		}
		//デストラクタ.
		~MY_MATERIAL(){
			SAFE_RELEASE(pTexture);
		}
	};


	HWND					m_hWnd;					//ウィンドウハンドル.

	//Dx9.
	LPDIRECT3D9				m_pD3d9;				//Dx9オブジェクト.
	LPDIRECT3DDEVICE9		m_pDevice9;				//Dx9デバイスオブジェクト.

	//Dx11.
	ID3D11Device*			m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;			//デバイスコンテキスト.

	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pCBufferPerMesh;		//コンスタントバッファ(メッシュ毎).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//コンスタントバッファ(マテリアル毎).
	ID3D11Buffer*			m_pCBufferPerFrame;		//コンスタントバッファ(フレーム毎)

	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.
	ID3D11Buffer**			m_ppIndexBuffer;		//インデックスバッファ.
	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.

	LPD3DXMESH				m_pMesh;				//メッシュオブジェクト.
	DWORD					m_NumMaterials;			//マテリアル数.

	MY_MATERIAL*			m_pMaterials;			//マテリアル構造体.
	DWORD					m_NumAttr;				//属性数.
	DWORD					m_AttrID[300];			//属性ID　※300属性まで.

	bool					m_EnableTexture;		//テクスチャあり.

	float					m_fScale;				//拡大縮小値(x,y,z等倍).
	D3DXVECTOR3				m_vRot;					//回転値(x,y,z).
													//※x = Pitch, y = Yaw, z = Roll.
	D3DXVECTOR3				m_vPos;					//位置(x,y,z).
	D3DXVECTOR3				m_vPrePos;

	SHADOW*					m_pstShadow;			//影の情報.
	int						m_ShadowMax;			//影の最大数.

	//レンダリング関数(クラス内でのみ使用).
	void RenderMesh(D3DXMATRIX& mWorld, D3DXMATRIX& mView, D3DXMATRIX& mProj);

public:
	//影関係の情報を設定処理関数.
	void SetShadow(SHADOW* shadow, int shadowMax) {
		m_pstShadow = shadow;
		m_ShadowMax = shadowMax;
	}
};


#endif	//#ifndef CDX9MESH_H