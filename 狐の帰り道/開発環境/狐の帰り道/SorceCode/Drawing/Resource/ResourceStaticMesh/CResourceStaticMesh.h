#ifndef CRESOURCE_CDX9MESH_H
#define CRESOURCE_CDX9MESH_H

#include "..\..\3D_Object\CDX9Mesh.h"
#include "..\CResourceBase.h"

/**********************************************
*	StaticMesh用読み込みクラス.
**/
class CResourceStaticMesh
	: public CResourceBase
{
public:
	CResourceStaticMesh();
	~CResourceStaticMesh();

	//===================列挙体======================//.
	//StaticMeshの種類.
	enum class enStaticMesh {
		Ground = 0,		//地面.
		Cow_Gohst,		//牛お化け
		Hit_Sphere,		//当たり判定用球体.
		Gate,			//鳥居.
		BackGround,		//背景.
		Grass,			//草.
		AroundGround,	//周りの地面.
		Ground2,		//地面2つ目.

		Max,			//最大数.
		Start = Ground,	//最初.
	};

	//====================関数======================//.
	HRESULT Init();						//初期設定処理関数.
	HRESULT Load();													//読み込み処理関数.
	HRESULT ReleaseCalling();										//解放処理呼び出し関数.

	//===============情報獲得処理関数================//.
	CDX9Mesh*	GetStaticMesh(enStaticMesh StaticMesh);
private: 
	//====================関数======================//.
	HRESULT Create(enStaticMesh StaticMesh, const char* pfileName);	//作成処理関数.
	HRESULT Release(enStaticMesh StaticMesh);						//解放処理関数.
	HRESULT Check_MeshRnge(enStaticMesh StaticMesh);				//メッシュの範囲を調べる関数.
	HRESULT	InitSphere();											//スフィアの作成処理関数.

	//===================クラス=====================//.
	CDX9Mesh**	m_ppStaticMesh;	//メッシュクラス.


};

#endif	//#ifndef CRESOURCE_CDX9MESH_H.