/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
**/
#ifndef C_DX9SKIN_MESH_H
#define C_DX9SKIN_MESH_H
//警告についてのコード分析を無効にする。4005：再定義.
#pragma warning( disable : 4005 )

#include "CDX9SkinMeshParser.h"

//==================================================================================================
//
//	スキンメッシュクラス.
//
//==================================================================================================
class CDX9SkinMesh
{
public:
	//メッシュ単位.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//ワールド行列.
		D3DXMATRIX	mWVP;		//ワールドから射影までの変換行列.
	};

	//マテリアル単位.
	struct CBUFFER_PER_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//アンビエント光.
		D3DXVECTOR4 vDiffuse;	//ディフューズ色.
		D3DXVECTOR4 vSpecular;	//鏡面反射.
	};

	//シェーダーに渡す値.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4 vLightDir;	//ライト方向.
		D3DXVECTOR4 vEye;		//カメラ位置.
	};

	//ボーン単位.
	struct CBUFFER_PER_BONES
	{
		D3DXMATRIX mBone[D3DXPARSER::MAX_BONES];
		CBUFFER_PER_BONES()
		{
			for (int i = 0; i < D3DXPARSER::MAX_BONES; i++)
			{
				D3DXMatrixIdentity(&mBone[i]);
			}
		}
	};


	//頂点構造体.
	struct MY_SKINVERTEX
	{
		D3DXVECTOR3	vPos;		//頂点位置.
		D3DXVECTOR3	vNorm;		//頂点法線.
		D3DXVECTOR2	vTex;		//UV座標.
		UINT bBoneIndex[4];		//ボーン 番号.
		float bBoneWeight[4];	//ボーン 重み.
		MY_SKINVERTEX()
			: vPos()
			, vNorm()
			, vTex()
			, bBoneIndex()
			, bBoneWeight()
		{}
	};

	//パーサークラスからアニメーションコントローラーを取得する.
	LPD3DXANIMATIONCONTROLLER GetAnimController()
	{
		return m_pD3dxMesh->m_pAnimController;
	}

	//========================追加===========================.

	//テクスチャ切り替え用.
	struct CHANGE_TEXTURE
	{
		CHAR						szTextureName[512];			//テクスチャファイル名.
		ID3D11ShaderResourceView*	pTexture;					//切り替えるテクスチャ.

		ID3D11ShaderResourceView*	pDefTexture;				//切り替える前のテクスチャ.
		CHAR						szTargetTextureName[512];	//切り替える対象のテクスチャ名.

		CHANGE_TEXTURE()
			: szTextureName()
			, pTexture(nullptr)
			, pDefTexture(nullptr)
			, szTargetTextureName()
		{}
		~CHANGE_TEXTURE()
		{
			SAFE_RELEASE(pTexture);
			pDefTexture = nullptr;		//アドレスのみなのでnullptrで初期化.
		}
	};


	CHANGE_TEXTURE* m_pChangeTexture;
	bool			m_IsEnabelChangeTextureSystem;

	void SetEnabelChangeTextureSystem(bool flag) {
		m_IsEnabelChangeTextureSystem = flag;
	}

	void SetChangeTexture(CHANGE_TEXTURE* pCT) {
		m_pChangeTexture = pCT;
	}

	ID3D11Device* GetDevice() { return m_pDevice11; }
	//========================ここまで===========================.



	//メソッド.
	CDX9SkinMesh();
	~CDX9SkinMesh();

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName);
	//Xファイルからスキンメッシュを作成する.
	HRESULT LoadXMesh( const char* fileName );
	//描画関数.
	void Render(const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye, 
		const LPD3DXANIMATIONCONTROLLER pAC=NULL );
	//解放関数.
	HRESULT Release();

	double GetAnimSpeed()				{ return m_dAnimSpeed;		}
	void SetAnimSpeed( double dSpeed )	{ m_dAnimSpeed = dSpeed;	}

	double GetAnimTime()				{ return m_dAnimTime;		}
	void SetAnimTime( double dTime )	{ m_dAnimTime = dTime;		}

	//アニメーションコントローラを取得.
	LPD3DXANIMATIONCONTROLLER GetAnimationController() { return m_pD3dxMesh->m_pAnimController; }

	//アニメーションセットの切り替え.
	void ChangeAnimSet( int index, LPD3DXANIMATIONCONTROLLER pAC=nullptr );
	//アニメーションセットの切り替え(開始フレーム指定可能版).
	void ChangeAnimSet_StartPos( int index, double dStartFramePos, LPD3DXANIMATIONCONTROLLER pAC=nullptr );

	//アニメーション停止時間を取得.
	double GetAnimPeriod( int index );
	//アニメーション数を取得.
	int GetAnimMax( LPD3DXANIMATIONCONTROLLER pAC=NULL );

	//指定したボーン情報(座標・行列)を取得する関数.
	bool GetMatrixFromBone(const char* sBoneName, D3DXMATRIX* pOutMat );
	bool GetPosFromBone(const char* sBoneName, D3DXVECTOR3* pOutPos);
	bool GetDeviaPosFromBone(const char* sBoneName, D3DXVECTOR3* pOutPos, D3DXVECTOR3 vSpecifiedPos = { 0.0f, 0.0f, 0.0f });


	//位置情報を設定.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//位置情報を取得.
	D3DXVECTOR3 GetPosition() {
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
	//拡縮情報を設定・取得.
	void SetScale(float Scale) {
		m_vScale.x = Scale;
		m_vScale.y = Scale;
		m_vScale.z = Scale;
	}
	D3DXVECTOR3 GetScale() {
		return m_vScale;
	}

	//中心軸のズレを取得.
	void SetPrePos(D3DXVECTOR3 PrePos) {
		m_vPrePos = PrePos;
	}

private:
	HWND m_hWnd;

	//Dx9.
	LPDIRECT3DDEVICE9		m_pDevice9;

	//Dx11.
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;
	ID3D11SamplerState*		m_pSampleLinear;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11Buffer*			m_pCBufferPerMesh;		//コンスタントバッファ(メッシュ毎).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//コンスタントバッファ(マテリアル毎).
	ID3D11Buffer*			m_pCBufferPerFrame;		//コンスタントバッファ(フレーム毎).
	ID3D11Buffer*			m_pCBufferPerBone;		//コンスタントバッファ(ボーン毎).

	D3DXVECTOR3		m_vPos;		//位置.
	D3DXVECTOR3		m_vRot;		//角度.
	D3DXVECTOR3		m_vScale;	//大きさ.
	D3DXVECTOR3		m_vPrePos;	//読み込み時のオブジェクトの中心軸差分.

	D3DXMATRIX		m_mWorld;
	D3DXMATRIX		m_mRotation;

	D3DXMATRIX		m_mView;
	D3DXMATRIX		m_mProj;

	D3DXVECTOR3		m_vLight;
	D3DXVECTOR3		m_vEye;

	//アニメーション速度.
	double m_dAnimSpeed;
	double m_dAnimTime;

	//解放処理用に.
	SKIN_PARTS_MESH* m_pReleaseMaterial;

	//メッシュ.
	D3DXPARSER* m_pD3dxMesh;

	//XFileのパス.
	CHAR	m_FilePath[256];

	//アニメーションフレーム.
	int		m_iFrame;

	HRESULT InitShader();
	HRESULT CreateIndexBuffer( DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer );
	void RecursiveSetNewPoseMatrices( BONE* pBone,D3DXMATRIX* pmParent );

	//全てのメッシュを作成する.
	void BuildAllMesh( D3DXFRAME* pFrame );
	
	//メッシュを作成する.
	HRESULT CreateAppMeshFromD3DXMesh( LPD3DXFRAME pFrame );

	//Xファイルからスキン関連の情報を読み出す関数.
	HRESULT ReadSkinInfo( MYMESHCONTAINER* pContainer, MY_SKINVERTEX* pvVB, SKIN_PARTS_MESH* pParts );

	//ボーンを次のポーズ位置にセットする関数.
	void SetNewPoseMatrices( SKIN_PARTS_MESH* pParts, int frame, MYMESHCONTAINER* pContainer );
	//次の(現在の)ポーズ行列を返す関数.
	D3DXMATRIX GetCurrentPoseMatrix( SKIN_PARTS_MESH* pParts, int index );

	//フレーム描画.
	void DrawFrame( LPD3DXFRAME pFrame );
	//パーツ描画.
	void DrawPartsMesh( SKIN_PARTS_MESH* p, D3DXMATRIX World, MYMESHCONTAINER* pContainer );
	void DrawPartsMeshStatic( SKIN_PARTS_MESH* pMesh, D3DXMATRIX World, MYMESHCONTAINER* pContainer );

	//全てのメッシュを削除.
	void DestroyAllMesh( D3DXFRAME* pFrame );
	HRESULT DestroyAppMeshFromD3DXMesh( LPD3DXFRAME p );

	//コンスタントバッファ作成関数.
	HRESULT CreateCBuffer(ID3D11Buffer** pConstantBuffer, UINT size);
	//サンプラー作成関数.
	HRESULT CreateLinearSampler(ID3D11SamplerState** pSampler);
};

#endif//#ifndef C_DX9SKIN_MESH_H