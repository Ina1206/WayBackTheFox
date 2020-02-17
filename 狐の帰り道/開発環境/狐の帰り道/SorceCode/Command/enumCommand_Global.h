#ifndef ENUM_COMMAND_GLOBAL_H
#define ENUM_COMMAND_GLOBAL_H

//===============列挙体====================//.
//コントローラのボタン基準のコマンドの種類.
enum class enCommandType {
	A = 0,		//Aボタン.
	B,			//Bボタン.
	X,			//Xボタン.
	Y,			//Yボタン.
	Up,			//上ボタン.
	Right,		//右ボタン.
	Down,		//下ボタン.
	Left,		//左ボタン.

	Max,		//最大値.
	Start = A,	//最初の値.
};

//入力判定.
enum class enInput_Decision {
	Great = 0,		//素晴らしい.
	Good,			//良い.
	Bad,			//悪い.

	Max,			//最大.
	Start = Great,	//最初.
};


#endif//#ifndef ENUM_COMMAND_GLOBAL_H.