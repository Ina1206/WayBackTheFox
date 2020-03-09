#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H
//==============列挙体==================//.
//敵の種類.
enum class enEnemy {
	RaccoonDog = 0,						//タヌキ.
	Cow_Ghost,							//牛お化け.
	UpRaccoonDog,						//上がる狸.
	Big_RaccoonDog,						//デカタヌキ.

	Max,
	Start = RaccoonDog,
	NormalEnemyMax = UpRaccoonDog + 1,	//通常敵の最大値.
};

#endif	//#ifndef ENEMY_TYPE_H.