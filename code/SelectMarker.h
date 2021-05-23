#pragma once
#include <memory>

#include"Marker.h"


class SelectMarker {
private:	
	//�Z���N�g�}�[�J�[�̈ʒu��\���ϐ�
	typedef struct PosMark_t {
		int block_x;
		int block_y;
		int direction;
	}PosMark;

	std::shared_ptr<Marker> marker;
public:
	SelectMarker();
	virtual ~SelectMarker();
	Direction Get_KeyDirection(int);
	void Ini_Roop();
	void Update(int);
	void Draw(int)const;
	void End();

	void Move_Select_Marker(int);
	static bool Click_Marker(int);				//�}�[�J�[��ON,OFF
	inline void Set_marker(std::shared_ptr<Marker> m) {
		marker->Set_selected(false);
		marker = m;
		marker->Set_selected(true);
	}

	inline PosMark& Get_Select_Pos() {
		return Pos_Select;
	}

private:

	int move_direction;		//�}�[�J�[�̈ړ�����
	int select_marker;		//�}�[�J�[�̌��݈ʒu

	PosMark Pos_Select;

	Font sema_font;
};