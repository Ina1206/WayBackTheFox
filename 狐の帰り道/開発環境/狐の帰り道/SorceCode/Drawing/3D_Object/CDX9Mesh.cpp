#include "CDX9Mesh.h"
#include <crtdbg.h>	//_ASSERT�}�N���ŕK�v.

const char SHADER_NAME[] = "Data\\Shader\\Mesh.hlsl";

//�R���X�g���N�^.
CDX9Mesh::CDX9Mesh()
	: m_hWnd				(nullptr)
	, m_pD3d9				(nullptr)
	, m_pDevice9			(nullptr)
	, m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pVertexShader		(nullptr)
	, m_pVertexLayout		(nullptr)
	, m_pPixelShader		(nullptr)
	, m_pCBufferPerMesh		(nullptr)
	, m_pCBufferPerMaterial	(nullptr)
	, m_pCBufferPerFrame	(nullptr)
	, m_pVertexBuffer		(nullptr)
	, m_ppIndexBuffer		(nullptr)
	, m_pSampleLinear		(nullptr)
	, m_pMesh				(nullptr)
	, m_NumMaterials		(0)
	, m_pMaterials			(nullptr)
	, m_NumAttr				(0)
	, m_AttrID				()
	, m_EnableTexture		(false)
	, m_Sphere				()
	, m_BBox				()
	, m_pMeshForRay			(nullptr)
	, m_fScale				(1.0f)
	, m_vRot				(0.0f, 0.0f, 0.0f)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_vPrePos				(0.0f, 0.0f, 0.0f)
	, m_pstShadow			(nullptr)
{

}

//�f�X�g���N�^.
CDX9Mesh::~CDX9Mesh()
{
	//�������.
	Release();
}

HRESULT CDX9Mesh::Init(
	HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11, const char* fileName)
{
	m_hWnd			= hWnd;
	m_pDevice9		= pDevice9;
	m_pDevice11		= pDevice11;
	m_pContext11	= pContext11;

	if (FAILED(LoadXMesh(fileName))) {
		return E_FAIL;
	}
	if (FAILED(InitShader())) {
		return S_OK;
	}

	return S_OK;
}

