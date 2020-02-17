#ifndef CRESOURCE_PARTICLE_H
#define CRESOURCE_PARTICLE_H

#include "..\..\..\Bord_Polygon\GameSprite\CParticle.h"
#include "..\..\..\Bord_Polygon\CDepth_Stencil.h"

#include "..\..\CResourceBase.h"

/****************************************************
*		�p�[�e�B�N���ǂݍ��݃N���X.
**/
class CResourceParticle
	: public CResourceBase
{
public:
	CResourceParticle();
	~CResourceParticle();

	//===================�񋓑�======================//.
	//Sprite�̎��.
	enum class enParticle {
		Maple_First = 0,		//���݂�.
		Maple_Second,			//���݂�2.

		Max,					//�ő吔.
		Start = Maple_First,	//�ŏ�.
	};

	//====================�֐�======================//.
	HRESULT Init();												//�����ݒ菈���֐�.
	HRESULT Load();												//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();									//��������Ăяo���֐�.

	//===============���l�������֐�================//.
	CParticle*	GetParticle(enParticle Particle);
private:
	//====================�֐�======================//.
	HRESULT Create(enParticle Particle, const char* pfileName);	//�쐬�����֐�.
	HRESULT Release(enParticle Particle);						//��������֐�.
	HRESULT Check_ParticleRnge(enParticle Particle);			//�p�[�e�B�N���͈̔͂𒲂ׂ�֐�.

	//===================�N���X=====================//.
	CParticle**	m_ppParticle;									//�p�[�e�B�N���N���X.
};

#endif //#ifndef CRESOURCE_PARTICLE_H.