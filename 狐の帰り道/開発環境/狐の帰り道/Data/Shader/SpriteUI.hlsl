//�O���[�o���ϐ�.
//�e�N�X�`���́A���W�X�^ t(n).
//t(n)�e�N�X�`���̉��ڂɂ��邩���w��.
Texture2D		g_Texture : register(t0);
//�T���v���́A���W�X�^ s(n).
SamplerState	g_samLinear : register(s0);

//�A�v���T�C�h�œ����������̂��V�F�[�_�ɓn���Čv�Z���Ă܂��n��.
//�R���X�^���g�o�b�t�@.
cbuffer gloabl	: register(b0)
{
	//c0�`c3��g_mW���苒����̂�c4����n�߂�.
	//c�����16�o�C�g.
	matrix	g_mW			: packoffset(c0);	//���[���h�s��.
	float	g_fViewPortW	: packoffset(c4);	//�r���[�|�[�g��.
	float	g_fViewPortH	: packoffset(c5);	//�r���[�|�[�g����.
	float	g_fAlpha		: packoffset(c6);	//�A���t�@�l.
	float2	g_vUV			: packoffset(c7);	//UV���W.
};

//�\����.
struct VS_OUTPUT
{
	float4 Pos		: SV_Position;
	float2 Tex		: TEXCOORD;
};

//���_�V�F�[�_.
VS_OUTPUT VS_Main(float4 Pos : POSITION,
				  float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, g_mW);

	//�X�N���[�����W�ɍ��킹��v�Z.
	//�J�����̈ʒu��v���W�F�N�V�����Ȃǂ͖���.
	output.Pos.x = (output.Pos.x / g_fViewPortW) * 2.0f - 1.0f;
	output.Pos.y = 1.0f - (output.Pos.y / g_fViewPortH) * 2.0f;

	output.Tex = Tex;

	//UV���W�����炷.
	output.Tex.x += g_vUV.x;
	output.Tex.y += g_vUV.y;
	
	return output;
}

//�s�N�Z���V�F�[�_.
float4 PS_Main(VS_OUTPUT input) : SV_Target
{
	//�e���_�ɂ����RGBA���ǂ��������ɒ���t���邩.
	float4 color = g_Texture.Sample(g_samLinear, input.Tex);
	//float4�^�̓h�b�g�ŕ\���ł���l��rgba�Őݒ肷�邱�Ƃ��ł���(�V�F�[�_��).
	//=�Ŏ����čs�����ꍇ�A���ړ���Ă��܂��̂Ń_��
	//(������������Ȃ������������疳����蓧�����Ă��܂������Ȃ��Ă��܂�����).
	color.a *= g_fAlpha;	//�A���t�@�l���|�����킹��.
	
	return color;
}