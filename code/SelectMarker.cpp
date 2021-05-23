
#include"SelectMarker.h"

SelectMarker::SelectMarker(){
	move_direction = 0;
	select_marker = 0;

	Pos_Select.block_x = 0;
	Pos_Select.block_y = 0;
	Pos_Select.direction = Direction::UP;

	sema_font = Font(10);
}

SelectMarker::~SelectMarker() {

}

Direction SelectMarker::Get_KeyDirection(int player_num)
{
		if (player_num == 0) {
			if (Input::KeyUp.clicked && Input::KeyL.pressed) {
				return Direction::UP_LEFT;
			}
			if (Input::KeyDown.clicked && Input::KeyL.pressed) {
				return Direction::DOWN_LEFT;
			}
			if (Input::KeyDown.clicked && Input::KeyR.pressed) {
				return Direction::DOWN_RIGHT;
			}
			if (Input::KeyUp.clicked && Input::KeyR.pressed) {
				return Direction::UP_RIGHT;
			}
			if (Input::KeyUp.clicked) {
				return Direction::UP;
			}
			if (Input::KeyLeft.clicked) {
				return Direction::LEFT;
			}
			if (Input::KeyDown.clicked) {
				return Direction::DOWN;
			}
			if (Input::KeyRight.clicked) {
				return Direction::RIGHT;
			}
		}
		if (player_num == 1) {
			if (Input::KeyW.clicked && Input::KeyL.pressed) {
				return Direction::UP_LEFT;
			}
			if (Input::KeyS.clicked && Input::KeyL.pressed) {
				return Direction::DOWN_LEFT;
			}
			if (Input::KeyS.clicked && Input::KeyR.pressed) {
				return Direction::DOWN_RIGHT;
			}
			if (Input::KeyW.clicked && Input::KeyR.pressed) {
				return Direction::UP_RIGHT;
			}
			if (Input::KeyW.clicked) {
				return Direction::UP;
			}
			if (Input::KeyA.clicked) {
				return Direction::LEFT;
			}
			if (Input::KeyS.clicked) {
				return Direction::DOWN;
			}
			if (Input::KeyD.clicked) {
				return Direction::RIGHT;
			}
		}
		return Direction::NONE;
	
}

void SelectMarker::Ini_Roop() {
		
}

void SelectMarker::Update(int player_num) {
	Move_Select_Marker(player_num);
}

void SelectMarker::Draw(int player_num)const {

	if (player_num == 0) {
		switch (Pos_Select.direction)
		{
		case Direction::UP:
			TextureAsset(L"img_select_circle").drawAt(50 + 90 * Pos_Select.block_x + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2 - 90 / 2);
			break;
		case Direction::LEFT:
			TextureAsset(L"img_select_circle").drawAt(50 + 90 * Pos_Select.block_x + 90 / 2 - 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2);
			break;
		case Direction::DOWN:
			TextureAsset(L"img_select_circle").drawAt(50 + 90 * Pos_Select.block_x + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2 + 90 / 2);
			break;
		case Direction::RIGHT:
			TextureAsset(L"img_select_circle").drawAt(50 + 90 * Pos_Select.block_x + 90 / 2 + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2);
			break;
		default:
			break;
		}
	}
	else if (player_num == 1) {
		switch (Pos_Select.direction)
		{
		case Direction::UP:
			TextureAsset(L"img_select_circle").drawAt(690 + 90 * Pos_Select.block_x + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2 - 90 / 2);
			break;
		case Direction::LEFT:
			TextureAsset(L"img_select_circle").drawAt(690 + 90 * Pos_Select.block_x + 90 / 2 - 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2);
			break;
		case Direction::DOWN:
			TextureAsset(L"img_select_circle").drawAt(690 + 90 * Pos_Select.block_x + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2 + 90 / 2);
			break;
		case Direction::RIGHT:
			TextureAsset(L"img_select_circle").drawAt(690 + 90 * Pos_Select.block_x + 90 / 2 + 90 / 2, 120 + 90 * Pos_Select.block_y + 90 / 2);
			break;
		default:
			break;
		}
	}
	//sema_font(Marker::Get_KeyDirection(0)).draw(750, 200,Palette::Black);
	sema_font(L"block_x", Pos_Select.block_x).draw(750, 230, Palette::Black);
	sema_font(L"block_y", Pos_Select.block_y).draw(750, 260, Palette::Black);
	sema_font(L"direction", Pos_Select.direction).draw(750, 290, Palette::Black);
}

void SelectMarker::End() {

}

