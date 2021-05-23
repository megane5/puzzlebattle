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
	std::vector<std::vector<std::shared_ptr<Block>>>obj_array_block;		//ブロックインスタンス
	//std::shared_ptr<SelectMarker> obj_select_marker;
	std::shared_ptr<Marker> selectedMarker;
	std::shared_ptr<Marker> moneyMarker;
	std::vector<std::shared_ptr<Marker>> ai_gotoMarker;
	std::vector<std::shared_ptr<Marker>> marker;//プレイヤーの持っている全てのマーカー
	std::vector<std::shared_ptr<Marker>> notParMarker;//麻痺してないマーカー
	//Marker obj_marker;

	std::vector<bool> button;
	bool decide;//決定ボタン

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
	void RandomMarkerPar();//プレイヤーが持つブロックのマーカーをランダムに選んで麻痺させる
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
	int ai_speed;//ボタンを押す時間
	bool win, lose,draw;
	static int end_count;//どちらかが勝利してからのカウント
	Font player_font;
	static std::unique_ptr<Stopwatch> GAME_TIME;//未使用
	//static Stopwatch game_time;
	std::shared_ptr<Player> enemy;//対戦相手(3人以上の対戦を想定していないので配列にしてない)
};