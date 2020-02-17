#include "CSceneBase.h"
#include <crtdbg.h>

int CSceneBase::m_PointSum;

CSceneBase::CSceneBase()
	: m_vLight			(0.0f, 0.0f, 0.0f)
	, m_vCamPos			(0.0f, 0.0f, 0.0f)
	, m_mView			()
	, m_mProj			()
	, m_bEndGameMainFlag(false)
	, m_bUIDrawEnd		(false)
{
}

CSceneBase::~CSceneBase()
{
}

//=========ílê›íË===========//.
void CSceneBase::Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos)
{
	m_vLight = vLight;
	m_vCamPos = vCamPos;
	m_mView = mView;
	m_mProj = mProj;
}

void CSceneBase::Value(D3DXMATRIX& mProj, D3DXVECTOR3& vLight)
{
	m_vLight = vLight;
	m_mProj = mProj;
}
