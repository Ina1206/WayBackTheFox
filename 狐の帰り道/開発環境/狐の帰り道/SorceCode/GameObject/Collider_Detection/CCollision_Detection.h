#ifndef CCOLLISION_DETECTION_H
#define CCOLLISION_DETECTION_H

#include "..\..\Drawing\Resource\CResourceManager.h"

/*********************************************
*		衝突判定クラス.
**/
class CCollision_Detection
{
public:
	CCollision_Detection();
	~CCollision_Detection();

	//=================列挙体=======================//.
	//オブジェクトの種類.
	enum class enObject {
		Raccoon_Dog,			//タヌキ.
		Cow_Ghost,				//牛お化け.
		Kappa,					//カッパ.
		BigRccoon_Dog,			//デカタヌキ.
		Playre,					//プレイヤー.
		Ground,					//地面.

		Max,					//最大数.
		Start = Raccoon_Dog,	//最初.
	};


	//=================構造体=======================//.
	//オブジェクト情報.
	struct stObjectInfo {
		enObject	Object;		//オブジェクトの種類.
		D3DXVECTOR3 vPos;		//位置情報.
	};

	//==================関数========================//.
	void Init();																						//初期化処理.
	bool JugeHit(stObjectInfo* AttackInfo, stObjectInfo* TargetInfo);									//衝突判定処理関数.

	//～情報置換処理関数～.
	void SetScale(float fScale, enObject Object) { m_pfScale[static_cast<int>(Object)] = fScale; }		//各キャラごとのスフィアの大きさ.
private:
	//=================列挙体========================//.
	//当たり判定のオブジェクト種類.
	enum class enHit {
		Attack,						//攻撃側.
		Target,						//標的側.
	};
	//==================関数========================//.
	void Attach();					//受け取り処理関数.
	void Release();					//解放処理関数.

	//===================変数=======================//.
	CDX9Mesh**		m_ppSphereMesh;	//CDX9Meshクラス.

	D3DXVECTOR3*	m_pvPos;		//座標.
	float*			m_pfScale;		//大きさ.

};

#endif	//#ifndef CCOLLISION_DETECTION_H.