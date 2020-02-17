#ifndef _C_XINPUT_H_
#define _C_XINPUT_H_

#include <Windows.h>
#include <Xinput.h>

#pragma comment( lib, "xinput.lib" )

#define INPUT_TRIGGER_MIN	(0)
#define INPUT_TRIGGER_MAX	(255)
#define INPUT_THUMB_MIN		(-32768)
#define INPUT_THUMB_MAX		(32767)
#define INPUT_VIBRATION_MIN	(0)
#define INPUT_VIBRATION_MAX	(65535)


class clsXInput
{
public:
	clsXInput(){
		ZeroMemory( this, sizeof( clsXInput ) );
	}
	~clsXInput(){}

	bool UpdateStatus(){
		if( ERROR_SUCCESS == XInputGetState(
			m_padId,
			&m_state )) 
		{
			return true;
		}
		return false;
	}
	bool UpdateKeyStatus(){
		if( ERROR_SUCCESS == XInputGetKeystroke(
				m_padId,
				0,
				&m_keystroke ) )
		{
			return true;
		}
		return false;
	}

	bool IsPress( const WORD _padKey )
	{
		if( m_state.Gamepad.wButtons & _padKey ){
			return true;
		}
		return false;
	}

	bool SetVibration( WORD LMotorSpd, WORD RMotorSpd )
	{
		m_vibration.wLeftMotorSpeed		= LMotorSpd;
		m_vibration.wRightMotorSpeed	= RMotorSpd;

		if( ERROR_SUCCESS == XInputSetState(
			m_padId, &m_vibration )){
			return true;
		}
		return false;
	}

	void EndProc(){
		SetVibration( 0, 0 );
//		XInputEnable( false );
	}

	BYTE GetLTrigger(){
		return m_state.Gamepad.bLeftTrigger;
	}
	BYTE GetRTrigger(){
		return m_state.Gamepad.bRightTrigger;
	}
	SHORT GetLThumbX(){
		return m_state.Gamepad.sThumbLX;
	}
	SHORT GetLThumbY(){
		return m_state.Gamepad.sThumbLY;
	}
	SHORT GetRThumbX(){
		return m_state.Gamepad.sThumbRX;
	}
	SHORT GetRThumbY(){
		return m_state.Gamepad.sThumbRY;
	}

private:
	DWORD				m_padId;
	XINPUT_STATE		m_state;
	XINPUT_KEYSTROKE	m_keystroke;
	XINPUT_VIBRATION	m_vibration;
};


#endif//#ifndef _C_XINPUT_H_