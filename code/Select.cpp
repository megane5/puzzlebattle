#include "Select.h"



Select::Select()
{
}

void Select::init()
{
}

void Select::update()
{
	if (Input::KeyZ.clicked) {
		changeScene(L"Game");
	}
}

void Select::draw() const
{

	m_data->font(L"キャラクターセレクト画面").drawCenter(Window::Center());
}

