//�O���[�o���ϐ�.

//�e�N�X�`���̓��W�X�^ t(n).
Texture2D		g_Texture	: register(t0);
//�T���v���̓��W�X�^   s(n).
SamplerState	g_samLinear	: register(s0);

//�R���X�^���g�o�b�t�@.
cbuffer global
{
	matrix g_WVP;		//���[���h�C�r���[�C�v���W�F�N�V�����܂ł̕ϊ��s��.
	float4 g_Color;		//�F.
	float  g_fAlpha;	//���ߒl.
};

//�\����.
struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

//���_�V�F�[�_.
VS_OUTPUT VS_Main(float4 Pos : POSITION,
				  float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, g_WVP);
	output.Tex = Tex;

	return output;
}

//�s�N�Z���V�F�[�_.
float4 PS_Main(VS_OUTPUT input) : SV_Target
{
	float4 color = g_Color * g_Texture.Sample(g_samLinear, input.Tex);
	//0�ɂ����Ă�0�ɂȂ�悤�Ɋ|���Z�����Ă���.
	color.a *= g_fAlpha;
	return color;
}