//���b�V���ǂݍ���.
HRESULT CDX9Mesh::LoadXMesh(const char* fileName)
{
	//�}�e���A���o�b�t�@.
	LPD3DXBUFFER pD3DXMtrlBuffer = nullptr;

	//X�t�@�C���̃��[�h.
	if (FAILED(D3DXLoadMeshFromX(
		fileName,				//�t�@�C����.
		D3DXMESH_SYSTEMMEM		//�V�X�e���������ɓǂݍ���.
			| D3DXMESH_32BIT,	//32bit.
		m_pDevice9, nullptr,
		&pD3DXMtrlBuffer,		//(out)�}�e���A�����.
		nullptr,
		&m_NumMaterials,		//(out)�}�e���A����.
		&m_pMesh)))				//(out)���b�V���I�u�W�F�N�g.
	{
		//�Ȃ�̃t�@�C�����ǂݍ��߂Ȃ��̂��H�𑫂�.
		_ASSERT_EXPR(false, L"X�t�@�C���ǂݍ��ݎ��s");
		return E_FAIL;
	}

	//X�t�@�C���̃��[�h(���C�Ɣ���p�ɕʐݒ�œǂݍ���).
	if (FAILED(D3DXLoadMeshFromX(
		fileName,				//�t�@�C����.
		D3DXMESH_SYSTEMMEM,		//�V�X�e���������ɓǂݍ���.
		m_pDevice9, nullptr,
		&pD3DXMtrlBuffer,		//(out)�}�e���A�����.
		nullptr,
		&m_NumMaterials,		//(out)�}�e���A����.
		&m_pMeshForRay)))		//(out)���b�V���I�u�W�F�N�g.
	{
		_ASSERT_EXPR(false, L"X�t�@�C���ǂݍ��ݎ��s");
		return E_FAIL;
	}


	D3D11_BUFFER_DESC		bd;			//Dx11�o�b�t�@�\����.
	D3D11_SUBRESOURCE_DATA	InitData;	//�������f�[�^.
	//�ǂݍ��񂾏�񂩂�K�v�ȏ��𔲂��o��.
	D3DXMATERIAL* d3dxMaterials
		= static_cast<D3DXMATERIAL*>(pD3DXMtrlBuffer->GetBufferPointer());
	//�}�e���A�������̗̈���m��.
	m_pMaterials = new MY_MATERIAL[m_NumMaterials]();
	//�|�C���^�𕡐���邽��*�����Ă�.
	m_ppIndexBuffer = new ID3D11Buffer*[m_NumMaterials]();
	//�}�e���A�������J��Ԃ�.
	for (DWORD No = 0; No < m_NumMaterials; No++) 
	{
		//�C���f�b�N�X�o�b�t�@�̏�����.
		m_ppIndexBuffer[No] = nullptr;

		//�}�e���A�����̃R�s�[.
		//�A���r�G���g.
		m_pMaterials[No].Ambient.x = d3dxMaterials[No].MatD3D.Ambient.r;
		m_pMaterials[No].Ambient.y = d3dxMaterials[No].MatD3D.Ambient.g;
		m_pMaterials[No].Ambient.z = d3dxMaterials[No].MatD3D.Ambient.b;
		m_pMaterials[No].Ambient.w = d3dxMaterials[No].MatD3D.Ambient.a;
		//�f�B�t���[�Y.
		m_pMaterials[No].Diffuse.x = d3dxMaterials[No].MatD3D.Diffuse.r;
		m_pMaterials[No].Diffuse.y = d3dxMaterials[No].MatD3D.Diffuse.g;
		m_pMaterials[No].Diffuse.z = d3dxMaterials[No].MatD3D.Diffuse.b;
		m_pMaterials[No].Diffuse.w = d3dxMaterials[No].MatD3D.Diffuse.a;
		//�X�y�L����.
		m_pMaterials[No].Specular.x = d3dxMaterials[No].MatD3D.Specular.r;
		m_pMaterials[No].Specular.y = d3dxMaterials[No].MatD3D.Specular.g;
		m_pMaterials[No].Specular.z = d3dxMaterials[No].MatD3D.Specular.b;
		m_pMaterials[No].Specular.w = d3dxMaterials[No].MatD3D.Specular.a;

		//�i���̖ʂɁj�e�N�X�`�����\���Ă��邩�H.
		if (d3dxMaterials[No].pTextureFilename != nullptr
			&& lstrlen(d3dxMaterials[No].pTextureFilename) > 0)
		{
			//�e�N�X�`������̃t���O�𗧂Ă�.
			m_EnableTexture = true;

			char path[128] = "";
			int path_count = lstrlen(fileName);
			for (int k = path_count; k >= 0; k--) {
				if (fileName[k] == '\\') {
					for (int j = 0; j <= k; j++) {
						path[j] = fileName[j];
					}
					path[k + 1] = '\0';
					break;
				}
			}
			//�p�X�ƃe�N�X�`���t�@�C������A��.
			strcat_s(path, sizeof(path), d3dxMaterials[No].pTextureFilename);

			//�e�N�X�`���t�@�C�������R�s�[.
			strcpy_s(m_pMaterials[No].szTextureName,
				sizeof(m_pMaterials[No].szTextureName), path);

			//�e�N�X�`���쐬.
			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(
				m_pDevice11, m_pMaterials[No].szTextureName,	//�e�N�X�`���t�@�C����.
				nullptr, nullptr,
				&m_pMaterials[No].pTexture,						//(out)�e�N�X�`���I�u�W�F�N�g.
				nullptr)))
			{
				_ASSERT_EXPR(false, L"�e�N�X�`���쐬���s");
				return E_FAIL;
			}
			
		}	
	}

	//-------------------------------------------------------.
	//		�C���f�b�N�X�o�b�t�@�쐬.
	//-------------------------------------------------------.
	//���b�V���̑������𓾂�.
	D3DXATTRIBUTERANGE* pAttrTable = nullptr;

	//���b�V���̖ʂ���ђ��_�̏��ԕύX�𐧌䂵�A�p�t�H�[�}���X���œK������.
	//D3DXMESHOPT_COMPACT : �ʂ̏��Ԃ�ύX���A�g�p����Ă��Ȃ����_�Ɩʂ��폜����.
	//D3DXMESHOPT_ATTRSORT: �p�t�H�[�}���X���グ��ׁA�ʂ̏��Ԃ�ύX���čœK�����s��.
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
		nullptr, nullptr, nullptr, nullptr);
	//�����e�[�u���̎擾.
	m_pMesh->GetAttributeTable(nullptr, &m_NumAttr);
	pAttrTable = new D3DXATTRIBUTERANGE[m_NumAttr];
	if (FAILED(m_pMesh->GetAttributeTable(pAttrTable, &m_NumAttr)))
	{
		_ASSERT_EXPR(false, L"�����e�[�u���擾���s");
		return E_FAIL;
	}

	//������Lock���Ȃ��Ǝ��o���Ȃ�.
	int* pIndex = nullptr;
	m_pMesh->LockIndexBuffer(
		D3DLOCK_READONLY, (void**)&pIndex);
	//�������Ƃ̃C���f�b�N�X�o�b�t�@���쐬.
	for (DWORD No = 0; No < m_NumAttr; No++)
	{
		m_AttrID[No] = pAttrTable[No].AttribId;
		//Dx9�̃C���f�b�N�X�o�b�t�@����̏��ŁADx11�̃C���f�b�N�X�o�b�t�@���쐬.
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int)*pAttrTable[No].FaceCount * 3;	//�ʐ��~�R�Œ��_��.
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		//�傫���C���f�b�N�X�o�b�t�@���̃I�t�Z�b�g(�~3����).
		InitData.pSysMem = &pIndex[pAttrTable[No].FaceStart*3];

		if (FAILED(m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_ppIndexBuffer[No])))
		{
			_ASSERT_EXPR(false, L"�C���f�b�N�X�o�b�t�@�쐬���s");
			return E_FAIL;
		}
		//�ʂ̐����R�s�[.
		m_pMaterials[m_AttrID[No]].dwNumFace = pAttrTable[No].FaceCount;
	}
	//�����e�[�u���̍폜.
	delete[] pAttrTable;
	//�g�p�ς݂̃C���f�b�N�X�o�b�t�@�̉��.
	m_pMesh->UnlockIndexBuffer();
	//�s�v�ɂȂ����}�e���A���o�b�t�@�����.
	SAFE_RELEASE(pD3DXMtrlBuffer);

	//-------------------------------------------------------.
	//	���_�o�b�t�@�̍쐬.
	//-------------------------------------------------------.
	//Dx9�̏ꍇ�Amap�ł͂Ȃ�Lock�Œ��_�o�b�t�@����f�[�^�����o��.
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	m_pMesh->GetVertexBuffer(&pVB);
	DWORD dwStride = m_pMesh->GetNumBytesPerVertex();
	BYTE*   pVertices = nullptr;
	VERTEX* pVertex = nullptr;
	if (SUCCEEDED(
		pVB->Lock(0, 0, (VOID**)&pVertices, 0)))
	{
		pVertex = (VERTEX*)pVertices;
		//Dx9�̒��_�o�b�t�@����̏��ŁADx11���_�o�b�t�@���쐬.
		bd.Usage = D3D11_USAGE_DEFAULT;
		//���_���i�[����̂ɕK�v�ȃo�C�g��.
		bd.ByteWidth = m_pMesh->GetNumBytesPerVertex()*m_pMesh->GetNumVertices();
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		InitData.pSysMem = pVertex;
		if (FAILED(m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer)))
		{
			_ASSERT_EXPR(false, L"���_�o�b�t�@�쐬���s");
			return E_FAIL;
		}
		pVB->Unlock();
	}
	SAFE_RELEASE(pVB);	//���_�o�b�t�@���.



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


	return S_OK;
}

