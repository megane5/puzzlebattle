#pragma once

namespace {

	//-----------------------------------------------Player---------------------------------------------------
	//プレイヤー人数
	const int PLAYER_ALL_NUMBER = 2;


	//-----------------------------------------------Block---------------------------------------------------

	//ブロックの数
	const int X_BLOCK_MAX = 6;
	const int Y_BLOCK_MAX = 6;

	const int BLOCK_WIDTH = 90;


	//-----------------------------------------------Const---------------------------------------------------

	//方向変数
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

	const int DIRECTION_NUM = 8;//移動できる方向数


	const int MARKER_COUNT_INI = 1;				//マーカーのカウンタの初期値
	const int MARKER_DELETE_TIME = 500;			//マーカーを消す時間
	const int MARKER_PAR_TIME = 900;				//マーカーの麻痺時間
	const int BLOCK_APPEAR_TIME = 1200;			//ブロックが出現する時間
	const int BLOCK_APPEAR_EFFECT_TIME = 50;	//出現エフェクトにかかる時間
	const int BLOCK_DELETE_EFFECT_TIME = 20;	//消滅エフェクトにかかる時間
	const int MONEY_MAX = 50; //持てるお金の上限
	const int TIME_MAX = 7200; //制限時間
	const int HP_MAX = 50;
	const int START_TIME = 120;

	const bool XBOX = true;
	const double VOLUME_OK = 0.5;
	const double VOLUME_SELECT = 0.5;
	const double VOLUME_BACK = 0.6;
}