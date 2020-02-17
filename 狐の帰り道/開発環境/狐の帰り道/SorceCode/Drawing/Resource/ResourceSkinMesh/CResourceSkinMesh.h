#ifndef CRESOURCE_SKINMESH_H
#define CRESOURCE_SKINMESH_H

#include "..\CResourceBase.h"

#include "..\..\3D_Object\CDX9SkinMesh.h"


/**********************************************
*	SkinMesh用読み込みクラス.
**/
class CResourceSkinMesh
	: public CResourceBase
{
public:
	CResourceSkinMesh();
	~CResourceSkinMesh();

	//===================列挙体======================//.
	//StaticMeshの種類.
	enum class enSkincMesh {
		Raccoon_Dog,			//タヌキ.
		Player,
		BigRaccoon_Dog,			//デカタヌキ.

		Max,					//最大数.
		Start = Raccoon_Dog,	//最初.
	};


	//====================関数======================//.
	HRESULT Init();													//初期設定処理関数.
	HRESULT Load();													//読み込み処理関数.
	HRESULT ReleaseCalling();										//解放処理呼び出し関数.

	//===============情報獲得処理関数================//.
	CDX9SkinMesh*	GetSkinMesh(enSkincMesh StaticMesh);
private:
	//====================関数======================//.
	HRESULT Create(enSkincMesh StaticMesh, const char* pfileName);	//作成処理関数.
	HRESULT Release(enSkincMesh StaticMesh);						//解放処理関数.
	HRESULT Check_SkinMeshRnge(enSkincMesh StaticMesh);				//スキンメッシュの範囲を調べる関数.
	HRESULT ChangeTexture();										//テクスチャ切り替え.

	//===================クラス=====================//.
	CDX9SkinMesh**	m_ppSkincMesh;	//メッシュクラス.
	CDX9SkinMesh::CHANGE_TEXTURE*	m_pChangeTexture;	//テクスチャ切り替え.

};

#endif	//#ifndef CRESOURCE_SKINMESH_H.