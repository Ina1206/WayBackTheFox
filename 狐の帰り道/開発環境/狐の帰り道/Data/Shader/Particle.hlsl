//グローバル.

//テクスチャ.
Texture2D		g_Texture	: register(t0);
//サンプラ.
SamplerState	g_Sampler	: register(s0);

//コンスタントバッファ.
cbuffer global
{
	matrix g_WVP;	//ワールド,ビュー，プロジェクション，の変換行列.
};

//構造体.
struct VS_OUTPUT
{
	float4 Pos : SV_Position;
};

struct GS_OUTPUT
{
	float4 Pos	: SV_Position;
	float2 UV	: TEXCOORD;
};

//頂点シェーダ.
VS_OUTPUT VS_Main(float4 Pos : POSITION)
{
	VS_OUTPUT output;
	output.Pos = Pos;	//ここでは頂点を変換しないでそのままジオメトリシェーダに渡す.

	return output;
}

//ジオメトリシェーダ.
//やりようによっては手前高ポリ、奥低ポリにできる.
//※ポリゴンを分割.
[maxvertexcount(4)]	//頂点の最大数.
void GS_Point(point VS_OUTPUT Input[1],
	inout TriangleStream<GS_OUTPUT> TriStream)
	//TriangleStream:ジオメトリシェーダで作成される三角形.
{
	float w = 0;	//4つの頂点全てのw値を１番目[0]の頂点のwに合わせる.
					//合わせるのは何番目でもいい。全てが同じなら.
					//ポリゴンにパースが掛かってしまうのを防止.
					//パース…手前と遠くの大きさの違い（一点透視法とか二点透視法とか）.
	
	//四角形の頂点.
	//初期化.
	GS_OUTPUT output = (GS_OUTPUT)0;
	output.Pos = mul(Input[0].Pos, g_WVP);
	w = output.Pos.w;
	output.UV = float2(0.0f, 0.0f);
	TriStream.Append(output);	//Append():頂点の追加.

	output.Pos = Input[0].Pos + float4(0.5f, 0.0f, 0.0f, 0.0f);
	output.Pos = mul(output.Pos, g_WVP);
	output.Pos.w = w;
	output.UV = float2(1.0f, 0.0f);
	TriStream.Append(output);

	output.Pos = Input[0].Pos + float4(0.0f, -0.5f, 0.0f, 0.0f);
	output.Pos = mul(output.Pos, g_WVP);
	output.Pos.w = w;
	output.UV = float2(0.0f, 1.0f);
	TriStream.Append(output);

	output.Pos = Input[0].Pos + float4(0.5f, -0.5f, 0.0f, 0.0f);
	output.Pos = mul(output.Pos, g_WVP);
	output.Pos.w = w;
	output.UV = float2(1.0f, 1.0f);
	TriStream.Append(output);

	TriStream.RestartStrip();	//3つの頂点を追加した後、呼び出して設定.
}

//ピクセルシェーダ.
float4 PS_Main(GS_OUTPUT Input) : SV_Target
{
	//テクスチャを貼る.
	return g_Texture.Sample(g_Sampler, Input.UV);
}
