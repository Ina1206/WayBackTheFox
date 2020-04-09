//グローバル変数.
//テクスチャは、レジスタ t(n).
//t(n)テクスチャの何個目にするかを指す.
Texture2D		g_Texture : register(t0);
//サンプラは、レジスタ s(n).
SamplerState	g_samLinear : register(s0);

//アプリサイドで動かしたものをシェーダに渡して計算してまた渡す.
//コンスタントバッファ.
cbuffer gloabl	: register(b0)
{
	//c0～c3がg_mWが占拠するのでc4から始める.
	//c一つ分で16バイト.
	matrix	g_mW			: packoffset(c0);	//ワールド行列.
	float	g_fViewPortW	: packoffset(c4);	//ビューポート幅.
	float	g_fViewPortH	: packoffset(c5);	//ビューポート高さ.
	float	g_fAlpha		: packoffset(c6);	//アルファ値.
	float2	g_vUV			: packoffset(c7);	//UV座標.
};

//構造体.
struct VS_OUTPUT
{
	float4 Pos		: SV_Position;
	float2 Tex		: TEXCOORD;
};

//頂点シェーダ.
VS_OUTPUT VS_Main(float4 Pos : POSITION,
				  float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, g_mW);

	//スクリーン座標に合わせる計算.
	//カメラの位置やプロジェクションなどは無視.
	output.Pos.x = (output.Pos.x / g_fViewPortW) * 2.0f - 1.0f;
	output.Pos.y = 1.0f - (output.Pos.y / g_fViewPortH) * 2.0f;

	output.Tex = Tex;

	//UV座標をずらす.
	output.Tex.x += g_vUV.x;
	output.Tex.y += g_vUV.y;
	
	return output;
}

//ピクセルシェーダ.
float4 PS_Main(VS_OUTPUT input) : SV_Target
{
	//各頂点によってRGBAをどういう風に張り付けるか.
	float4 color = g_Texture.Sample(g_samLinear, input.Tex);
	//float4型はドットで表示できる値はrgbaで設定することができる(シェーダは).
	//=で持って行った場合、直接入れてしまうのでダメ
	//(もし透明じゃない処理だったら無理やり透明してしまい黒くなってしまうから).
	color.a *= g_fAlpha;	//アルファ値を掛け合わせる.
	
	return color;
}