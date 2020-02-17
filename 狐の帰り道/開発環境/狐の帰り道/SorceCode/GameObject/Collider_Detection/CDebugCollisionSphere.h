#ifndef CDEBUG_COLLISION_SPHERE_H
#define CDEBUG_COLLISION_SPHERE_H

#include "..\..\Drawing\Resource\CResourceManager.h"

/**************************************************
*	デバッグ用の当たり判定球体クラス.
**/
class CDebugCollisionSphere
{
public:
	CDebugCollisionSphere();
	~CDebugCollisionSphere();

	//=====================関数=========================//.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);		//描画処理関数.

	//====情報置換処理関数====//.
	void SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }
	void SetScale(float fScale) { m_fScale = fScale; }
private:
	//=====================関数=========================//.
	void Attach();				//取得関数.
	void Release();				//解放処理関数.


	//=====================変数==========================//.
	CDX9Mesh*		m_pSphere;	//球体のメッシュ.

	D3DXVECTOR3		m_vPos;		//座標.
	float			m_fScale;	//大きさ.
};

#endif	//#ifndef CDEBUG_COLLISION_SPHERE_H.