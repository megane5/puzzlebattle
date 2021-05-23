
#include"Field.h"

Field::Field(){
	for (int i = 0; i < PLAYER_ALL_NUMBER; i++) {
		array_obj_player.emplace_back(new Player(i));
	}
	for (int player_num = 0; player_num < PLAYER_ALL_NUMBER; player_num++) {
		for (int i = 0; i < PLAYER_ALL_NUMBER; i++) {
			if (i != player_num)
				array_obj_player[player_num]->Set_enemy(array_obj_player[i]);//対戦相手の設定
		}
	}
	field_font(10);
	count = 0;
}

Field::~Field() {

}

void Field::Ini_Roop() {
	end_flag = false;
	Player::Static_Ini_Roop();
	for (int player_num=0; player_num < PLAYER_ALL_NUMBER; player_num++) {
		array_obj_player[player_num]->Ini_Roop();
	}
}

void Field::Update() {
	Player::StaticUpdate();
	for (int i = 0; i < PLAYER_ALL_NUMBER; i++) {
		array_obj_player[i]->Update();
	}
	for (int i = 0; i < PLAYER_ALL_NUMBER; i++) {//全てのプレイヤーのend_flagがtrueならフィールドのend_flagをtrueにする
		if (array_obj_player[i]->Get_end_flag()) {
			if (i == PLAYER_ALL_NUMBER - 1) {
				end_flag = true;
			}
		}
		else break;
	}
	count++;
}

void Field::Draw()const {
	//背景画面描画
	TextureAsset(L"gameback").resize(1280, 720).drawAt(1280/2,720/2,Alpha(140));
	TextureAsset(L"field").drawAt(50+540/2, 120+540/2);
	TextureAsset(L"field").drawAt(690+540/2, 120+540/2);

	for (int player_num = 0; player_num < PLAYER_ALL_NUMBER; player_num++) {
		array_obj_player[player_num]->Draw();
	}
	if (Player::Get_start_flag()) {
		FontAsset(L"UI")((TIME_MAX - Player::GetCount() + 60 + START_TIME) / 60).drawAt(Window::Width() / 2, 50, Palette::Black);
	}
	else {
		FontAsset(L"UI")(TIME_MAX/60).drawAt(Window::Width() / 2, 50, Palette::Black);
	}

}

void Field::End(int player_num) {
	//array_obj_player[player_num]->obj_block.End();
	//array_obj_player[player_num]->obj_marker.End();

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			Get_Obj_Block(player_num,i,j)->End();
			for (int k = 0; k < 4; k++) {
				Get_Obj_Marker(player_num,i,j,k)->End();
			}
		}
	}
	array_obj_player[player_num]->End();
	//array_obj_player[player_num]->obj_select_marker->End();
}