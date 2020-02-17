#ifndef C_SOUND_H
#define C_SOUND_H

#include <Windows.h >

//ﾗｲﾌﾞﾗﾘ読込.
#pragma comment( lib, "winmm.lib" )

//文字列ﾊﾞｯﾌｧ.
const int STR_BUFF_MAX = 256;

/**********************************************************.
*	ｻｳﾝﾄﾞｸﾗｽ.	
*		midi, mp3, wav形式のﾌｧｲﾙの再生・停止等を行う.
**/
class clsSound
{
public:
	clsSound();		//ｺﾝｽﾄﾗｸﾀ.
	~clsSound();	//ﾃﾞｽﾄﾗｸﾀ.

	//音声ﾌｧｲﾙを開く.
	bool Open( LPCTSTR sFName, char* sAlias, HWND hWnd);

	//音声ﾌｧｲﾙを閉じる.
	bool Close();

	//再生.
	//特定のﾀｲﾐﾝｸﾞでチェックしたい場合三つ目のやつを入れる.
	//状態のﾁｪｯｸをしない場合はﾃﾞﾌｫﾙﾄで false が入っているので引数が二つでもOK.
	bool Play( bool bNotify = false );

	//停止.
	bool Stop();

	//状態を取得する関数.
	bool GeaStatus( char *sStatus );

	//音の停止を確認する関数.
	bool IsStopped();

	//音の再生中を確認する関数.
	bool IsPlaying();

	//再生位置を最初に戻す関数.
	bool SeekToStart();

	//音量を調整する関数.
	bool VolumeConvert(int volume);

private:
	HWND	m_hWnd;	//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙ.
	char	m_sAlias[STR_BUFF_MAX];//ｴｲﾘｱｽ.

	//初期設定関数.
	void SetInitParam( char *sAlias, HWND hWnd );
};


#endif //#ifndef C_SOUND_H