
#include"GameMng.h"

GameMng::GameMng() {
	
}


void GameMng::init() {
		obj_field.Ini_Roop();
		pause.init();
}

void GameMng::update() {
	if (obj_field.Get_end_flag()) {
		if (Input::AnyKeyClicked() || Gamepad(0).button(PAD::TWO).clicked || Gamepad(0).button(PAD::ONE).clicked || Gamepad(0).button(PAD::THREE).clicked || Gamepad(0).button(PAD::FOUR).clicked || Gamepad(0).button(PAD::START).clicked) {
			SoundAsset(L"BGM_02").stop();
			changeScene(L"Title");
		}
	}
	if (Input::KeyBackspace.clicked || (Gamepad(0).button(PAD::START).clicked&&!XBOX)||(Gamepad(0).button(7).clicked&&XBOX)) {
		SoundAsset(L"ok").playMulti(VOLUME_OK);
		SoundAsset(L"BGM_02").pause();
		pause.pause(0);
	}
	else if (Gamepad(1).button(PAD::START).clicked) {
		SoundAsset(L"ok").playMulti(VOLUME_OK);
		SoundAsset(L"BGM_02").pause();
		pause.pause(1);
	}
	if (!pause.getPauseflag()) {
		obj_field.Update();
	}
	if (pause.update())
	{
		SoundAsset(L"BGM_02").play();
		String s = pause.getSelected();
		if (s == L"タイトルへ") {
			SoundAsset(L"BGM_02").stop();
			changeScene(L"Title");
		}
		else if (s == L"リスタート") {
			SoundAsset(L"BGM_02").stop();
			changeScene(L"Game");
		}
		pause.init();
	}
}

void GameMng::draw()const {
		obj_field.Draw();
		pause.draw();
		
}

void GameMng::End() {
	for (int i = 0; i < PLAYER_ALL_NUMBER; i++) {
		obj_field.End(i);
	}
}