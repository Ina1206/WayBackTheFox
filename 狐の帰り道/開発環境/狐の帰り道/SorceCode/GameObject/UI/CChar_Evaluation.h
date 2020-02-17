#ifndef CCHAR_EVALUATION_H
#define CCHAR_EVALUATION_H

#include "CUI_Base.h"
#include "..\..\Sound\CSEPlayManager.h"
//コントローラクラス.
#include"..\..\Controller\CXInput.h"

class CChar_Evaluation
	: public CUI_Base
{
public:
	CChar_Evaluation();
	~CChar_Evaluation();

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
	const D3DXVECTOR3 EVALUATION_POS	= D3DXVECTOR3(-0.055f, 2.5f,0.1f);		//評価の位置.
	const D3DXVECTOR3 CHAR_POS			= D3DXVECTOR3(-0.028f, 2.498f,0.1f);	//高中低の位置.
	const int SPRITE_MAX				= 4;									//スプライトの最大数.
	const int CHAR_HIGH					= 0;									//高文字番号.
	const int CHAR_MIDDLE				= 1;									//中文字番号.
	const int CHAR_LOW					= 2;									//低文字番号.
	const int CHAR_EVALUATION			= 3;									//評価文字番号.
	const float SCALE_STANDARD			= 1.0f;									//大きさ標準.
	const float SCALE_MIN				= 0.0f;									//大きさ最小.
	const float SCALE_MAX				= 2.0f;									//大きさ最大.
	const float SCALE_SPEED				= 0.3f;									//大きさ速度.
	const float SCALE_SPEED_CHAR		= 0.05f;								//大きさ速度.
	const float ROTAITON_MAX			= 6.3f;									//回転値最大.
	const float ROTAITON_SPEED			= 0.3f;									//回転速度.
	const int   EVALUATION_DISP_TIME	= 60;									//評価描画時間.
	const int	CHAR_DISP_TIME			= 120;
	const int	INPUT_OK				= 5;									//操作可能時間.

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();												//解放処理関数.
	void SetScale_Dowm(int num);								//縮小設定.
	void SetRotation(int num);									//回転値設定.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	CSprite**		m_ppCCharSprite;	//Spriteクラス.
	CSEPlayManager*	m_pCSEPlayManager;	//CSEPlayManagerクラス.
	enClear_Status	m_enClear_Status;	//クリアの状態.
	clsXInput*		m_pCInput;			//コントローラクラス.

	D3DXVECTOR3		m_vRot;
	float*			m_fScale;			//位置.
	float			m_fRot;				//回転値.
	bool*			m_pbDispFlag;		//描画フラグ.
	int				m_frame;			//経過時間.
	int				m_WaitTime;			//待機時間.
	bool			m_bCheckSE_Eva;		//評価文字SEチェック用.
	bool			m_bCheckSE_Char;	//文字SEチェック用.


};

#endif//#ifndef CCHAR_EVALUATION_H.
