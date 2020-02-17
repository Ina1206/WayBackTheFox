#ifndef CTIMENG_COMMAND_H
#define CTIMENG_COMMAND_H

#include "..\CCommand_Base.h"

/**************************************
*		タイミングコマンド.
**/
class CTimingCommand
	: public CCommand_Base
{
public:
	CTimingCommand();
	~CTimingCommand();
	//=======================定数===========================//.
	const float CIRCLE_SIZE_MAX		= 1.8f;																//丸のサイズの最大数.
	const float CIRCLE_SIZE_MIN		= 0.4f;																//丸のサイズの最小値.
	const float START_CIRCLE_SIZE	= CIRCLE_SIZE_MIN - 0.2f;											//スタート時の差分.
	const float DISPRY_DISTANCE		= 8.5f;																//丸の表示.
	const float CIRCLE_GREAT_SIZE	= START_CIRCLE_SIZE + ((CIRCLE_SIZE_MAX - CIRCLE_SIZE_MIN) / 3.0f);	//Great判定の大きさ区切り.
	const float CIRCLE_BAD_SIZE		= CIRCLE_SIZE_MIN + 0.03f;											//Badの判定サイズ.
	const float MARU_POS_HIGH		= 0.4f;																//丸の高さ.
	const float HIT_SIZE_MAX		= 2.0f;																//ボタン押したときの光の大きさ最大値.
	const float HIT_SIZE_MIN		= 0.0f;																//ボタン押したときの光の大きさ最小値.
	const float HIT_ALPHA_MAX		= 0.7f;																//ボタン押したときの光の透過値最大値.
	const float HIT_ALPHA_MIN		= 0.0f;																//ボタン押したときの光の透過値最小値.
	const float START_DIFFERENCE	= 0.9f;																//開始位置の差分.
	const float LIGHT_ALPHA_SPEED	= 0.15f;															//光の透過速度.
	const float LIGHT_SCALE_SPEED	= 0.15f;															//光の大きさ速度.
	//=======================関数===========================//.
	void UpDate(enCommandType CommandType);				//更新処理関数.
	void Render();										//描画処理関数.

private:
	//=======================関数===========================//.
	void Release();										//解放処理関数.
	void DispDecision();								//表示判定処理関数.
	void CommandDecision(enCommandType CommandType);	//コマンド判定処理関数.
	void Circle_ScaleDown();							//円の大きさを小さくする処理関数.
	void CircleRender();								//丸の描画処理関数.
	void ButtonPushCircle();							//ボタン押したときの円の処理関数.
	void ButtonPushRender();							//ボタンを押したときの丸の描画処理関数.

	//=======================定数===========================//.
	CSprite*		m_pCSpriteMaru;						//丸のスプライト.
	D3DXVECTOR3		m_vMaruPos;							//丸の位置.
	float			m_fScale;							//丸の大きさ.
	bool			m_bCircleDispry;					//丸の表示フラグ.

	bool			m_bButtonPushFlag;					//ボタン押したときのフラグ.
};

#endif	//#ifndef CTIMENG_COMMAND_H.