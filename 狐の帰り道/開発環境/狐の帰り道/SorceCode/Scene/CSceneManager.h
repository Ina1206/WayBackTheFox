#ifndef CSCENEMANAGER_H
#define CSCENEMANAGER_H


#include "..\MyMacro.h"						//マクロ.
#include "..\Drawing\3D_Object\CDX9Mesh.h"	//CDX9Meshクラス.
#include "..\FileLoad\CFileLoadManager.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"
#include "..\Sound\CSEPlayManager.h"
#include "..\Fade\CBran.h"

#include "Load/CLoad.h"

//コントローラクラス.
#include"..\Controller\CXInput.h"


//--------シーン---------//.
#include "CSceneBase.h"						//シーンベースクラス.
#include "Title\CTitle.h"					//タイトルクラス.
#include "Main/CGameMain.h"					//ゲームメインクラス.
#include "Clear/CClear.h"					//クリア.

//===========列挙体=============//.
//シーンの種類の列挙体.
enum class enScene
{
	Title = 0,			//タイトル.
	GameMain,			//ゲーム中.
	Clear				//クリア.
};					

/***********************************
*	シーン管理クラス.
**/
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	//============関数==============//.
	void SceneChange();																		//シーン変更処理関数.
	void InitLoad(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);		//読み込み処理関数.
	void UpDate();																			//更新処理関数.
	void Render(D3DXMATRIX& mProj, D3DXVECTOR3& vLight);									//描画処理関数.
	
	//=======情報取得処理関数========//.
	bool GetLoadFinish() { return m_bLoadFinish; }
private:
	//============定数==============//.		
	const float ALPHA_MAX		= 1.0f;	//透過値最大数.
	const int	BGM_VOLUME_MAX	= 1000;	//BGMの音量最大値.

	//============列挙体==============//.
	//行動制御用.
	enum class enOperation
	{
		Possible = 0,		//可能.
		Impossible,			//不可能.

		Max,				//最大.
		Start = Possible,	//最初.
	};

	//============関数==============//.		
	void SceneSetting();		//シーン設定.
	void Destroy();				//解放処理関数.
	void StageSelect();			//ステージ選択処理関数.

	//============変数==============//.
	HWND					m_hWnd;				//ウィンドウハンドル.
	ID3D11Device*			m_pDevice11;		//デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;		//デバイスコンテキスト.

	CSceneBase*				m_pCScene;			//現在のシーン.
	clsXInput*				m_pCInput;			//コントローラクラス.
	CBran*					m_pCBran;			//ふすまクラス.

	enScene					m_enScene;			//シーンの種類の列挙体.
	enOperation				m_enOperation;		//操作列挙体.
	int						m_Frame;			//シーン切り替え用.

	int						m_BGMnum;			//BGMの番号.
	int						m_BGM_Volume;		//BGMの音量.

	bool					m_bLoadFinish;		//読み込み終了フラグ.

	int*					m_pStageTypeNum;	//ステージの種類.
	int						m_OldStageTypeNum;	//前回のステージ番号.
	int						m_StageCnt;			//ステージカウント.

	int						m_PushButtonCnt;	//ボタンカウント.
	int						m_SceneChangeCnt;	//シーン切り替え時のボタンカウント.
	bool					m_bSpecialStageFlag;//特別ステージフラグ.
	bool					m_bControllerFlag;	//コントローラフラグ.
};

#endif //#ifndef CSCENEMANAGER_H.