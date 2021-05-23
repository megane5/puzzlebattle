#include "Explain.h"



void Explain::draw() const
{
	if(slide<ex.size())
		ex[slide].draw();
}

void Explain::update()
{
	if (Gamepad(0).button(PAD::TWO).clicked || Input::KeyZ.clicked) {
		SoundAsset(L"ok").playMulti(VOLUME_OK);
		if (ex.size() - 1 <= slide) {
			SoundAsset(L"BGM_01").stopMulti();
			changeScene(L"Game");
		} 
		else {
			slide++;
		}
	}
}

void Explain::init()
{
	slide = 0;
}

Explain::Explain()
{
	ex.emplace_back(TextureAsset(L"ex1"));
	ex.emplace_back(TextureAsset(L"ex2"));
}


Explain::~Explain()
{
}