//����֐�.
void CDX9Mesh::Release()
{
	//�C���f�b�N�X�o�b�t�@���.	
	if (m_ppIndexBuffer != nullptr) {
		for (int No = m_NumMaterials - 1; No >= 0; No--) {
			if (m_ppIndexBuffer[No] != nullptr) {
				SAFE_RELEASE(m_ppIndexBuffer[No]);
			}
		}
		delete[] m_ppIndexBuffer;
		m_ppIndexBuffer = nullptr;
	}

	//�}�e���A�����.
	//�������ꂪ���񂩎g���Ă������� SAFE_RELEASE_ARY�̃}�N�������.
	if (m_pMaterials != nullptr) {
		//delete�̃^�C�~���O�Œ��g�̃|�C���^���}�N���Ŏ����ŏ����Ă����.
		delete[] m_pMaterials;
		m_pMaterials = nullptr;
	}

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pCBufferPerMaterial);
	SAFE_RELEASE(m_pCBufferPerMesh);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	SAFE_RELEASE(m_pDevice9);
	SAFE_RELEASE(m_pD3d9);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
	m_hWnd = nullptr;
}

//==================================================================.
//	HLSL�t�@�C����ǂݍ��݃V�F�[�_���쐬����.
//	HLSL : High Level Shading Language �̗�.
//==================================================================.
HRESULT CDX9Mesh::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSL����o�[�e�b�N�X�V�F�[�_�̃u���u���쐬.
	if (m_EnableTexture == true){
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
	}
	else {
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
				nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
				nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
				"VS_NoTex",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.				//""�̓v���p�e�B�̐ݒ荀�ڂƈꏏ.
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
	D3D11_INPUT_ELEMENT_DESC layout[3];

	//���_�C���v�b�g���C�A�E�g�̔z��v�f�����Z�o.
	UINT numElements = 0;
	if (m_EnableTexture == true) {
		D3D11_INPUT_ELEMENT_DESC tmp[] =
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
				"NORMAL",						//�@��.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI�̃t�H�[�}�b�g(32bit float�^*3).
				0,
				12,								//�f�[�^�̊J�n�ʒu.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"TEXCOORD",						//�e�N�X�`���ʒu.
				0,
				DXGI_FORMAT_R32G32_FLOAT,		//DXGI�̃t�H�[�}�b�g(32bit float�^*2).
				0,
				24,								//�f�[�^�̊J�n�ʒu����̃f�[�^��4�o�C�g��3���邩��12���̊J�n�ʒu�͊ԈႦ�Ă͂����Ȃ�.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
			
		};
		numElements = sizeof(tmp) / sizeof(tmp[0]);	//�v�f���Z�o.
		memcpy_s(layout, sizeof(layout), tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}
	else
	{
		D3D11_INPUT_ELEMENT_DESC tmp[] =
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
				"NORMAL",						//�@��.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI�̃t�H�[�}�b�g(32bit float�^*3).
				0,
				12,								//�f�[�^�̊J�n�ʒu.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
		};
		numElements = sizeof(tmp) / sizeof(tmp[0]);	//�v�f���Z�o.
		memcpy_s(layout, sizeof(layout), tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}

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
	if (m_EnableTexture == true) {
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
	}
	else {
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
				nullptr,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
				nullptr,			//�C���N���[�h�t�@�C���������C���^�[�t�F�C�X�ւ̃|�C���^(���g�p).
				"PS_NoTex",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
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
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(CBUFFER_PER_MESH);		//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;						//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb,nullptr,&m_pCBufferPerMesh)))
	{
		_ASSERT_EXPR(false, L"�R���X�^���g�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@ �}�e���A���p.
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(CBUFFER_PRE_MATERIAL);	//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;						//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb,nullptr,&m_pCBufferPerMaterial)))
	{
		_ASSERT_EXPR(false, L"�R���X�^���g�o�b�t�@�쐬���s");
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@ �t���[���p.
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�R���X�^���g�o�b�t�@���w��.
	cb.ByteWidth = sizeof(CBUFFER_PER_FRAME);		//�R���X�^���g�o�b�t�@�̃T�C�Y.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ŃA�N�Z�X.
	cb.MiscFlags = 0;								//���̑��̃t���O(���g�p).
	cb.StructureByteStride = 0;						//�\���̂̃T�C�Y().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//�g�p���@�F���ڏ�������.

	//�R���X�^���g�o�b�t�@�̍쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb, nullptr, &m_pCBufferPerFrame)))
	{
		_ASSERT_EXPR(false, L"�R���X�^���g�o�b�t�@�쐬���s");
		return E_FAIL;
	}


	return S_OK;
}

//�����_�����O�p.
void CDX9Mesh::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos)
{
	D3DXMATRIX PreTran;
	//���[���h�s��A�X�P�[���s��A��]�s��A���s�ړ��s��.
	D3DXMATRIX mWorld, mScale, mRot, mTran;
	D3DXMATRIX mYaw, mPitch, mRoll;


	//�g��k���s��쐬.
	D3DXMatrixScaling(
		&mScale,						//(out)�v�Z����.
		m_fScale, m_fScale, m_fScale);	//x,y,z���ꂼ��̊g�k�l.
	//Y����]�s��쐬.
	D3DXMatrixRotationY(&mYaw,m_vRot.y);
	//X����]�s��쐬.
	D3DXMatrixRotationX(&mPitch,m_vRot.x);
	//Z����]�s��쐬.
	D3DXMatrixRotationZ(&mRoll,m_vRot.z);
	//���s�ړ��s��쐬.
	D3DXMatrixTranslation(
		&mTran,							//(out)�v�Z����.
		m_vPos.x, m_vPos.y, m_vPos.z);	//x,y,z���W.

	D3DXMatrixTranslation(
		&PreTran,							//(out)�v�Z����.
		m_vPrePos.x, m_vPrePos.y, m_vPrePos.z);	//x,y,z���W.

	//��]�s����쐬.
	mRot = mYaw * mPitch * mRoll;

	//D3DXMatrixTranslation��x,y,z�Ő��E�̈ʒu�ɒu�����Ƃ��ł���.
	//���[���h�s��쐬.
	mWorld = PreTran * mScale * mRot * mTran;

	//�g�p����V�F�[�_�̃Z�b�g.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);		//���_�V�F�[�_.
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);		//�s�N�Z���V�F�[�_.

	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	//�o�b�t�@���̃f�[�^�̏��������J�n����Map.
	if (SUCCEEDED(m_pContext11->Map(
		m_pCBufferPerFrame, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &pData)))
	{
		CBUFFER_PER_FRAME cb;						//�R���X�^���g�o�b�t�@.

		//�J�����ʒu.
		cb.vCamPos = D3DXVECTOR4(vCamPos.x, vCamPos.y, vCamPos.z, 0.0f);
		cb.vLightDir = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);

		//���C�g�����̐��K��(�m�[�}���C�Y).
		D3DXVec4Normalize(&cb.vLightDir, &cb.vLightDir);

		//�e.
		cb.vCasterToLight = cb.vLightDir;
		for (int shadow = 0; shadow < SHADOW_MAX; shadow++) {
			cb.vCasterPos[shadow] = D3DXVECTOR4(0.0f, -100.0f, 0.0f, 0.0f);

			//�O���ݒ肳��Ă��鐔�̂ق������Ȃ��ꍇ�́A����ȍ~���X�L�b�v.
			if (shadow >= /*m_ShadowMax*/10) {
				continue;
			}

			//�e��񂪓����Ă���Ώ���.
			if (m_pstShadow != nullptr) {
				if (m_pstShadow[shadow].bDispFlag == true) {
					cb.vCasterPos[shadow] = static_cast<D3DXVECTOR4>(m_pstShadow[shadow].vCasterPos);
					//cb.vCasterPos[shadow] = D3DXVECTOR4(0.0f, 0.8f, 4.0f + (shadow * 0.1f), 1.0f);
					cb.vCasterPos[shadow].w = 1.0f;
				}
			}
		}

		memcpy_s(
			pData.pData,		//�R�s�[��̃o�b�t�@.
			pData.RowPitch,		//�R�s�[��̃o�b�t�@�T�C�Y.
			(void*)(&cb),		//�R�s�[���̃o�b�t�@.
			sizeof(cb));		//�R�s�[���̃T�C�Y.

		//�o�b�t�@���̃f�[�^�̏��������I������Unmap.
		m_pContext11->Unmap(m_pCBufferPerFrame, 0);
	}

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�p���邩�H.
	m_pContext11->VSSetConstantBuffers(
		2, 1, &m_pCBufferPerFrame);			//���_�V�F�[�_.
	m_pContext11->PSSetConstantBuffers(
		2, 1, &m_pCBufferPerFrame);			//�s�N�Z���V�F�[�_.

	//���b�V���̃����_�����O.
	RenderMesh(mWorld, mView, mProj);
}

//�����_�����O�֐�(�N���X���ł̂ݎg�p����).
void CDX9Mesh::RenderMesh(
	D3DXMATRIX& mWorld, D3DXMATRIX& mView, D3DXMATRIX& mProj)
{
	//�V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	//�o�b�t�@���̃f�[�^�̏��������J�n����Map.
	if (SUCCEEDED(m_pContext11->Map(
		m_pCBufferPerMesh, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &pData)))
	{
		CBUFFER_PER_MESH cb;						//�R���X�^���g�o�b�t�@.

		//���[���h�s���n��.
		cb.mW = mWorld;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);		//���[���h�ɒ��ڏ��������Ȃ��͉̂��ł��g������.

		//���[���h,�r���[,�v���W�F�N�V�����s���n��.
		D3DXMATRIX mWVP = mWorld * mView * mProj;
		D3DXMatrixTranspose(&mWVP, &mWVP);			//�s���]�u����.
		//���s��̌v�Z���@��DirectX��GPU�ɈقȂ邽�ߓ]�u���K�v.
		cb.mWVP = mWVP;

		memcpy_s(
			pData.pData,		//�R�s�[��̃o�b�t�@.
			pData.RowPitch,		//�R�s�[��̃o�b�t�@�T�C�Y.
			(void*)(&cb),		//�R�s�[���̃o�b�t�@.
			sizeof(cb));		//�R�s�[���̃T�C�Y.

		//�o�b�t�@���̃f�[�^�̏��������I������Unmap.
		m_pContext11->Unmap(m_pCBufferPerMesh, 0);
	}

	//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�p���邩�H.
	m_pContext11->VSSetConstantBuffers(
		0, 1, &m_pCBufferPerMesh);			//���_�V�F�[�_.
	m_pContext11->PSSetConstantBuffers(
		0, 1, &m_pCBufferPerMesh);			//�s�N�Z���V�F�[�_.

	//���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout(m_pVertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//���_�o�b�t�@���Z�b�g.
	UINT stride = m_pMesh->GetNumBytesPerVertex();
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset);

	//�����̐������A���ꂼ��̑����̃C���f�b�N�X�o�b�t�@��`��.
	for (DWORD No = 0; No < m_NumAttr; No++) {
		//�g�p����Ă��Ȃ��}�e���A���΍�.
		if (m_pMaterials[m_AttrID[No]].dwNumFace == 0) {
			continue;
		}
		//�C���f�b�N�X�o�b�t�@.
		m_pContext11->IASetIndexBuffer(
			m_ppIndexBuffer[No], DXGI_FORMAT_R32_UINT, 0);
		//�}�e���A���̊e�v�f���V�F�[�_�ɓn��.
		D3D11_MAPPED_SUBRESOURCE pDataMat;
		if (SUCCEEDED(
			m_pContext11->Map(m_pCBufferPerMaterial,
				0, D3D11_MAP_WRITE_DISCARD, 0, &pDataMat)))
		{
			CBUFFER_PRE_MATERIAL cb;
			//�A���r�G���g,�f�B�t���[�Y,�X�y�L�������V�F�[�_�ɓn��.
			cb.vAmbient = m_pMaterials[m_AttrID[No]].Ambient;
			cb.vDiffuse = m_pMaterials[m_AttrID[No]].Diffuse;
			cb.vSpecular = m_pMaterials[m_AttrID[No]].Specular;

			memcpy_s(pDataMat.pData, pDataMat.RowPitch, (void*)&cb, sizeof(cb));

			m_pContext11->Unmap(m_pCBufferPerMaterial, 0);
		}

		//���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�����H.
		//�V�F�[�_�ł�register�ԍ��Ƒ��������A�����Ă���.
		m_pContext11->VSSetConstantBuffers(1, 1, &m_pCBufferPerMaterial);
		m_pContext11->PSSetConstantBuffers(1, 1, &m_pCBufferPerMaterial);

		//�e�N�X�`�����V�F�[�_�ɓn��.
		if (m_pMaterials[m_AttrID[No]].pTexture != nullptr) {
			//�e�N�X�`��������Ƃ�.
			m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
			m_pContext11->PSSetShaderResources(0, 1, &m_pMaterials[m_AttrID[No]].pTexture);
		}
		else {
			//�e�N�X�`�����Ȃ��Ƃ�.
			ID3D11ShaderResourceView* pNothing[1] = { 0 };
			m_pContext11->PSSetShaderResources(0, 1, pNothing);
		}

		//�v���~�e�B�u(�|���S��)�������_�����O.
		m_pContext11->DrawIndexed(m_pMaterials[m_AttrID[No]].dwNumFace * 3, 0, 0);
	}

}
