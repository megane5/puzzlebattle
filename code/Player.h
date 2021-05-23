#pragma once

#include<Siv3D.hpp>
#include<vector>
#include<memory>
#include"Block.h"
#include"Marker.h"
#include"Const.h"


class Player {
public:
	Player(int);
	virtual ~Player();

	void Ini_Roop();
	void Update();
	void Draw()const;
	void End();
	static void StaticUpdate();

	void MoveMarker();

	static void Static_Ini_Roop();

	void Damage( int);

	static int GetTimeMs() {
		return GAME_TIME->ms();
	}

	static int GetCount() {
		return count;
	}

	inline int GetHp() {
		return hp;
	}

	inline int GetMoney() {
		return money;
	}

	inline void SetMoney(int money) {
		this->money = money;
	}


	//Block obj_block;
	std::vector<std::vector<std::shared_ptr<Block>>>obj_array_block;		//�u���b�N�C���X�^���X
	//std::shared_ptr<SelectMarker> obj_select_marker;
	std::shared_ptr<Marker> selectedMarker;
	std::shared_ptr<Marker> moneyMarker;
	std::vector<std::shared_ptr<Marker>> ai_gotoMarker;
	std::vector<std::shared_ptr<Marker>> marker;//�v���C���[�̎����Ă���S�Ẵ}�[�J�[
	std::vector<std::shared_ptr<Marker>> notParMarker;//��Ⴢ��ĂȂ��}�[�J�[
	//Marker obj_marker;

	std::vector<bool> button;
	bool decide;//����{�^��

	inline void Set_enemy(std::shared_ptr<Player> ene) {
		enemy = ene;
	}

	inline bool Get_end_flag() {
		return end_flag;
	}

	static inline bool Get_start_flag() {
		return start_flag;
	}

	void ai_Check();
	void ai_RandomMarkerGo();
	void RandomMarkerPar();//�v���C���[�����u���b�N�̃}�[�J�[�������_���ɑI��Ŗ�Ⴢ�����
private:
	static bool start_flag;
	int ai_count;
	static bool end_flag;
	bool resetflag;
	static int count;
	int money;
	int hp;
	const int player_n;
	bool ai,ai_wait,ai_go,ai_gomoney,ai_gosand;
	int ai_speed;//�{�^������������
	bool win, lose,draw;
	static int end_count;//�ǂ��炩���������Ă���̃J�E���g
	Font player_font;
	static std::unique_ptr<Stopwatch> GAME_TIME;//���g�p
	//static Stopwatch game_time;
	std::shared_ptr<Player> enemy;//�ΐ푊��(3�l�ȏ�̑ΐ��z�肵�Ă��Ȃ��̂Ŕz��ɂ��ĂȂ�)
};