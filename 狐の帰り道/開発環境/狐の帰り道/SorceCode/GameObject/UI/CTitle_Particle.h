#ifndef CTITLE_PARTICLE_H
#define CTITLE_PARTICLE_H

#include "CUI_Base.h"

class CTitle_Particle
	: public CUI_Base
{
public:
	CTitle_Particle();
	~CTitle_Particle();

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//------------------------------------------.
	//	定数.
	//------------------------------------------.
	const D3DXVECTOR3	PARTICLE_POS_F		= D3DXVECTOR3(-2.0f, 4.0f, 5.0f);	//パーティクル位置.
	const D3DXVECTOR3	PARTICLE_POS_S		= D3DXVECTOR3(2.0f, 4.0f, 5.0f);	//パーティクル位置.
	const D3DXVECTOR3	PARTICLE_DIR		= D3DXVECTOR3(5.0f, 5.0f, 0.0f);	//パーティクル方向.
	const int			PARTICLE_MAX		= 40;								//パーティクル最大数.
	const float			PARTICLE_ADJ		= 2.0f;								//調整.
	const float			PARTICLE_SPEED		= 2.0f;								//速度.
	const float			PARTICLE_SPEED_ADJ	= 0.0005f;							//速度調整.
	const double		GRAVITY				= 0.003;							//重力.
	const float			ROTATION			= 0.005f;							//回転.
	const float			POSITION_Y_MIN		= -2.0f;							//y座標最小値.
	const float			POSITION_Y_MAX		= 4.0f;								//y座標最大値.
	//------------------------------------------.
	//	構造体.
	//------------------------------------------.
	//パーティクルの情報.
	struct stParticleInfo
	{
		D3DXVECTOR3	m_vPos;
		D3DXVECTOR3 m_vDir;
		D3DXVECTOR3 m_vRot;
		int			m_BirthFrame;
		float		m_fSpeed;
		CParticle*	m_pCParticle;

		stParticleInfo()
			: m_vPos(0.0f, 0.0f, 0.0f)
			, m_vDir(0.0f, 0.0f, 0.0f)
			, m_vRot(0.0f, 0.0f, 0.0f)
			, m_BirthFrame(0)
			, m_fSpeed(0.0f)
			, m_pCParticle(nullptr)
		{};
	};

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();			//解放処理関数.
	void ParticleInit();	//パーティクルの初期化処理.
	void ParticleMove();	//パーティクルの移動処理.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	stParticleInfo*	m_pstParticleInfo;
	int				m_Frame;				//経過時間.

};
#endif//#ifndef CTITLE_PARTICLE_H.