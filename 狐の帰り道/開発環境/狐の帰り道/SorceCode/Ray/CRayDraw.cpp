#include "CRayDraw.h"

//�V�F�[�_�[�t�@�C����(�f�B���N�g�����܂�).
const char SHADER_NAME[] = "Data\\Shader\\Ray.hlsl";

CRayDraw::CRayDraw()
	: m_pVertexShader(nullptr)	
	, m_pVertexLayout(nullptr)	
	, m_pPixelShader(nullptr)	
	, m_pConstantBuffer(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_Ray()
{
}

CRayDraw::~CRayDraw()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}

//������.
HRESULT CRayDraw::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================.
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL : High Level Shading Language �̗�.
//==================================================================.
HRESULT CRayDraw::InitShader()
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


//���C������.
HRESULT CRayDraw::InitModel()
{
	//���C�̃o�[�e�b�N�o�b�t�@�쐬.
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX)*2;	//2�_��.
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_Ray.Point;	//���C�̍��W���Z�b�g.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer)))
	{
		_ASSERT_EXPR(false, "�o�[�e�b�N�X�o�b�t�@�쐬���s");
		return E_FAIL;
	}
	return S_OK;
}

//�`��.
void CRayDraw::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj)
{
	//���[���h�s��.
	D3DXMATRIX mWorld;
	//��]�s��,�@�ړ��s��.
	D3DXMATRIX mRot, mTran;

	//��]�s��.
	D3DXMatrixRotationY(&mRot, m_Ray.fYaw);

	//���s�ړ�.
	D3DXMatrixTranslation(&mTran, m_Ray.Pos.x, m_Ray.Pos.y, m_Ray.Pos.z);

	//�g�p����V�F�[�_�̓o�^.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//���[���h�s��.
	mWorld = mRot * mTran;

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

		//�J���[.
		cb.vColor = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�����H.
	//registar��b2��2�ƘA�����Ă���.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX);	//�f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout(m_pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	//�v���~�e�B�u�������_�����O.
	m_pContext11->Draw(2, 0);	//����(���_2��).
}