void SelectMarker::Move_Select_Marker(int player_num) {
	switch (Get_KeyDirection(player_num))
	{
	case Direction::UP:
		//��ֈړ��\�Ȃ�
		if ((Pos_Select.block_y == 0 && Pos_Select.direction == Direction::DOWN) //��ԏ�̃u���b�N�̉��̃}�[�J�[
			|| Pos_Select.block_y > 0 ) {//��ԏ�ȊO�̃u���b�N
										 //��ԉ���̃u���b�N�͗�O�i�u���b�N�ԍ������̂���
			if ((Pos_Select.block_y == Y_BLOCK_MAX - 1 && Pos_Select.direction == Direction::DOWN)
				||(Pos_Select.block_y == 0 && Pos_Select.direction == Direction::DOWN)) {
				Pos_Select.direction = Direction::UP;
			}
			else {
				Pos_Select.block_y--;
			}
		}
		break;
	case Direction::LEFT:
		if ((Pos_Select.block_x == 0 && Pos_Select.direction == Direction::RIGHT)
			|| Pos_Select.block_x > 0) {
			//��ԍ��E�̃u���b�N�͗�O�i�u���b�N�ԍ������̂���
			if ((Pos_Select.block_x == X_BLOCK_MAX - 1 && Pos_Select.direction == Direction::RIGHT)
				||(Pos_Select.block_x == 0 && Pos_Select.direction == Direction::RIGHT)) {
				Pos_Select.direction = Direction::LEFT;
			}
			else {
				Pos_Select.block_x--;
			}
		}
		break;
	case Direction::DOWN:
		if ((Pos_Select.block_y == Y_BLOCK_MAX - 1 && Pos_Select.direction == Direction::UP)
			|| Pos_Select.block_y < Y_BLOCK_MAX - 1) {
			//��ԏ㉺�̃u���b�N�͗�O�i�u���b�N�ԍ������̂���
			if ((Pos_Select.block_y == 0 && Pos_Select.direction == Direction::UP)
				|| (Pos_Select.block_y == Y_BLOCK_MAX - 1 && Pos_Select.direction == Direction::UP)) {
				Pos_Select.direction = Direction::DOWN;
			}
			else {
				Pos_Select.block_y++;
			}
		}
		break;
	case Direction::RIGHT:
		if ((Pos_Select.block_x == X_BLOCK_MAX - 1 && Pos_Select.direction == Direction::LEFT)
			|| Pos_Select.block_x < X_BLOCK_MAX - 1) {
			//��ԍ��E�̃u���b�N�͗�O�i�u���b�N�ԍ������̂���
			if ((Pos_Select.block_x == 0 && Pos_Select.direction == Direction::LEFT)
				||(Pos_Select.block_x == X_BLOCK_MAX - 1 && Pos_Select.direction == Direction::LEFT)) {
				Pos_Select.direction = Direction::RIGHT;
			}
			else {
				Pos_Select.block_x++;
			}
		}
		break;
	case Direction::UP_LEFT:
		if (!(Pos_Select.block_x == 0 && Pos_Select.direction == Direction::LEFT) 
			&& !(Pos_Select.block_y == 0 && Pos_Select.direction == Direction::UP)) {//��ԍ��ƈ�ԏ�ȊO�͈ړ��\
			switch (Pos_Select.direction)
			{
			case Direction::UP:
				Pos_Select.block_y--;
				Pos_Select.direction = Direction::LEFT;
				break;
			case Direction::LEFT:
				Pos_Select.block_x--;
				Pos_Select.direction = Direction::UP;
				break;
			case Direction::DOWN:
				Pos_Select.direction = Direction::LEFT;
				break;
			case Direction::RIGHT:
				Pos_Select.direction = Direction::UP;
				break;
			default:
				break;
			}
		}
		break;
	case Direction::DOWN_LEFT:
		if (!(Pos_Select.block_y == Y_BLOCK_MAX - 1 && Pos_Select.direction == Direction::DOWN)
			&& !(Pos_Select.block_x == 0 && Pos_Select.direction == Direction::LEFT)) {//��ԉ��ƈ�ԍ��ȊO�͈ړ��\
			switch (Pos_Select.direction)
			{
			case Direction::UP:
				Pos_Select.direction = Direction::LEFT;
				break;
			case Direction::LEFT:
				Pos_Select.block_x--;
				Pos_Select.direction = Direction::DOWN;
				break;
			case Direction::DOWN:
				Pos_Select.block_y++;
				Pos_Select.direction = Direction::LEFT;
				break;
			case Direction::RIGHT:
				Pos_Select.direction = Direction::DOWN;
				break;
			default:
				break;
			}
		}
		break;
	case Direction::DOWN_RIGHT:
		if (!(Pos_Select.block_y == Y_BLOCK_MAX - 1 && Pos_Select.direction == Direction::DOWN)
			&& !(Pos_Select.block_x == X_BLOCK_MAX-1 && Pos_Select.direction == Direction::RIGHT)) {//��ԉ��ƈ�ԉE�ȊO�͈ړ��\
			switch (Pos_Select.direction)
			{
			case Direction::UP:
				Pos_Select.direction = Direction::RIGHT;
				break;
			case Direction::LEFT:
				Pos_Select.direction = Direction::DOWN;
				break;
			case Direction::DOWN:
				Pos_Select.block_y++;
				Pos_Select.direction = Direction::RIGHT;
				break;
			case Direction::RIGHT:
				Pos_Select.block_x++;
				Pos_Select.direction = Direction::DOWN;
				break;
			default:
				break;
			}
		}
		break;
	case Direction::UP_RIGHT:
		if (!(Pos_Select.block_y == 0 && Pos_Select.direction == Direction::UP)
			&& !(Pos_Select.block_x == X_BLOCK_MAX - 1 && Pos_Select.direction == Direction::RIGHT)) {//��ԏ�ƈ�ԉE�ȊO�͈ړ��\
			switch (Pos_Select.direction)
			{
			case Direction::UP:
				Pos_Select.block_y--;
				Pos_Select.direction = Direction::RIGHT;
				break;
			case Direction::LEFT:
				Pos_Select.direction = Direction::UP;
				break;
			case Direction::DOWN:
				Pos_Select.direction = Direction::RIGHT;
				break;
			case Direction::RIGHT:
				Pos_Select.block_x++;
				Pos_Select.direction = Direction::UP;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

bool SelectMarker::Click_Marker(int player_num) {
	if ((Input::KeyZ.clicked&&player_num==0)|| (Input::KeySpace.clicked&&player_num == 1)) {
		//�R�X�g�̏������f
		return true;
	}
	return false;
}
