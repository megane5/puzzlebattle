#include "Title.h"



Title::Title():
	selectnum(2),
	selected(1)
{
	setkey<String>(L"START",L"EXIT");
}

void Title::init()
{
	SoundAsset(L"BGM_01").setLoop(true);
	SoundAsset(L"BGM_01").playMulti();
}

void Title::update()
{
	if (!Gamepad(0).isConnected()) {
		if (Input::KeyZ.clicked) {
			SoundAsset(L"ok").playMulti(VOLUME_OK);
			if (key[selected - 1] == L"START") {

				changeScene(L"Explain");
			}
			else if (key[selected - 1] == L"EXIT") {
				System::Exit();
			}
		}
		if (Input::KeyDown.clicked) {
			SoundAsset(L"select").playMulti(VOLUME_SELECT);
			selected++;
		}
		else if (Input::KeyUp.clicked) {
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
	else {
		if (Gamepad(0).button(PAD::TWO).clicked) {
			SoundAsset(L"ok").playMulti(VOLUME_OK);
			if (key[selected - 1] == L"START") {
				SoundAsset(L"BGM_01").stopMulti();
				changeScene(L"Game");
			}
			else if (key[selected - 1] == L"EXIT") {
				System::Exit();
			}
		}
		if (Gamepad(0).povBackward.clicked) {
			SoundAsset(L"select").playMulti(VOLUME_SELECT);
			selected++;
		}
		else if (Gamepad(0).povForward.clicked) {
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
}

void Title::draw() const
{
	TextureAsset(L"title").draw();
	select<Texture>(selected, Window::Width()/2, 500,TextureAsset(L"start"),TextureAsset(L"end"));
}

