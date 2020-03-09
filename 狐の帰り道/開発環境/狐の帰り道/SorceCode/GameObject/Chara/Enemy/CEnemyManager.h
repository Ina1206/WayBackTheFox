#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

//===========敵のヘッダーファイル=========//.
#include "NormalEnemy/Raccoon_Dog/CRaccoon_Dog.h"
#include "NormalEnemy/Kappa/CKappa.h"
#include "NormalEnemy/Cow_Ghost/CCow_Ghost.h"
#include "Boss/Big_Raccoon_Dog/CBig_Raccoon_Dog.h"

//========アイテムのヘッダファイル=========//.
#include "..\..\Item\CItemManager.h"

//読み込みファイル.
#include "..\..\..\FileLoad\CFileInitPos.h"
#include "..\..\..\FileLoad\CFileLoadManager.h"

//コントローラクラス.
#include"..\..\..\Controller\CXInput.h"

//レイ.
#include "..\..\..\Ray\CRay.h"

/***************************************************
*	敵の管理用クラス.
**/
class CEnemyManager
{
public:
	CEnemyManager();
	~CEnemyManager();

	//=====================定数=======================//.
	const float DECELERATION_DISTANCE	= 3.0f;											//減速スタート距離.	
	const int	BOSS_TYPE_NUM			= static_cast<int>(enEnemy::Big_RaccoonDog);	//ボスの番号.
	const int	NORMAL_ENEMY_MAX		= static_cast<int>(enEnemy::NormalEnemyMax);	//通常敵の最大数.
	const int	ENEMY_MAX				= static_cast<int>(enEnemy::Max);				//敵の最大数.
	const int	BOSS_SINGLE_NUM			= 1;											//ボス単体番号.
	const int	COMMAND_DECISION_MAX	= 2;											//コマンド判定結果最大数.
	const float	DECISION_START_WIDTH	= 0.8f;											//判定開始幅の半分.
	const float	DECISION_END_BACK		= 0.5f;											//判定終了のplayerの座標からの奥行.

	//=====================関数=======================//.
	void InitProcess();																					//初期化処理関数.
	void Update();																						//更新処理関数.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);	//描画処理関数.
	void Release();																						//解放処理関数.
	bool JudgeCameraUp();																				//カメラの上がるか判定処理関数.

	//～～情報獲得処理関数～～.
	//敵の最大数.
	int	GetEnemyMax(int enemyType) { return m_pEnemyMax[enemyType]; }
	//敵の総合最大数.
	int GetAllEnemySumMax() { return m_AllEnemyMax; }
	//コマンドの最大数.
	int GetCommandMax(int enemyType) { return m_pCommandMax[enemyType]; }
	//敵の座標.
	D3DXVECTOR3 GetEnemyPos(int enemyType, int enemy = 0);
	//敵の角度.	
	D3DXVECTOR3 GetEnemyRot(int enemyType, int enemy = 0) { return m_pCBigRaccoon_Dog->GetRotation(); }
	//減速フラグ.
	bool GetDeceleration() { return m_bDecelerationStart; }			
	//表示フラグ.
	bool GetBossDispFlag() { return m_pCBigRaccoon_Dog->GetDispFlag(); }
	//ボスコマンド表示開始フラグ.
	bool GetBossCommandDisp() { return m_pCBigRaccoon_Dog->GetCommandStart(); }
	//コマンド結果.
	enInput_Decision GetEnemyInputDecision(int enemy, int num = 0);
	//カメラを上げるフラグ.
	bool GetMoveUpCamera() { return m_bMoveUpCamera; }

	//～～情報置換処理関数～～.
	//移動速度.
	void SetSpeed(float Speed) { m_fMoveSpeed = Speed; }						
	//移動距離.
	void SetMovingDistance(float Distance) { m_fMovingDistance = Distance; }	
	//コマンド判定結果.
	void SetInputDecision(int enemy, enInput_Decision Decision) { m_penInputDecision[enemy] = Decision; }
	//プレイヤー座標.
	void SetPlayerPos(D3DXVECTOR3 vPos) { m_vPlayerPos = vPos; }	
	//上がる距離.
	void SetUpDistance(float Distance) { m_fUpDistance = Distance; }	
	//タイマー.
	void SetMoveFlag(bool flag) { m_bMoveFlag = flag; }									

