#pragma once

namespace {

	//-----------------------------------------------Player---------------------------------------------------
	//�v���C���[�l��
	const int PLAYER_ALL_NUMBER = 2;


	//-----------------------------------------------Block---------------------------------------------------

	//�u���b�N�̐�
	const int X_BLOCK_MAX = 6;
	const int Y_BLOCK_MAX = 6;

	const int BLOCK_WIDTH = 90;


	//-----------------------------------------------Const---------------------------------------------------

	//�����ϐ�
	typedef enum Direction_t {
		UP, LEFT, DOWN, RIGHT, UP_LEFT, DOWN_LEFT, DOWN_RIGHT, UP_RIGHT, NONE
	}Direction;

	typedef enum Flag_OnOff_t {
		ON, OFF
	}Flag_OnOff;

	enum class Block_Type {
		NORMAL, THUNDER, GETMONEY, HEAL, ALLRESET
	};

	enum class PauseMenu {
		NONE,RESTART,TITLE
	};

	enum PAD {
		ONE, TWO, THREE, FOUR, L1, R1, L2, R2, SELECT, START, L3, R3
	};

	struct Scene {
		int selectnum;
		std::vector<String> key;
	};

	const int DIRECTION_NUM = 8;//�ړ��ł��������


	const int MARKER_COUNT_INI = 1;				//�}�[�J�[�̃J�E���^�̏����l
	const int MARKER_DELETE_TIME = 500;			//�}�[�J�[����������
	const int MARKER_PAR_TIME = 900;				//�}�[�J�[�̖�჎���
	const int BLOCK_APPEAR_TIME = 1200;			//�u���b�N���o�����鎞��
	const int BLOCK_APPEAR_EFFECT_TIME = 50;	//�o���G�t�F�N�g�ɂ����鎞��
	const int BLOCK_DELETE_EFFECT_TIME = 20;	//���ŃG�t�F�N�g�ɂ����鎞��
	const int MONEY_MAX = 50; //���Ă邨���̏��
	const int TIME_MAX = 7200; //��������
	const int HP_MAX = 50;
	const int START_TIME = 120;

	const bool XBOX = true;
	const double VOLUME_OK = 0.5;
	const double VOLUME_SELECT = 0.5;
	const double VOLUME_BACK = 0.6;
}