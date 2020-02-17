#include "CParticle.h"
#include <crtdbg.h>

//�V�F�[�_�l�[��.
const char SHADER_NAME[] = "Data\\Shader\\Particle.hlsl";

CParticle::CParticle()
	: m_pVertexShader(nullptr)
	, m_pVertexLayout(nullptr)
	, m_GeometryShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pConstantBuffer(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pSampleLinear(nullptr)
	, m_pTexture(nullptr)
	, m_AnimCount(0)
	, m_UV(0.0f, 0.0f)
	, m_vPos()
	, m_Scale(1.0f)
	, m_pParticleArray(nullptr)
	, m_Frame(0)
	, m_vRot(0.0f, 0.0f, 0.0f)
{
}

//�f�X�g���N�^.
CParticle::~CParticle()
{
	Release();
}

//������.
HRESULT CParticle::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContex11;

	//�u�����h�X�e�[�g.
	if (FAILED(InitBlend()))
	{
		return E_FAIL;
	}

	//�V�F�[�_�쐬.
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	//�|���S���쐬.
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}
	//�e�N�X�`���쐬
	if(FAILED(InitTexture(fileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//���.
void CParticle::Release()
{
	//�e���v���[�g�N���X�Ƃ������̂�����.
	//�����g����悤�ɂȂ�ƕ֗�.
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pNoAlphaBlend);

	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;

	SAFE_DELETE_ARRAY(m_pParticleArray);
}

//==================================================================.
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL : High Level Shading Language �̗�.
//==================================================================.
HRESULT CParticle::InitShader()
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
//		{
//			"TEXCOORD",						//�e�N�X�`���ʒu.
//			0,
//			DXGI_FORMAT_R32G32_FLOAT,		//DXGI�̃t�H�[�}�b�g(32bit float�^*2).
//			0,
//			12,								//�f�[�^�̊J�n�ʒu����̃f�[�^��4�o�C�g��3���邩��12���̊J�n�ʒu�͊ԈႦ�Ă͂����Ȃ�.
//			D3D11_INPUT_PER_VERTEX_DATA, 0
//		}

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

	//HLSL����W�I���g���V�F�[�_�̃u���u���쐬.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
			"GS_Point",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"gs_5_0",			//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
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

	//��L�ō쐬�����u���u����u�W�I���g���V�F�[�_�v���쐬.
	if (FAILED(
		m_pDevice11->CreateGeometryShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_GeometryShader)))	//(out)�W�I���g���V�F�[�_.
	{
		_ASSERT_EXPR(false, L"�W�I���g���V�F�[�_�쐬���s");
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
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;								//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;				//�g�p���@�F���ڏ�������.

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


//���f���쐬.
HRESULT CParticle::InitModel()
{
	//���_���쐬.
	VERTEX vertices[] =
	{
		//���_���W(x,y,z).
		D3DXVECTOR3(-0.5f, 0.5f, 0.0f),
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�o�b�t�@�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;		//�g�p���@(�f�t�H���g).
	bd.ByteWidth			= sizeof(VERTEX) * uVerMax;	//���_�̃T�C�Y.
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	//���_�o�b�t�@�Ƃ��Ĉ���.
	bd.CPUAccessFlags		= 0;						//CPU����̓A�N�Z�X���Ȃ�.
	bd.MiscFlags			= 0;						//���̑��̃t���O(���g�p).
	bd.StructureByteStride	= 0;						//�\���̂̃T�C�Y(���g�p).

	//�T�u���\�[�X�f�[�^�\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem		= vertices;					//�|���̒��_���Z�b�g.

	//���_�o�b�t�@�̍쐬.
	if (FAILED(m_pDevice11->CreateBuffer(
		&bd, &InitData, &m_pVertexBuffer)))
	{
		_ASSERT_EXPR(false, L"���_�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		&m_pVertexBuffer, &stride, &offset);


	return S_OK;
}

//�e�N�X�`���ǂݍ��݁��쐬.
HRESULT CParticle::InitTexture(const char* fileName)
{
	//�e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	//���j�A�t�B���^(���`���).
							//POINT:���������e��.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//���b�s���O���[�h(WRAP:�J��Ԃ�).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
					//MIRROR: ���]�J��Ԃ�.
					//CLAMP : �[�̖͗l�������L�΂�.
					//BORDER: �ʓr���E�F�����߂�.
	//�T���v���쐬.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)�T���v��.
	{
		_ASSERT_EXPR(false, L"�T���v���쐬���s");
		return E_FAIL;
	}

	//�e�N�X�`���쐬.
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,		//���\�[�X���g�p����f�o�C�X�̃|�C���^.
		fileName,			//�t�@�C����.
		nullptr, nullptr,
		&m_pTexture,		//(out)�e�N�X�`��.
		nullptr)))
	{
		_ASSERT_EXPR(false, L"�e�N�X�`���쐬���s");
		return E_FAIL;
	}


	return S_OK;
}

//�����_�����O�p.
void CParticle::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCamPos)
{
	//���[���h�s��.
	D3DXMATRIX mWorld, mScale, mRot, mTrans;
	D3DXMATRIX mYaw, mPitch, mRoll;

	//�g��E�k��.
	D3DXMatrixScaling(&mScale,
		m_Scale, m_Scale, m_Scale);

	//Y����]�s��쐬.
	D3DXMatrixRotationY(&mYaw, m_vRot.y);
	//X����]�s��쐬.
	D3DXMatrixRotationX(&mPitch, m_vRot.x);
	//Z����]�s��쐬.
	D3DXMatrixRotationZ(&mRoll, m_vRot.z);

	//���s�ړ�.
	D3DXMatrixTranslation(&mTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	//��]�s����쐬.
	mRot = mYaw * mPitch * mRoll;

	//���[���h�s��.
	mWorld = mScale * mRot * mTrans;

	//�g�p����V�F�[�_�̓o�^.
	//�g���V�F�[�_�����ꂼ��.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->GSSetShader(m_GeometryShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//�R���X�^���g�o�b�t�@.
	//�o�b�t�@���̃f�[�^�̏��������J�n����map.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�C�r���[�C�v���W�F�N�V�����s���n��.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose(&m, &m);			//�s���]�u����.
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�����H.
	//registar��b2��2�ƘA�����Ă���.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout(m_pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//�e�N�X�`���[���V�F�[�_�ɓn��.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pTexture);

	//�A���t�@�u�����h�L���ɂ���.
	SetBlend(true);

	//�v���~�e�B�u�������_�����O.
	//�o�b�N�o�b�t�@�ɃZ�b�g�����.
	m_pContext11->Draw(1, 0);	//�|�C���g�X�v���C�g�Ȃ̂Œ��_��1��.
								//�c��̒��_�̓V�F�[�_�ŕ\������.

	//�W�I���g���V�F�[�_�𖳌��ɂ���.
	m_pContext11->GSSetShader(nullptr, nullptr, 0);

	//�A���t�@�u�����h�����ɂ���.
	SetBlend(false);
}



//�V�F�[�_���O���֐�.
void CParticle::DetachShader() 
{
	//�e�V�F�[�_���f�^�b�`����.

	m_pContext11->VSSetShader(nullptr, nullptr, 0);	//���_�V�F�[�_.
	m_pContext11->HSSetShader(nullptr, nullptr, 0);	//�n���V�F�[�_.

	//�`�`�`�`�`�e�b�Z���[�^�`�`�`�`�`�`�i�㉺�̊ԏ����j.

	m_pContext11->DSSetShader(nullptr, nullptr, 0);	//�h���C���V�F�[�_.
	m_pContext11->GSSetShader(nullptr, nullptr, 0);	//�W�I���g���V�F�[�_.

	//�`�`�`�`�`�`�`���X�^���C�U�`�`�`�`�`(�㉺�̊ԏ���).

	m_pContext11->PSSetShader(nullptr, nullptr, 0);	//�s�N�Z���V�F�[�_.
}

