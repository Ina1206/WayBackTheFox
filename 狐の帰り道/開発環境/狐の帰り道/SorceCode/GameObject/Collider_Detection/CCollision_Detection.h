#ifndef CCOLLISION_DETECTION_H
#define CCOLLISION_DETECTION_H

#include "..\..\Drawing\Resource\CResourceManager.h"

/*********************************************
*		�Փ˔���N���X.
**/
class CCollision_Detection
{
public:
	CCollision_Detection();
	~CCollision_Detection();

	//=================�񋓑�=======================//.
	//�I�u�W�F�N�g�̎��.
	enum class enObject {
		Raccoon_Dog,			//�^�k�L.
		Cow_Ghost,				//��������.
		Kappa,					//�J�b�p.
		BigRccoon_Dog,			//�f�J�^�k�L.
		Playre,					//�v���C���[.
		Ground,					//�n��.

		Max,					//�ő吔.
		Start = Raccoon_Dog,	//�ŏ�.
	};


	//=================�\����=======================//.
	//�I�u�W�F�N�g���.
	struct stObjectInfo {
		enObject	Object;		//�I�u�W�F�N�g�̎��.
		D3DXVECTOR3 vPos;		//�ʒu���.
	};

	//==================�֐�========================//.
	void Init();																						//����������.
	bool JugeHit(stObjectInfo* AttackInfo, stObjectInfo* TargetInfo);									//�Փ˔��菈���֐�.

	//�`���u�������֐��`.
	void SetScale(float fScale, enObject Object) { m_pfScale[static_cast<int>(Object)] = fScale; }		//�e�L�������Ƃ̃X�t�B�A�̑傫��.
private:
	//=================�񋓑�========================//.
	//�����蔻��̃I�u�W�F�N�g���.
	enum class enHit {
		Attack,						//�U����.
		Target,						//�W�I��.
	};
	//==================�֐�========================//.
	void Attach();					//�󂯎�菈���֐�.
	void Release();					//��������֐�.

	//===================�ϐ�=======================//.
	CDX9Mesh**		m_ppSphereMesh;	//CDX9Mesh�N���X.

	D3DXVECTOR3*	m_pvPos;		//���W.
	float*			m_pfScale;		//�傫��.

};

#endif	//#ifndef CCOLLISION_DETECTION_H.