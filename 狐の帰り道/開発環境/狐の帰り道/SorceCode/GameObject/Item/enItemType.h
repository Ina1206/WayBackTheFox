#ifndef ITEM_TYPE
#define ITEM_TYPE
//==============—ñ‹“‘Ì==================//.
//ƒAƒCƒeƒ€‚Ìí—Ş.
enum class enItemType
{
	Vegetables = 0,		//–ìØ.
	Meat,				//“÷.
	Fish,				//‹›.
	Rice,				//•Ä.

	MAX,				//Å‘å.
	Start = Vegetables,
};

//”»’è.
enum class enItemJudge
{
	Success = 0,	//¬Œ÷.
	failure,		//¸”s.
	Invincible,		//–³“G.

	Max,			//Å‘å”.
	Start = Success,//Å‰.
};

//–³“Gó‘Ô.
enum class enInvincible
{
	Invincible = 0,	//–³“G.
	Not_Invincible,//–³“G‚¶‚á‚È‚¢.
};

#endif//#ifndef ITEM_TYPE
