
# include <Siv3D.hpp>
#include"GameMng.h"
#include<HamFramework.hpp>
#include"Title.h"
#include"Select.h"
#include"Const.h"
#include"Explain.h"

void Main()
{

	TextureAsset::Register(L"img_button_off", L"graphic/circle_off1.png");
	TextureAsset::Register(L"img_button_on", L"graphic/circle_on1.png");
	TextureAsset::Register(L"img_button_par", L"graphic/par.png");
	TextureAsset::Register(L"img_button_money", L"graphic/circle_money.png"); 
	TextureAsset::Register(L"block1", L"graphic/copper.png");
	TextureAsset::Register(L"block2", L"graphic/silver.png");
	TextureAsset::Register(L"block3", L"graphic/gold.png");
	//TextureAsset::Register(L"block1", L"graphic/block1.png");
	//TextureAsset::Register(L"block2", L"graphic/block2.png");
	//TextureAsset::Register(L"block3", L"graphic/block3.png");
	TextureAsset::Register(L"shutter", L"graphic/shutter.png");
	TextureAsset::Register(L"thunder", L"graphic/thunder.png");
	TextureAsset::Register(L"money", L"graphic/money.png");
	TextureAsset::Register(L"heal", L"graphic/heal.png");
	TextureAsset::Register(L"reset", L"graphic/reset.png");
	TextureAsset::Register(L"chara1", L"graphic/chara1.png");
	TextureAsset::Register(L"chara2", L"graphic/chara2.png");
	TextureAsset::Register(L"hp", L"graphic/hp.png");
	TextureAsset::Register(L"field", L"graphic/field.png");
	TextureAsset::Register(L"gameback", L"graphic/background.png");
	TextureAsset::Register(L"img_button_select", L"graphic/circle_select1.png");
	TextureAsset::Register(L"img_select_circle", L"graphic/select_circle.png");
	TextureAsset::Register(L"title", L"graphic/title1.png");
	TextureAsset::Register(L"start", L"graphic/start.png");
	TextureAsset::Register(L"setting", L"graphic/setting.png");
	TextureAsset::Register(L"end", L"graphic/end.png");
	TextureAsset::Register(L"select", L"graphic/select.png");
	TextureAsset::Register(L"win", L"graphic/win.png");
	TextureAsset::Register(L"lose", L"graphic/lose.png");
	TextureAsset::Register(L"draw", L"graphic/draw.png");
	TextureAsset::Register(L"frame", L"graphic/flame.png");
	TextureAsset::Register(L"effect", L"graphic/effect2.png");
	TextureAsset::Register(L"ex1", L"graphic/図1.png");
	TextureAsset::Register(L"ex2", L"graphic/図2.png");
	TextureAsset::Register(L"start_signal", L"graphic/start_signal.png");

	SoundAsset::Register(L"back", L"sound/back.wav");
	SoundAsset::Register(L"BGM_01", L"sound/BGM_01.wav");
	SoundAsset::Register(L"BGM_02", L"sound/BGM_02.wav");
	SoundAsset::Register(L"break", L"sound/break.wav");
	SoundAsset::Register(L"break2", L"sound/break2.wav");
	SoundAsset::Register(L"heal", L"sound/heal.wav");
	SoundAsset::Register(L"ok", L"sound/ok.wav");
	SoundAsset::Register(L"result1", L"sound/result1.wav");
	SoundAsset::Register(L"result2", L"sound/result2.wav");
	SoundAsset::Register(L"select", L"sound/select.wav");
	SoundAsset::Register(L"thunder", L"sound/thunder.wav");
	SoundAsset::Register(L"whistle", L"sound/whistle.wav");


	FontAsset::Register(L"win", 100,Typeface::Bold, FontStyle::Outline);
	FontAsset(L"win").changeOutlineStyle(TextOutlineStyle(Palette::Black, Palette::Red, 2.0));
	FontAsset::Register(L"lose", 100, Typeface::Bold, FontStyle::Outline);
	FontAsset(L"lose").changeOutlineStyle(TextOutlineStyle(Palette::White, Palette::Blue, 2.0));

	FontAsset::Register(L"UI", 28, Typeface::Bold);
	FontAsset::Register(L"cost", 18, Typeface::Bold);
	FontAsset::Register(L"pause", 30, Typeface::Bold);

	SceneManager<String, CommonData> manager;

	manager.add<Title>(L"Title");
	manager.add<Explain>(L"Explain");
	manager.add<Select>(L"Select");
	manager.add<GameMng>(L"Game");
	//GameMng obj_gamemng;

	const Size targetSize(1280, 720);

	//obj_gamemng.Ini_Roop();

	while (System::Update())
	{
		/*obj_gamemng.Update();
		obj_gamemng.Draw();
		obj_gamemng.End();*/

		Graphics::SetBackground(Palette::White);
		
		manager.updateAndDraw();
		// フルスクリーンモード
		if (!Window::SetFullscreen(true, targetSize))
		{
			System::Exit();
		}
	}
}