#include "Pause.h"



void Pause::draw() const
{
	if (pauseflag) {
		back.draw(Color(200, 20, 20, 100));
		select<String>(selected, Window::Width() / 2, Window::Height() / 4 + 30, L"続ける", L"リスタート", L"タイトルへ", L"ゲームを終える");
	}
}

void Pause::init()
{
	player = 0;
	pauseflag = false;
	selected = 1;
}

bool Pause::update()
{
	if (pauseflag) {
		if (Input::KeyZ.clicked || Gamepad(player).button(PAD::TWO).clicked) {
			SoundAsset(L"ok").pauseMulti();
			/*if (key[selected - 1] == L"続ける") {
			}
			else if (key[selected - 1] == L"リスタート") {
			}
			else if (key[selected - 1] == L"タイトルへ") {
			}*/
			if (key[selected - 1] == L"ゲームを終える") {
				System::Exit();
			}
			return true;
		}
		if (Input::KeyX.clicked || Gamepad(player).button(PAD::THREE).clicked) {
			SoundAsset(L"back").playMulti(VOLUME_BACK);
			selected = 1;
			return true;
		}
		//Pause関係でめんどくさいのでストップウォッチでなくカウントを使う
		if (Input::KeyDown.clicked || Gamepad(player).povBackward.clicked) {
			SoundAsset(L"select").playMulti(VOLUME_SELECT);
			selected++;
		}
		else if (Input::KeyUp.clicked || Gamepad(player).povForward.clicked) {
			SoundAsset(L"select").playMulti(VOLUME_SELECT);
			selected--;
		}
		if (selected > selectnum) {
			selected = 1;
		}
		if (selected < 1) {
			selected = selectnum;
		}
	}
	return false;
}


Pause::Pause():selectnum(4),selected(1),pauseflag(false),back(Window::Width()/2-400,Window::Height()/4-30,800,Window::Height()/2+60,10)
{
	setkey<String>(L"続ける", L"リスタート", L"タイトルへ",L"ゲームを終える");
}

