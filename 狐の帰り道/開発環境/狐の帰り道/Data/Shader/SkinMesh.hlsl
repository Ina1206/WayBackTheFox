/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
*	Auther		: an.
**/
//定義.
#define MAX_BONE_MATRICES (255)

//グローバル.
Texture2D		g_Texture	: register( t0 );	//テクスチャーは レジスターt(n).
SamplerState	g_Sampler	: register( s0 );	//サンプラーはレジスターs(n).


//コンスタントバッファ(メッシュごと).
cbuffer per_mesh		: register( b0 )
{
	matrix g_mW;		//ワールド行列.
	matrix g_mWVP;		//ワールドから射影までの変換行列.
};
//コンスタントバッファ(マテリアルごと).
cbuffer per_material	: register( b1 )
{
	float4 g_Ambient	= float4( 0, 0, 0, 0 );	//アンビエント光.
	float4 g_Diffuse	= float4( 1, 0, 0, 0 );	//拡散反射(色）
	float4 g_Specular	= float4( 1, 1, 1, 1 );	//鏡面反射.
};
//コンスタントバッファ(フレームごと).
cbuffer per_frame		: register( b2 )
{
	float4 g_vLight;//ライトの方向ベクトル.
	float4 g_vEye;	//カメラ位置.
};
//ボーンのポーズ行列が入る.
cbuffer per_bones		: register( b3 )
{
	matrix g_mConstBoneWorld[MAX_BONE_MATRICES];
};

//スキニング後の頂点・法線が入る.
struct Skin
{
	float4 Pos;
	float3 Norm;
};
//バーテックスバッファーの入力.
struct VSSkinIn
{
	float3 Pos		: POSITION;		//位置.  
	float3 Norm		: NORMAL;		//頂点法線.
	float2 Tex		: TEXCOORD;		//テクスチャー座標.
	uint4  Bones	: BONE_INDEX;	//ボーンのインデックス.
	float4 Weights	: BONE_WEIGHT;	//ボーンの重み.
};

//ピクセルシェーダーの入力（バーテックスバッファーの出力）　
struct PSSkinIn
{
	float4 Pos	: SV_Position;	//位置.
	float3 Norm : NORMAL;		//頂点法線.
	float2 Tex	: TEXCOORD;		//テクスチャー座標.
	float4 Color: COLOR0;		//最終カラー（頂点シェーダーにおいての）.
};


//指定した番号のボーンのポーズ行列を返す.
//サブ関数（バーテックスシェーダーで使用）.
matrix FetchBoneMatrix( uint iBone )
{
	return g_mConstBoneWorld[iBone];
}


//頂点をスキニング（ボーンにより移動）する.
//サブ関数（バーテックスシェーダーで使用）.
Skin SkinVert( VSSkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	float3 Norm = Input.Norm;
	//ボーン0.
	uint iBone	=Input.Bones.x;
	float fWeight= Input.Weights.x;
	matrix m	=  FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン1.
	iBone	= Input.Bones.y;
	fWeight	= Input.Weights.y;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン2.
	iBone	= Input.Bones.z;
	fWeight	= Input.Weights.z;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン3.
	iBone	= Input.Bones.w;
	fWeight	= Input.Weights.w;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );

	return Output;
}

// バーテックスシェーダ.
PSSkinIn VS_Main( VSSkinIn input )
{
	PSSkinIn output;
	Skin vSkinned = SkinVert( input);

	output.Pos	= mul( vSkinned.Pos, g_mWVP );
	output.Norm	= normalize( mul( vSkinned.Norm, (float3x3)g_mW ) );
	output.Tex	= input.Tex;
	float3 LightDir	= normalize( g_vLight );
	float3 PosWorld	= mul( vSkinned.Pos, g_mW );
	float3 ViewDir	= normalize( g_vEye - PosWorld );
	float3 Normal	= normalize( output.Norm );
	float4 NL		= saturate( dot( Normal, LightDir ) );

	float3 Reflect	= normalize( 2 * NL * Normal - LightDir );
	float4 specular = pow( saturate( dot( Reflect, ViewDir ) ), 4.0f ); 

	output.Color	= g_Diffuse * NL + specular * g_Specular;

	output.Color	= g_Ambient;

	return output;
}


// ピクセルシェーダ.
float4 PS_Main( PSSkinIn input ) : SV_Target
{
	// テクスチャからピクセル色を取り出す.
	float4 TexDiffuse = g_Texture.Sample( g_Sampler, input.Tex );
	// 出力用を作成.
	float4 RetColor = input.Color/*/2.0f */+ TexDiffuse/*/2.0f*/;

	//RetColor = g_Ambient;

	// テクスチャのα値をそのまま使用。
	RetColor.a = TexDiffuse.a;

	return RetColor;
}
