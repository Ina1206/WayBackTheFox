//�O���[�o���ϐ�.

//�e�N�X�`���̓��W�X�^ t(n).
Texture2D		g_Texture	: register(t0);
//�T���v���̓��W�X�^   s(n).
SamplerState	g_samLinear	: register(s0);

//�e�̍ő吔(�\�����E��)
#define SHADOW_MAX 10

//�R���X�^���g�o�b�t�@.
cbuffer per_mesh : register(b0)
{
	matrix g_mW;		//���[���h�s��.
	matrix g_mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����s��.
};
//�}�e���A���P��.
cbuffer per_material : register(b1)
{
	float4 g_vAmbient;	//�A���r�G���g�F(���F).
	float4 g_vDiffuse;	//�f�B�t���[�Y�F(�g�U���ːF).
	float4 g_vSpecular;	//�X�y�L�����F(���ʔ��ːF).
};
//�t���[���P��.
cbuffer per_frame	: register(b2)
{
	float4	g_vCamPos					: packoffset(c0);	//�J�������.
	float4	g_vLightDir					: packoffset(c1);	//���C�g����.
	float4	g_vCasterToLight			: packoffset(c2);	//�e�𗎂Ƃ����f���ƃ��C�g�����ԃx�N�g��.
	float4  g_vCasterPos[SHADOW_MAX]	: packoffset(c3);	//�e�𗎂Ƃ��L���X�^�[�ʒu.
};

//���_�V�F�[�_�̏o�̓p�����[�^.
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
//		���_(�o�[�e�b�N�X)�V�F�[�_.
//-------------------------------------------------------.
VS_OUTPUT VS_Main(float4 Pos : POSITION,
				  float4 Norm: NORMAL,
				  float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//�@�������[���h��Ԃ�.
	Norm.w = 0;	//w=0�ňړ������𔽉f�����Ȃ�.
	output.Normal = mul(Norm, g_mW);
	output.Pos = mul(Pos, g_mWVP);
	//���C�g����.
	output.Light = g_vLightDir;
	//�����x�N�g��.
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
	
	//�e�N�X�`�����W��n��.
	output.Tex = Tex;

	return output;
}

//*******************************************************.
//	���X�^���C�U(�A�v�����Őݒ肷�鍀�ځB�����ł͐G��Ȃ�).
//*******************************************************.

//-------------------------------------------------------.
//	�s�N�Z���V�F�[�_.
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

//============�e�N�X�`������============================================.
//-------------------------------------------------------.
//		���_(�o�[�e�b�N�X)�V�F�[�_.
//-------------------------------------------------------.
VS_OUTPUT VS_NoTex(float4 Pos : POSITION,
				   float4 Norm : NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//�@�������[���h��Ԃ�.
	Norm.w = 0;	//w=0�ňړ������𔽉f�����Ȃ�.
	output.Normal = mul(Norm, g_mW);
	output.Pos = mul(Pos, g_mWVP);
	//���C�g����.
	output.Light = g_vLightDir;
	//�����x�N�g��.
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
//	�s�N�Z���V�F�[�_.
//-------------------------------------------------------.
float4 PS_NoTex(VS_OUTPUT input) : SV_Target
{
	float4 Color = input.Color;

	return Color;
}


//========================================================.
//	�ȍ~�A�|���S���p�R�[�h.
//========================================================.
//�R���X�^���g�o�b�t�@.
cbuffer Ita_Global : register(b2)	//���W�X�^�𐔕��ǉ�.
{
	matrix g_WVP;	//���[���h�C�r���[�C�v���W�F�N�V�����܂ł̕ϊ��s��.
	float4 g_Color;	//�F.
	float  g_Amvient;	//���ߐF.
	float4 g_UV;	//UV���W.
};

//�\����.
struct VS_ITAOUT
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD;
};

//���_�V�F�[�_.
VS_ITAOUT VS_Ita(float4 Pos : POSITION,
				 float2 Tex : TEXCOORD)
{
	VS_ITAOUT output = (VS_ITAOUT)0;
	output.Pos = mul(Pos, g_WVP);
	output.Tex = Tex;

	//�e�N�X�`����UV���W�𑀍삷��.
	output.Tex.x += g_UV.x;

	return output;
}

//�s�N�Z���V�F�[�_.
float4 PS_Ita(VS_ITAOUT input) : SV_Target
{
	float4 color = g_Texture.Sample(g_samLinear, input.Tex);
	color.a *= g_Amvient;

	return color;	//�F��Ԃ�.
}