#include "CDebugText.h"
#include <crtdbg.h>

//�V�F�[�_�t�@�C����.
const char SHADER_NAME[] = "Data\\Shader\\DebugText.hlsl";

//�R���X�g���N�^.
CDebugText::CDebugText()
	: m_pDevice11		(nullptr)
	, m_pContext11		(nullptr)
	, m_pVertexShader	(nullptr)
	, m_pVertexLayout	(nullptr)
	, m_pPixelShader	(nullptr)
	, m_pConstantBuffer	(nullptr)
	, m_pVertexBuffer	()
	, m_pSampleLinear	(nullptr)
	, m_pAsciiTexture	(nullptr)
	, m_pAlphaBlend		(nullptr)
	, m_pNoAlphaBlend	(nullptr)
	, m_fKerning		()
	, m_fAlpha			(0.0f)
	, m_fScale			(1.0f)
	, m_vColor			(0.0f, 0.0f, 0.0f, 0.0f)
	, m_vPos			()
{
}

//�f�X�g���N�^.
CDebugText::~CDebugText()
{
}

//�������֐�.
HRESULT CDebugText::Init(ID3D11DeviceContext* pContext11,
	DWORD Width, DWORD Height,
	float Scale, D3DXVECTOR4 vColor)
{
	m_fAlpha = vColor.w;
	m_vColor = vColor;
	m_fScale = Scale / 25.0f;

	//95�������J��Ԃ�.
	for (int i = 0; i < 95; i++) {
		m_fKerning[i] = 10.0f;
	}
	//�f�o�C�X�R���e�L�X�g���R�s�[.
	m_pContext11 = pContext11;
	//�f�o�C�X�R���e�L�X�g����f�o�C�X���擾.
	m_pContext11->GetDevice(&m_pDevice11);

	//Windows�T�C�Y.
	m_dwWindowHeight = Height;
	m_dwWindowWidth  = Width;

	//===�t�H���g���ɃN�A�b�h�i��`�j�쐬===.
	float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;
	int cnt = 0;
	//2�d���[�v��1�������w�肷��.
	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 10; i++) {
			left	= k * WDIMENSION;
			top		= i * DIMENSION;
			right	= left + m_fKerning[cnt];
			bottom	= top + DIMENSION;

			left	/= TEX_DIMENSION;
			top		/= TEX_DIMENSION;
			right	/= TEX_DIMENSION;
			bottom	/= TEX_DIMENSION;

			VERTEX vertices[] = 
			{
				D3DXVECTOR3(0.0f,       DIMENSION, 0.0f), D3DXVECTOR2(left, bottom),
				D3DXVECTOR3(0.0f, 		0.0f,	   0.0f), D3DXVECTOR2(left, top),
				D3DXVECTOR3(WDIMENSION, DIMENSION, 0.0f), D3DXVECTOR2(right, bottom),
				D3DXVECTOR3(WDIMENSION, 0.0f,      0.0f), D3DXVECTOR2(right, top),
			};

			//�ő�v�f�����Z�o����.
			UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

			//�o�b�t�@�\����.
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;				//�g�p���@(�f�t�H���g).
			bd.ByteWidth = sizeof(VERTEX) * uVerMax;	//���_�̃T�C�Y.
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���_�o�b�t�@�Ƃ��Ĉ���.
			bd.CPUAccessFlags = 0;						//CPU����̓A�N�Z�X���Ȃ�.
			bd.MiscFlags = 0;							//���̑��̃t���O(���g�p).
			bd.StructureByteStride = 0;					//�\���̂̃T�C�Y(���g�p).

			//�T�u���\�[�X�f�[�^�\����.
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;				//�|���̒��_���Z�b�g.

			//���_�o�b�t�@�̍쐬.
			if (FAILED(m_pDevice11->CreateBuffer(
				&bd, &InitData, &m_pVertexBuffer[cnt])))
			{
				_ASSERT_EXPR(false, L"���_�o�b�t�@�쐬���s");
				return E_FAIL;
			}
			cnt++;
		}
	}

	//�e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter	 = D3D11_FILTER_MIN_MAG_MIP_POINT;	//POINT:���������e��.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//���b�s���O���[�h(WRAP:�J��Ԃ�).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//�T���v���쐬.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)�T���v��.
	{
		_ASSERT_EXPR(false, L"�T���v���쐬���s");
		return E_FAIL;
	}

	//�e�N�X�`���쐬.
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,									//���\�[�X���g�p����f�o�C�X�̃|�C���^.
		"Data\\Texture\\DebugText\\ascii.png",			//�t�@�C����.
		nullptr, nullptr,
		&m_pAsciiTexture,								//(out)�e�N�X�`��.
		nullptr)))
	{
		_ASSERT_EXPR(false, L"�e�N�X�`���쐬���s");
		return E_FAIL;
	}

	//�V�F�[�_�쐬.
	if (FAILED(InitShader())) {
		return E_FAIL;
	}
	//�u�����h�X�e�[�g�쐬.
	if (FAILED(InitBlend())) {
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================.
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL : High Level Shading Language �̗�.
//==================================================================.
HRESULT CDebugText::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSL����o�[�e�b�N�X�V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			"VS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.				//""�̓v���p�e�B�̐ݒ荀�ڂƈꏏ.
			"vs_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,		//�V�F�[�_�R���p�C���t���O.
			0,					//�G�t�F�N�g�R���p�C���t���O(���g�p).
			nullptr,			//�X���b�h�|���v�C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			&pCompiledShader,	//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,			//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr)))			//�߂�l�ւ̃|�C���^(���g�p).
	{
		_ASSERT_EXPR(false, L"hlsl�ǂݍ��ݎ��s");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬�����u���u����u�o�[�e�b�N�X�V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader)))	//(out)�o�[�e�b�N�X�V�F�[�_.
	{
		_ASSERT_EXPR(false, L"�o�[�e�b�N�X�V�F�[�_�쐬���s");
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI�̃t�H�[�}�b�g(32bit float�^*3).
			0,
			0,								//�f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//�e�N�X�`���ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGI�̃t�H�[�}�b�g(32bit float�^*2).
			0,
			12,								//�f�[�^�̊J�n�ʒu����̃f�[�^��4�o�C�g��3���邩��12���̊J�n�ʒu�͊ԈႦ�Ă͂����Ȃ�.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}

	};
	//���_�C���v�b�g���C�A�E�g�̔z��v�f�����Z�o.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))	//(out)���_�C���v�b�g���C�A�E�g.
	{
		_ASSERT_EXPR(false, L"���_�C���v�b�g���C�A�E�g�쐬���s");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//HLSL����s�N�Z���V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			"PS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"ps_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,		//�V�F�[�_�R���p�C���t���O.
			0,					//�G�t�F�N�g�R���p�C���t���O(���g�p).
			nullptr,			//�X���b�h�|���v�C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			&pCompiledShader,	//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,			//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			nullptr)))			//�߂�l�ւ̃|�C���^(���g�p).
	{
		_ASSERT_EXPR(false, L"hlsl�ǂݍ��ݎ��s");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬�����u���u����u�s�N�Z���V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader)))	//(out)�s�N�Z���V�F�[�_.
	{
		_ASSERT_EXPR(false, L"�s�N�Z���V�F�[�_�쐬���s");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//�R���X�^���g(�萔)�o�b�t�@�쐬.
	//�V�F�[�_�ɓ���̐��l�𑗂�o�b�t�@.
	//�����ł͕ϊ��s��n���p.
	//�V�F�[�_�� World, View, Projection �s���n��.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);	//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;						//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			&m_pConstantBuffer)))
	{
		_ASSERT_EXPR(false, L"�R���X�^���g�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CDebugText::InitBlend()
{
	//��̧�����ޗp�����޽ðč\����.
	//pnģ�ٓ��ɱ�̧��񂪂���̂ŁA���߂���悤�������޽ðĂŐݒ肷��.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));	//������.

	BlendDesc.IndependentBlendEnable
		= false;
	BlendDesc.AlphaToCoverageEnable
		= false;									//true:��̧ĩ���ڰ�ނ��g�p����.
	BlendDesc.RenderTarget[0].BlendEnable
		= true;										//true:��̧�����ނ��g�p����.
	BlendDesc.RenderTarget[0].SrcBlend				//���f�ނɑ΂���ݒ�.
		= D3D11_BLEND_SRC_ALPHA;					//��̧�����ނ��w��.
	BlendDesc.RenderTarget[0].DestBlend				//�d�˂�f�ނɑ΂���ݒ�.
		= D3D11_BLEND_INV_SRC_ALPHA;				//��̧�����ނ̔��]���w��.
	BlendDesc.RenderTarget[0].BlendOp				//�����޵�߼��.
		= D3D11_BLEND_OP_ADD;						//ADD:���Z����.
	BlendDesc.RenderTarget[0].SrcBlendAlpha			//���f�ނ̱�̧�ɑ΂���w��.
		= D3D11_BLEND_ONE;							//���̂܂܎g�p.
	BlendDesc.RenderTarget[0].DestBlendAlpha		//�d�˂�f�ނ̱�̧�ɑ΂���ݒ�.
		= D3D11_BLEND_ZERO;							//�������Ȃ��B
	BlendDesc.RenderTarget[0].BlendOpAlpha			//��̧�������޵�߼��.
		= D3D11_BLEND_OP_ADD;						//ADD:���Z����.
	BlendDesc.RenderTarget[0].RenderTargetWriteMask	//�߸�ٖ��̏�������Ͻ�.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//�S�Ă̐���(RGBA)�ւ��ް��̊i�[��������.

	//�����޽ðč쐬.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"�����޽ðč쐬���s");
		return E_FAIL;
	}

	//�����޽ðč쐬.
	BlendDesc.RenderTarget[0].BlendEnable
		= false;		//true:��̧�����ނ��g�p���Ȃ�.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pNoAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"�����޽ðč쐬���s");
		return E_FAIL;
	}

	return S_OK;
}

//���ߐݒ�̐؂�ւ�.
void CDebugText::SetBlend(bool EnableAlpha)
{
	//�����޽ðĂ̐ݒ�.
	UINT mask = 0xffffffff;	//Ͻ��l.
	if (EnableAlpha == true) {
		m_pContext11->OMSetBlendState(
			m_pAlphaBlend, nullptr, mask);
	}
	else {
		m_pContext11->OMSetBlendState(
			m_pNoAlphaBlend, nullptr, mask);
	}
}

//�����_�����O�֐�.
void CDebugText::Render(const char* text, int x, int y)
{
	//�r���[�g�����X�t�H�[��.
	D3DXVECTOR3 vEye (0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 vLook(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp	 (0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(
		&m_mView, &vEye, &vLook, &vUp);

#if 0
	//�v���W�F�N�V�����g�����X�t�H�[��(�Œ�).
	D3DMATRIX mOtho = {
		2.0f / static_cast<float>(m_dwWindowWidth), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / static_cast<float>(m_dwWindowHeight), 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	};
#else
	D3DXMATRIX mOtho;
	D3DXMatrixIdentity(&mOtho);		//�P�ʍs��쐬.
	mOtho._11 =  2.0f / static_cast<float>(m_dwWindowWidth);
	mOtho._22 = -2.0f / static_cast<float>(m_dwWindowHeight);
	mOtho._41 = -1.0f;
	mOtho._42 =  1.0f;
#endif
	m_mProj = mOtho;

	//�v���~�e�B�u�E�g�|���W�[.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout(m_pVertexLayout);

	//�g�p����V�F�[�_�̓o�^.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//�R���X�^���g�o�b�t�@��o�^.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//�T���v���ƃe�N�X�`�����s�N�Z���V�F�[�_�ɓn��.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pAsciiTexture);

	//�����������[�v.
	for (int i = 0; i < static_cast<int>(strlen(text)); i++) 
	{
		char font = text[i];
		int index = font - 32;	//�t�H���g�C���f�b�N�X�쐬.

		//�t�H���g�����_�����O.
		RenderFont(index, x, y);
		x += static_cast<int>(m_fKerning[index]);
	}
}

//�t�H���g�����_�����O�֐�.
void CDebugText::RenderFont(int FontIndex, int x, int y)
{
	//���[���h�ϊ�.
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mWorld, static_cast<FLOAT>(x), static_cast<FLOAT>(y), -100.0f);

	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//�R���X�^���g�o�b�t�@.

	//�o�b�t�@���̃f�[�^�̏��������J�n����map.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�C�r���[�C�v���W�F�N�V�����s���n��.
		D3DXMATRIX m = mWorld * m_mView * m_mProj;
		D3DXMatrixTranspose(&m, &m);			//�s���]�u����.
		cb.mWVP = m;

		//�J���[.
		cb.vColor = m_vColor;

		//���ߒl.
		cb.fAlpha.x = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer[FontIndex], &stride, &offset);

	SetBlend(true);
	//�`��.
	m_pContext11->Draw(4, 0);

	SetBlend(false);

}