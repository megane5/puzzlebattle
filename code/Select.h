#pragma once
#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include "CommonData.h"
class Select:public SceneManager<String, CommonData>::Scene
{
public:
	Select();
	void init() override;
	void update() override;
	void draw() const override;
};

