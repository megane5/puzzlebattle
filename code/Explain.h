#pragma once
#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include "CommonData.h"
#include "Const.h"


class Explain :public SceneManager<String, CommonData>::Scene
{
private:
	std::vector<TextureAsset> ex;
	int slide;
public:
	void draw()const;
	void update();
	void init();
	Explain();
	~Explain();
};

