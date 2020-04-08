#ifndef CSCENEBASE_H
#define CSCENEBASE_H

//-----�`��------//.
#include "..\Drawing\Bord_Polygon\DebugText\CDebugText.h"	//�f�o�b�O�e�L�X�g�N���X.

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Sound\CSEPlayManager.h"

/**********************************
*	�V�[���x�[�X�N���X.
**/
class CSceneBase 
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===========�֐�=============//.
	void Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos);	//�l�ݒ�.
	void Value(D3DXMATRIX& mProj, D3DXVECTOR3& vLight);

	virtual void Init_Process() = 0;		//�����ݒ菈���֐�.
	virtual void UpDate()		= 0;		//�X�V�����֐�.
	virtual void Render()		= 0;		//�`�揈���֐�.
	virtual void Release()		= 0;		//��������֐�.

	void SetEndGameMain(bool flag) { m_bEndGameMainFlag = flag; }
	bool GetEndGameMain() { return m_bEndGameMainFlag; }
	void SetPointSum(int num) { m_PointSum = num; }
	int  GetPointSum() { return m_PointSum; };
	bool GetUIDrawEndFlag() { return m_bUIDrawEnd; }

	void SetControllerFlag(bool flag) {	m_bControllerFlag = flag; }//�R���g���[���t���O�擾�����֐�.
protected:
	D3DXVECTOR3		m_vLight;		//���C�g�̕���.
	D3DXVECTOR3		m_vCamPos;		//�J�����ʒu.
	D3DXMATRIX		m_mView;		//�r���[�s��.
	D3DXMATRIX		m_mProj;		//�v���W�F�N�V�����s��.

	bool			m_bEndGameMainFlag;
	static int		m_PointSum;
	bool			m_bUIDrawEnd;

	bool			m_bControllerFlag;	//�R���g���[���t���O.

private:

};


#endif	//#ifndef CSCENEBASE_H.