#ifndef ITEM_TYPE
#define ITEM_TYPE
//==============�񋓑�==================//.
//�A�C�e���̎��.
enum class enItemType
{
	Vegetables = 0,		//���.
	Meat,				//��.
	Fish,				//��.
	Rice,				//��.

	MAX,				//�ő�.
	Start = Vegetables,
};

//����.
enum class enItemJudge
{
	Success = 0,	//����.
	failure,		//���s.
	Invincible,		//���G.

	Max,			//�ő吔.
	Start = Success,//�ŏ�.
};

//���G���.
enum class enInvincible
{
	Invincible = 0,	//���G.
	Not_Invincible,//���G����Ȃ�.
};

#endif//#ifndef ITEM_TYPE