	//アイテムの設定.
	void SetItem(int enemyType, int num, enItemJudge enJudge);
	int  GetPoint_WholeSum() { return m_Point_WholeSum; };
	int GetItem_Sum(int enItem);								//アイテムの合計.


private:
	//====================関数========================//.
	void NormalEnemyUpDate();					//通常敵の更新処理関数.
	void BossUpDate();							//ボスの更新処理関数.
	void Command_Possible();					//コマンド判定可能処理関数.
	HRESULT Command_Entry();					//コマンド入力処理関数.
	void CheckCommandLongPush();				//コマンド長押し確認処理関数.

	//アイテム.
	void ItemUpDate();							//アイテムの更新処理関数.
	void Point_WholeSum(int item);				//ポイント合計の計算処理関数.
	void Item_WholeSum(int item);				//アイテムの合計計算処理関数.


	//===================構造体=======================//.
	//通常敵の情報.
	struct stNormalEnemyInfo {
		CNormalEnemyBase**	m_ppCEnemy;				//敵全体のクラス.
		
		//初期化.
		stNormalEnemyInfo()
			: m_ppCEnemy	(nullptr)
		{}
	};

	//====================変数========================//.
	//敵関係.
	stNormalEnemyInfo*	m_pstNormalEnemyInfo;		//通常敵の構造体.
	CNormalEnemyBase**	m_ppCNormalEnemy;			//敵全体のクラス.
	CBig_Raccoon_Dog*	m_pCBigRaccoon_Dog;			//デカタヌキクラス.
	int*				m_pEnemyMax;				//敵の最大数.
	int					m_AllNormalEnemyMax;		//通常敵のすべての数.
	int					m_AllEnemyMax;				//全ての敵の総数.
	int					m_EnemyHit;					//通常敵の当たった回数.

	//コマンド関係.
	int*				m_pCommandMax;				//コマンドの最大数.
	enInput_Decision**	m_ppenInputDecision;		//コマンド判定結果.
	enInput_Decision*	m_penInputDecision;			//コマンド判定結果.
	bool*				m_pbDecisionPossible;		//判定可能フラグ.
	enCommandType		m_eninputInformation;		//コマンドの入力情報.
	enCommandType		m_enOldInputInformation;	//コマンドの前回の入力情報.
	int					m_LongPushCnt;				//ボタンを長押ししているカウント.

	int*				m_pButtonNum;				//ボタン番号.

	//移動.
	float				m_fMoveSpeed;				//移動速度.
	float				m_fMovingDistance;			//移動距離.
	float				m_fUpDistance;				//上がる距離.	
	bool				m_bDecelerationStart;		//減速スタート.	
	bool				m_bMoveFlag;				//タイマー.		

	//Player.
	D3DXVECTOR3			m_vPlayerPos;				//プレイヤー座標.

	//ファイル.
	CFileLoadManager*	m_pCFileManager;			//ファイル読み込み管理クラス.

	clsXInput*			m_pCInput;					//コントローラクラス.

	bool				m_bMoveUpCamera;			//上にカメラが上がる時のフラグ.

	//アイテム関連.
	CItemManager*		m_pCItemManager;			//アイテムマネージャークラス.
	int					m_Point_WholeSum;			//ポイントの全体合計.
	int					m_VegetablesSum;			//野菜個数合計.
	int					m_VegetablesPoint;			//野菜ポイント合計.
	int					m_MeatSum;					//肉個数合計.
	int					m_MeatPoint;				//肉ポイント合計.
	int					m_FishSum;					//魚個数合計.
	int					m_FishPoint;				//魚ポイント合計.
	int					m_RiceSum;					//米個数合計.
	int					m_RicePoint;				//米ポイント合計.
	bool				m_bCheckItem_Point;			//アイテムポイントの減算に使用.
	bool				m_bCheckItem_Number;		//アイテム個数の減算に使用.
	enItemJudge*		m_OldenJudge;				//前判定.


};


#endif	//#ifndef CENEMYMANAGER_H.