#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H
//==============�񋓑�==================//.
//�G�̎��.
enum class enEnemy {
	RaccoonDog = 0,						//�^�k�L.
	Cow_Ghost,							//��������.
	UpRaccoonDog,						//�オ��K.
	Big_RaccoonDog,						//�f�J�^�k�L.

	Max,
	Start = RaccoonDog,
	NormalEnemyMax = UpRaccoonDog + 1,	//�ʏ�G�̍ő�l.
};

#endif	//#ifndef ENEMY_TYPE_H.