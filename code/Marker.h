#pragma once

#include<Siv3D.hpp>
#include<vector>
#include<memory>
#include"Const.h"

#include"Block.h"
class Block;

class Marker {
public:
	Marker(int, int,bool);
	virtual ~Marker();

	void Ini_Roop();
	void Update();
	void Draw() const;		//マーカー全部を描画
	//void Draw(Marker&,int,int, int, int);		//ブロックの上下左右を描画　未使用
	void End();

	inline bool Get_marker_flag(Marker& obj_m) {
		return obj_m.marker_flag;
	}
	inline bool Get_marker_flag() {
		return marker_flag;
	}

	inline void Set_selected(bool b) {
		selected = b;
	}

	inline void SetMoney_flag(bool flag) {
		money_flag = flag;
	}
	inline bool GetMoney_flag(){
		return money_flag;
	}

	bool Marker_Click(); 
	inline void Set_marker_flag(bool flag) {
		marker_flag = flag;
	}
	bool MarkerUpdate(int);					//マーカーを時間などで false に戻す
	bool ParUpdate(int);		

	void Par() {
		par_flag = true;
		marker_flag = false;
		count_false = 0;
	};

	int GetCost() const;
	inline int GetSimpleCost() const{
		return (next_block[0] != NULL&&next_block[0]->Get_block_flag() ? next_block[0]->getNum_inblock() : 0)
			+ (next_block[1] != NULL&&next_block[1]->Get_block_flag() ? next_block[1]->getNum_inblock() : 0);
	}
	inline void Set_next_block_marker(unsigned int i,std::shared_ptr<Marker> m) {
		if (i >= 0 && i < next_block_marker.size())
			next_block_marker[i] = m;
	}
	inline std::shared_ptr<Marker> Get_next_block_marker(int i) {
		return next_block_marker[i];	
	}
	inline std::shared_ptr<Block> Get_next_block(int i) {
		return next_block[i];
	}
	inline void Set_next_block(unsigned int i, std::shared_ptr<Block> b) {
		if (i >= 0 && i < next_block.size())
			next_block[i] = b;
	}
	inline int GetX(){
		return x;
	}
	inline int GetY() {
		return y;
	}
	inline bool GetPar_flag() {
		return par_flag;
	}
	inline int GetCount_false() {
		return count_false;
	}
	inline bool Side() {
		return side;
	}
private:
	std::vector<std::shared_ptr<Block>>next_block;//隣のブロックのポインタ
	std::vector<std::shared_ptr<Marker>>next_block_marker;//隣のマーカーのポインタ

	bool marker_flag;		//マーカーのON,OFF
	bool par_flag; //マーカーが麻痺してるかどうか
	bool money_flag;
	const bool side;

	int count_false;		//カウンタもマーカーごとに管理
	int count_par;	//麻痺してからの時間

	bool selected; //選択されているならtrue

	int x, y;//表示する座標

	//マーカーの状態
	typedef enum Button_Num_t{
		Off,On
	}Button_Num;

public:
	int debug_count;
};