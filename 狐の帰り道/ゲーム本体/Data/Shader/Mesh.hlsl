//グローバル変数.

//テクスチャはレジスタ t(n).
Texture2D		g_Texture	: register(t0);
//サンプラはレジスタ   s(n).
SamplerState	g_samLinear	: register(s0);

//影の最大数(表示限界数)
#define SHADOW_MAX 10

//コンスタントバッファ.
cbuffer per_mesh : register(b0)
{
	matrix g_mW;		//ワールド行列.
	matrix g_mWVP;		//ワールド,ビュー,プロジェクションの合成行列.
};
//マテリアル単位.
cbuffer per_material : register(b1)
{
	float4 g_vAmbient;	//アンビエント色(環境色).
	float4 g_vDiffuse;	//ディフューズ色(拡散反射色).
	float4 g_vSpecular;	//スペキュラ色(鏡面反射色).
};
//フレーム単位.
cbuffer per_frame	: register(b2)
{
	float4	g_vCamPos					: packoffset(c0);	//カメラ情報.
	float4	g_vLightDir					: packoffset(c1);	//ライト方向.
	float4	g_vCasterToLight			: packoffset(c2);	//影を落とすモデルとライトを結ぶベクトル.
	float4  g_vCasterPos[SHADOW_MAX]	: packoffset(c3);	//影を落とすキャスター位置.
};

//頂点シェーダの出力パラメータ.
struct VS_OUTPUT
{
	float4 Pos			: SV_Position;
	float4 Color		: COLOR;
	float3 Light		: TEXCOORD0;
	float3 Normal		: TEXCOORD1;
	float3 EyeVector	: TEXCOORD2;
	float2 Tex			: TEXCOORD3;
	float4 PosWorld		: TEXCOORD4;
};

//-------------------------------------------------------.
//		頂点(バーテックス)シェーダ.
//-------------------------------------------------------.
VS_OUTPUT VS_Main(float4 Pos : POSITION,
				  float4 Norm: NORMAL,
				  float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//法線をワールド空間に.
	Norm.w = 0;	//w=0で移動成分を反映させない.
	output.Normal = mul(Norm, g_mW);
	output.Pos = mul(Pos, g_mWVP);
	//ライト方向.
	output.Light = g_vLightDir;
	//視線ベクトル.
	output.PosWorld = mul(Pos, g_mW);
	output.EyeVector = g_vCamPos - output.PosWorld;

	//float3 Normal = normalize(output.Normal);
	//float3 LightDir = normalize(output.Light);
	//float3 ViewDir = normalize(output.EyeVector);
	//float4 NL = saturate(dot(Normal, LightDir));

	//float3 Reflect = normalize(2 * NL*Normal - LightDir);
	//float4 Specular = pow(saturate(dot(Reflect, ViewDir)), 4);
	//
	////output.Color = g_vDiffuse * NL + Specular * g_vSpecular;
	output.Color = g_vAmbient;
	
	//テクスチャ座標を渡す.
	output.Tex = Tex;

	return output;
}

//*******************************************************.
//	ラスタライザ(アプリ側で設定する項目。ここでは触れない).
//*******************************************************.

//-------------------------------------------------------.
//	ピクセルシェーダ.
//-------------------------------------------------------.
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	float4 Color = g_Texture.Sample(g_samLinear, input.Tex) / 1.0f + input.Color / 1.0f;

	for (int shadow = 0; shadow < SHADOW_MAX; shadow++) {
		float4 vToCaster = normalize(g_vCasterPos[shadow] - input.PosWorld);
		float cos = saturate(dot(g_vCasterToLight, vToCaster));

		if (cos > 0.98f) {
			Color *= 0.5f;
			//break;
		}
	}

	return Color;
}

//============テクスチャ無し============================================.
//-------------------------------------------------------.
//		頂点(バーテックス)シェーダ.
//-------------------------------------------------------.
VS_OUTPUT VS_NoTex(float4 Pos : POSITION,
				   float4 Norm : NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//法線をワールド空間に.
	Norm.w = 0;	//w=0で移動成分を反映させない.
	output.Normal = mul(Norm, g_mW);
	output.Pos = mul(Pos, g_mWVP);
	//ライト方向.
	output.Light = g_vLightDir;
	//視線ベクトル.
	float3 PosWorld = mul(Pos, g_mW);
	output.EyeVector = g_vCamPos - PosWorld;

	float3 Normal = normalize(output.Normal);
	float3 LightDir = normalize(output.Light);
	float3 ViewDir = normalize(output.EyeVector);
	float4 NL = saturate(dot(Normal, LightDir));

	float3 Reflect = normalize(2 * NL*Normal - LightDir);
	float4 Specular = pow(saturate(dot(Reflect, ViewDir)), 4);

	output.Color = g_vDiffuse * NL + Specular * g_vSpecular;

	return output;
}

//-------------------------------------------------------.
//	ピクセルシェーダ.
//-------------------------------------------------------.
float4 PS_NoTex(VS_OUTPUT input) : SV_Target
{
	float4 Color = input.Color;

	return Color;
}


//========================================================.
//	以降、板ポリゴン用コード.
//========================================================.
//コンスタントバッファ.
cbuffer Ita_Global : register(b2)	//レジスタを数分追加.
{
	matrix g_WVP;	//ワールド，ビュー，プロジェクションまでの変換行列.
	float4 g_Color;	//色.
	float  g_Amvient;	//透過色.
	float4 g_UV;	//UV座標.
};

//構造体.
struct VS_ITAOUT
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

//頂点シェーダ.
VS_ITAOUT VS_Ita(float4 Pos : POSITION,
				 float2 Tex : TEXCOORD)
{
	VS_ITAOUT output = (VS_ITAOUT)0;
	output.Pos = mul(Pos, g_WVP);
	output.Tex = Tex;

	//テクスチャのUV座標を操作する.
	output.Tex.x += g_UV.x;

	return output;
}

//ピクセルシェーダ.
float4 PS_Ita(VS_ITAOUT input) : SV_Target
{
	float4 color = g_Texture.Sample(g_samLinear, input.Tex);
	color.a *= g_Amvient;

	return color;	//色を返す.
}