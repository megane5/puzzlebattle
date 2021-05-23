#pragma once
#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include "CommonData.h"
#include "Const.h"

class Title:public SceneManager<String, CommonData>::Scene
{
private:
	int selectnum;
	int selected;
	std::vector<String> key;
	inline void setkey() {
	}
	template<class First,class... Rest>
	void setkey(First first,Rest... rest) {
		key.push_back(first);
		setkey(rest...);
	}
	
	inline void select(const int selected,const int& x, const int& y) const {
	}
	template<class First, class... Tex>
	void select(const int selected, const int& x, const int& y, const First& first, const Tex&... rest) const{
		if ((selectnum - sizeof...(rest)) == selected) {
			TextureAsset(L"select").draw(x - TextureAsset(L"select").width-first.width/2,y-first.height/2);
			first.drawAt(x, y);
		}
		else {
			first.drawAt(x, y);
		}
		select(selected, x, y + first.height, rest...);
	}
public:
	Title();
	void init() override;
	void update() override;
	void draw() const override;
};

