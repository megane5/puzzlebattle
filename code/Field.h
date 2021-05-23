#pragma once

#include<Siv3D.hpp>
#include<vector>
#include<memory>

#include"Const.h"
#include"Player.h"

class Field {
public:
	Field();
	virtual ~Field();

	void Ini_Roop();
	void Update();
	void Draw()const;
	void End(int);

	inline std::shared_ptr<Marker>& Get_Obj_Marker(int player_num, int block_x, int block_y, int direction_t) {
		return array_obj_player.at(player_num)->obj_array_block.at(block_x).at(block_y)->GetMarker(direction_t);
	}


	inline std::shared_ptr<Block>& Get_Obj_Block(int player_num, int block_x, int block_y) {
		return array_obj_player[player_num]->obj_array_block[block_x][block_y];
	}

	inline bool Get_end_flag() {
		return end_flag;
	}
private:
	bool end_flag;
	std::vector<std::shared_ptr<Player>>array_obj_player;	//プレイヤーインスタンス

	//プレイヤーナンバー
	typedef enum NUM_t {
		PLAYER1, PLAYER2
	}NUM;

	Font field_font;		//デバッグフォント

	int count;			//カウンタ
};