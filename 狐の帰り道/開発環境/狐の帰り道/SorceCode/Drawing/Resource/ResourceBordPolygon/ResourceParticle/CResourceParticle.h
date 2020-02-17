#ifndef CRESOURCE_PARTICLE_H
#define CRESOURCE_PARTICLE_H

#include "..\..\..\Bord_Polygon\GameSprite\CParticle.h"
#include "..\..\..\Bord_Polygon\CDepth_Stencil.h"

#include "..\..\CResourceBase.h"

/****************************************************
*		パーティクル読み込みクラス.
**/
class CResourceParticle
	: public CResourceBase
{
public:
	CResourceParticle();
	~CResourceParticle();

	//===================列挙体======================//.
	//Spriteの種類.
	enum class enParticle {
		Maple_First = 0,		//もみじ.
		Maple_Second,			//もみじ2.

		Max,					//最大数.
		Start = Maple_First,	//最初.
	};

	//====================関数======================//.
	HRESULT Init();												//初期設定処理関数.
	HRESULT Load();												//読み込み処理関数.
	HRESULT ReleaseCalling();									//解放処理呼び出し関数.

	//===============情報獲得処理関数================//.
	CParticle*	GetParticle(enParticle Particle);
private:
	//====================関数======================//.
	HRESULT Create(enParticle Particle, const char* pfileName);	//作成処理関数.
	HRESULT Release(enParticle Particle);						//解放処理関数.
	HRESULT Check_ParticleRnge(enParticle Particle);			//パーティクルの範囲を調べる関数.

	//===================クラス=====================//.
	CParticle**	m_ppParticle;									//パーティクルクラス.
};

#endif //#ifndef CRESOURCE_PARTICLE_H.