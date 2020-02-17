#ifndef CCOMMAND_BASE_H
#define CCOMMAND_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Command\enumCommand_Global.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"
#include "..\Sound\CSEPlayManager.h"


#include "..\Effect\SparkleEffect\GreatEffect\CGreatEffect.h"
#include "..\Effect\SparkleEffect\GoodEffect\CGoodEffect.h"

/************************************************
*		�R�}���h�̌��ƂȂ�N���X.
**/
class CCommand_Base
{
public:
	CCommand_Base();
	virtual ~CCommand_Base();

	//===================�萔=======================//.
	const int	COMMAND_DECISION_MAX	= 2;			//�R�}���h����ő吔.
	const int	STANDERD_COMMAND_USE	= 0;			//��{�I�Ɏg���R�}���h�̗v�f�ԍ�.
	const float ALPHA_MAX			= 1.0f;				//���ߒl�ő�.
	const float ALPHA_MIN			= 0.6f;				//���ߒl�ŏ�.
	const float	LIGHT_SCALE_MAX		= 2.0f;				//�{�^���̌��̑傫���ő吔.			
	const float LIGHT_SCALE_MIN		= 1.0f;				//�{�^���̌��̑傫���ŏ��l.
	const float LIGHT_ALPHA_MAX		= 1.0f;				//�{�^���̌��̓��ߒl�ő�l.
	const float LIGHT_ALPHA_MIN		= 0.0f;				//�{�^���̌��̓��ߒl�ŏ��l.

	//===================�֐�=======================//.
	void	Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�l�ݒ菈���֐�.
	virtual void UpDate(enCommandType CommandType) = 0;								//�X�V�����֐�.
	virtual void Render() = 0;														//�`�揈���֐�.
	void	EffectAndSE_Play();														//SE�Đ������֐�.
	void	EffectRender();															//�G�t�F�N�g�`��.

	//�`���u�������֐��`.
	//�G�̌l�̍��W.
	void	SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }												
	//�ʏ�G�̃{�^��.
	void	SetButtonNum(int ButtonNum) { m_ButtonNum = ButtonNum; }								
	//�{�X�̃{�^��.
	void	SetMultipleButtonNum(int ButtonNum, int Button) { m_pButtonNum[Button] = ButtonNum; }	
	//Player�̍��W.
	void	SetPlayerPos(D3DXVECTOR3 PlayerPos) { m_vPlayerPos = PlayerPos; }						
	//�{�X�R�}���h�\���t���O.
	void	SetDispFlag(bool flag) { m_bDispFlag = flag; }											
	//�R�}���h����\�t���O.
	void	SetJudgePossible(bool flag) { m_bJudgePossible = flag; }								
	//�^�C�~���O���̃R�}���h�̍��W.
	void	SetDispHight(float Pos) { m_fDispHight = Pos; }											
	//�������J�E���g.
	void	SetLongPushCnt(int Cnt) { m_LongPushCnt = Cnt; }										
	//�`���擾�����֐��`.
	enInput_Decision GetInput_Deision(int command = 0) { return m_penInput_Decision[command]; }		
	bool GetButtonLightFinish() { return m_bButtonLightFinish; }

protected:
	//===================�֐�========================//.
	virtual void Release() = 0;														//��������֐�.
	virtual void DispDecision() = 0;												//�\�����菈���֐�.
	virtual void CommandDecision(enCommandType CommandType) = 0;					//�R�}���h���菈���֐�.

	void	Init();																	//�����ݒ菈���֐�.
	void	Button_Render();														//�{�^���`�揈���֐�.

	//===================�ϐ�========================//.
	D3DXVECTOR3			m_vCameraPos;			//�J�����ʒu.
	D3DXMATRIX			m_mView;				//�r���[�s��.
	D3DXMATRIX			m_mProj;				//�v���W�F�N�V�����s��.

	CResourceManager*	m_pCResourceManager;	//�ǂݍ��݊Ǘ��N���X.
	CSprite*			m_pCSprite;				//�X�v���C�g�N���X.
	CDepth_Stencil*		m_pCDepth_Stencil;		//�f�v�X�X�e���V���N���X.
	float				m_fAlpha;				//���ߒl.

	D3DXVECTOR3			m_vPos;					//�ʒu���.
	D3DXVECTOR3			m_vInitPos;				//�����ʒu.
	float				m_fDispHight;			//�\������.
	int					m_ButtonNum;			//�{�^���ԍ�.
	int*				m_pButtonNum;			//�{�^���ԍ�(�����̏ꍇ).
	enInput_Decision*	m_penInput_Decision;	//��������.
	enInput_Decision*	m_penOld_Decision;		//�O��̔���.
	bool				m_bDispFlag;			//�\���t���O.
	bool				m_bJudgePossible;		//����\�t���O.
	int					m_LongPushCnt;			//�������h�~�J�E���g.

	D3DXVECTOR3			m_vPlayerPos;			//�v���C���[�̈ʒu���.

	CSEPlayManager*		m_pCSEPlayManager;		//SE�Đ��N���X.

	CEffectBase**		m_ppCEffectBase;		//�G�t�F�N�g�x�[�X�N���X.

	CSprite*			m_pCButtonLightSprite;	//�{�^���̌��̃X�v���C�g�N���X.
	float				m_fButtonLightAlpha;	//�{�^���̌����ߒl.
	float				m_fButtonLightScale;	//�{�^���̌��傫��.

	bool				m_bButtonLightFinish;	//�{�^���̌��I��.

private:
};

#endif	//#ifndef CCOMMAND_BASE_H.