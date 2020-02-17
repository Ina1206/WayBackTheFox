#ifndef ENUM_COMMAND_GLOBAL_H
#define ENUM_COMMAND_GLOBAL_H

//===============�񋓑�====================//.
//�R���g���[���̃{�^����̃R�}���h�̎��.
enum class enCommandType {
	A = 0,		//A�{�^��.
	B,			//B�{�^��.
	X,			//X�{�^��.
	Y,			//Y�{�^��.
	Up,			//��{�^��.
	Right,		//�E�{�^��.
	Down,		//���{�^��.
	Left,		//���{�^��.

	Max,		//�ő�l.
	Start = A,	//�ŏ��̒l.
};

//���͔���.
enum class enInput_Decision {
	Great = 0,		//�f���炵��.
	Good,			//�ǂ�.
	Bad,			//����.

	Max,			//�ő�.
	Start = Great,	//�ŏ�.
};


#endif//#ifndef ENUM_COMMAND_GLOBAL_H.