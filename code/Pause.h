#pragma once
#include<Siv3D.hpp>
#include"Const.h"

class Pause
{
private:
	const RoundRect back;
	const int selectnum;
	int selected;
	int player;
	bool pauseflag;
	std::vector<String> key;
	inline void setkey() {
	}
	template<class First, class... Rest>
	void setkey(First first, Rest... rest) {
		key.push_back(first);
		setkey(rest...);
	}

	inline void select(const int selected, const int& x, const int& y) const {
	}
	template<class First, class... Tex>
	void select(const int selected, const int& x, const int& y, const First& first, const Tex&... rest) const {
		if ((selectnum - sizeof...(rest)) == selected) {
			FontAsset(L"pause")(first).drawAt(x, y,Palette::Red);
		}
		else {
			FontAsset(L"pause")(first).drawAt(x, y);
		}
		select(selected, x, y + FontAsset(L"pause").height + 30, rest...);
	}
public:
	void draw() const;
	void init();
	inline void pause(int p){
		pauseflag = true;
		player = p;
	}
	inline bool getPauseflag() {
		return pauseflag;
	}
	inline String getSelected() {
		return key[selected - 1];
	};
	bool update();
	Pause();
};

