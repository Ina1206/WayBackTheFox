#ifndef ENCAMERA_TYPE_H
#define	ENCAMERA_TYPE_H

//カメラタイプ.
enum class enCameraType {
	UpCamera,			//上から見るカメラ.
	BossBadCamera,		//ボスクリアできなかったカメラ.
	BossGreatCamera,	//ボスクリアできたカメラ.
	StanderdCamera,		//通常カメラ.
};

#endif	//#ifndef ENCAMERA_TYPE_H.