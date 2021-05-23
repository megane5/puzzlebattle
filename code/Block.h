#pragma once

#include<Siv3D.hpp>
#include<vector>
#include<memory>
#include "const.h"
class Marker;

class Block {
public:
	Block(int, int);
	virtual ~Block();

	void Ini_Roop();
	void Update();//���g�p
	void Draw()const;			
	void End();
	void SetBlock();
	bool DeleteUpdate();		//���܂ꂽ�����,�������Ƃ�true��Ԃ�
	bool AppearUpdate(int);		//�����Ă����莞�Ԍo������Ăяo��������,�o�������Ƃ�true��Ԃ�
	inline int getNum_inblock() {
		return num_inblock;
	};

	bool BlockDelete();

	bool Get_block_flag() {
		return block_flag;
	}

	Block_Type Get_type() {
		return type;
	}
	void ResetMarker(unsigned int d,Marker* m) {
		if (d < array_block_marker.size() && d>=0) {
			array_block_marker[d].reset(m);
		}
	}

	void SetMarker(unsigned int d, std::shared_ptr<Marker> m) {
		if (d < array_block_marker.size() && d >= 0) {
			array_block_marker[d] = m;
		}
	}

	bool Sanded();

	std::shared_ptr<Marker>& GetMarker(unsigned int d) {
		return array_block_marker[d];
	}

	/*inline int getCost(bool side) {
		if (side) {
			return array_block_marker[Direction::LEFT]->GetSimpleCost() + array_block_marker[Direction::RIGHT]->GetSimpleCost();
		}
		return  array_block_marker[Direction::UP]->GetSimpleCost() + array_block_marker[Direction::DOWN]->GetSimpleCost();
	}*/

	void Appear();
private:
	Texture drawTex;
	Rect BlockRect;
	Block_Type type;
	int num_inblock;	//�u���b�N���̗v�f�ϐ�
	bool block_flag;
	int count_false;
	int x, y;//�\��������W
	//�u���b�N���Ƃ̃}�[�J�[�i��Ɏl��
	std::vector<std::shared_ptr<Marker>>array_block_marker;
	int count_true;

};