#pragma once

#include"Field.h"
#include"Const.h"
#include"Pause.h"
#include<HamFramework.hpp>
#include "CommonData.h"

class GameMng :public SceneManager<String, CommonData>::Scene {
public:
	GameMng();

	void init() override;
	void update()override;
	void draw()const override;
	void End();

private:
	Field obj_field;
	Pause pause;
	Font font;
};