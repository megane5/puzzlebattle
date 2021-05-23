
#include"Player.h"

bool Player::end_flag = false;
int Player::end_count = 0;
int Player::count = 0;
bool Player::start_flag = false;
std::unique_ptr<Stopwatch> Player::GAME_TIME(new Stopwatch());

Player::Player(int player_num) :
	player_n(player_num)
{
	ai_gotoMarker.resize(2);
	for (int i = 0; i < 6; i++) {
		obj_array_block.emplace_back();
		for (int j = 0; j < 6; j++) {
			obj_array_block[i].emplace_back(new Block(50 + player_num * 640 + BLOCK_WIDTH * i + 90 / 2, 120 + BLOCK_WIDTH * j + 90 / 2));
		}
	}
	for (int i = 0; i < X_BLOCK_MAX; i++) {
		for (int j = 0; j < Y_BLOCK_MAX; j++) {
			for (int k = 0; k < 4; k++) {
				int x, y;
				auto newblock = [&]() {
					bool side = k == Direction::RIGHT || k == Direction::LEFT;
					obj_array_block[i][j]->ResetMarker(k, new Marker(x, y, side));
					marker.emplace_back(obj_array_block[i][j]->GetMarker(k));
					notParMarker.emplace_back(obj_array_block[i][j]->GetMarker(k));
				};
				//同じ位置のマーカーがNULLもしくは存在しないならば新しくMarkerインスタンスを生成
				//NULLでないならそのマーカーを参照させる
				switch (k)
				{
				case Direction::UP:
					if (j > 0) {
						if (obj_array_block[i][j - 1]->GetMarker(Direction::DOWN) != NULL) {
							obj_array_block[i][j]->SetMarker(k, obj_array_block[i][j - 1]->GetMarker(Direction::DOWN));
						}
						else {
							x = 50 + player_num * 640 + 90 * i + 90 / 2;
							y = 120 + 90 * j + 90 / 2 - 90 / 2;
							newblock();
						}
					}
					else {
						x = 50 + player_num * 640 + 90 * i + 90 / 2;
						y = 120 + 90 * j + 90 / 2 - 90 / 2;
						newblock();
					}
					break;
				case Direction::LEFT:
					if (i > 0) {
						if (obj_array_block[i - 1][j]->GetMarker(Direction::RIGHT) != NULL) {
							obj_array_block[i][j]->SetMarker(k, obj_array_block[i - 1][j]->GetMarker(Direction::RIGHT));
						}
						else {
							x = 50 + player_num * 640 + 90 * i + 90 / 2 - 90 / 2;
							y = 120 + 90 * j + 90 / 2;
							newblock();
						}
					}
					else {
						x = 50 + player_num * 640 + 90 * i + 90 / 2 - 90 / 2;
						y = 120 + 90 * j + 90 / 2;
						newblock();
					}

					break;
				case Direction::DOWN:
					if (j < Y_BLOCK_MAX - 1) {
						if (obj_array_block[i][j + 1]->GetMarker(Direction::UP) != NULL) {
							obj_array_block[i][j]->SetMarker(k, obj_array_block[i][j + 1]->GetMarker(Direction::UP));
						}
						else {
							x = 50 + player_num * 640 + 90 * i + 90 / 2;
							y = 120 + 90 * j + 90 / 2 + 90 / 2;
							newblock();
						}
					}
					else {
						x = 50 + player_num * 640 + 90 * i + 90 / 2;
						y = 120 + 90 * j + 90 / 2 + 90 / 2;
						newblock();
					}
					break;
				case Direction::RIGHT:
					if (i < X_BLOCK_MAX - 1) {
						if (obj_array_block[i + 1][j]->GetMarker(Direction::LEFT) != NULL) {
							obj_array_block[i][j]->SetMarker(k, obj_array_block[i + 1][j]->GetMarker(Direction::LEFT));
						}
						else {
							x = 50 + player_num * 640 + 90 * i + 90 / 2 + 90 / 2;
							y = 120 + 90 * j + 90 / 2;
							newblock();
						}
					}
					else {
						x = 50 + player_num * 640 + 90 * i + 90 / 2 + 90 / 2;
						y = 120 + 90 * j + 90 / 2;
						newblock();
					}
					break;
				}
			}
		}
	}



	//next_block_markerとnext_blockの設定
	//next_blockは0に左か上のブロックを、1に右か下のブロックを入れる
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				if ((i == 0 && k == 1) || (j == 0 && k == 0) || (k == 2) || (k == 3)) {
					if (k == 0 || k == 1) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block(1, obj_array_block[i][j]);
					}
					else {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block(0, obj_array_block[i][j]);
					}
					if (k == Direction::DOWN) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP, obj_array_block[i][j]->GetMarker(Direction::UP));
					}
					else if (j - 1 >= 0) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP, obj_array_block[i][j - 1]->GetMarker(k));
					}


					if (k == Direction::RIGHT) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::LEFT, obj_array_block[i][j]->GetMarker(Direction::LEFT));
					}
					else if (i - 1 >= 0) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::LEFT, obj_array_block[i - 1][j]->GetMarker(k));
					}

					if (k == Direction::UP) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN, obj_array_block[i][j]->GetMarker(Direction::DOWN));
					}
					else if (j + 1 < Y_BLOCK_MAX) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN, obj_array_block[i][j + 1]->GetMarker(k));
					}


					if (k == Direction::LEFT) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::RIGHT, obj_array_block[i][j]->GetMarker(Direction::RIGHT));
					}
					else if (i + 1 < X_BLOCK_MAX) {
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::RIGHT, obj_array_block[i + 1][j]->GetMarker(k));
					}
					switch (k)
					{
					case Direction::UP:
						if (j - 1 >= 0) {
							obj_array_block[i][j]->GetMarker(k)->Set_next_block(1, obj_array_block[i][j - 1]);
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_LEFT, obj_array_block[i][j - 1]->GetMarker(Direction::LEFT));
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_RIGHT, obj_array_block[i][j - 1]->GetMarker(Direction::RIGHT));
						}
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_LEFT, obj_array_block[i][j]->GetMarker(Direction::LEFT));
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_RIGHT, obj_array_block[i][j]->GetMarker(Direction::RIGHT));

						break;
					case Direction::LEFT:
						if (i - 1 >= 0) {
							obj_array_block[i][j]->GetMarker(k)->Set_next_block(1, obj_array_block[i - 1][j]);
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_LEFT, obj_array_block[i - 1][j]->GetMarker(Direction::UP));
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_LEFT, obj_array_block[i - 1][j]->GetMarker(Direction::DOWN));
						}
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_RIGHT, obj_array_block[i][j]->GetMarker(Direction::DOWN));
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_RIGHT, obj_array_block[i][j]->GetMarker(Direction::UP));
						break;

					case Direction::DOWN:
						if (j + 1 < Y_BLOCK_MAX) {
							obj_array_block[i][j]->GetMarker(k)->Set_next_block(1, obj_array_block[i][j + 1]);
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_RIGHT, obj_array_block[i][j + 1]->GetMarker(Direction::RIGHT));
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_LEFT, obj_array_block[i][j + 1]->GetMarker(Direction::LEFT));
						}
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_LEFT, obj_array_block[i][j]->GetMarker(Direction::LEFT));
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_RIGHT, obj_array_block[i][j]->GetMarker(Direction::RIGHT));
						break;
					case Direction::RIGHT:
						if (i + 1 < X_BLOCK_MAX) {
							obj_array_block[i][j]->GetMarker(k)->Set_next_block(1, obj_array_block[i + 1][j]);
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_RIGHT, obj_array_block[i + 1][j]->GetMarker(Direction::DOWN));
							obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_RIGHT, obj_array_block[i + 1][j]->GetMarker(Direction::UP));
						}
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::UP_LEFT, obj_array_block[i][j]->GetMarker(Direction::UP));
						obj_array_block[i][j]->GetMarker(k)->Set_next_block_marker(Direction::DOWN_LEFT, obj_array_block[i][j]->GetMarker(Direction::DOWN));
						break;
					}
				}
			}
		}
	}


	button.resize(8);
}

Player::~Player() {

}

void Player::Ini_Roop() {
	//SoundAsset(L"BGM_02").setLoop(true);
	SoundAsset(L"BGM_02").play();
	//初期設定
	for (unsigned int i = 0; i < ai_gotoMarker.size(); i++) {
		ai_gotoMarker[i] = nullptr;
	}
	ai = false;
	if (player_n == 1) {
		ai = true;
	}
	ai_speed = 16;
	hp = HP_MAX;
	money = 15;
	count = 0;
	win = false;
	lose = false;
	draw = false;
	start_flag = false;
	end_flag = false;
	resetflag = false;
	//プレイヤーの持つブロックとマーカーの初期化
	for (int i = 0; i < X_BLOCK_MAX; i++) {
		for (int j = 0; j < Y_BLOCK_MAX; j++) {
			obj_array_block[i][j]->Ini_Roop();
		}
	}
	for (unsigned int i = 0; i < marker.size(); i++) {
		marker[i]->Ini_Roop();
	}

	int rand = Random(0, (int)marker.size() - 1);
	marker[rand]->SetMoney_flag(true);
	moneyMarker = marker[rand];


	obj_array_block[0][0]->GetMarker(0)->Set_selected(true);//選択しているマーカーの初期位置
	selectedMarker = obj_array_block[0][0]->GetMarker(0);
}

void Player::Update() {
	if (!SoundAsset(L"BGM_02").isPlaying()) {
		SoundAsset(L"BGM_02").play();
	}

	if (start_flag) {
		if (!win && !lose && !draw) {
			if (selectedMarker != moneyMarker) {
				if (count % 90 == 0) {
					money++;
				}
			}
			else {
				if (count % 30 == 0) {
					money++;
				}
			}

			if (!ai) {
				if (player_n == 0) {//ボタンの取得
					if (!Gamepad(0).isConnected()) {
						button[Direction::UP] = Input::KeyUp.clicked && !(Input::KeyQ.pressed || Input::KeyE.pressed);
						button[Direction::DOWN] = Input::KeyDown.clicked && !(Input::KeyQ.pressed || Input::KeyE.pressed);
						button[Direction::LEFT] = Input::KeyLeft.clicked;
						button[Direction::RIGHT] = Input::KeyRight.clicked;
						button[Direction::DOWN_RIGHT] = Input::KeyDown.clicked && Input::KeyE.pressed;
						button[Direction::DOWN_LEFT] = Input::KeyDown.clicked && Input::KeyQ.pressed;
						button[Direction::UP_RIGHT] = Input::KeyUp.clicked && Input::KeyE.pressed;
						button[Direction::UP_LEFT] = Input::KeyUp.clicked && Input::KeyQ.pressed;
						decide = Input::KeyZ.clicked;
					}
					else {
						button[Direction::UP] = Gamepad(0).povForward.clicked && !(Gamepad(0).button(PAD::L1).pressed || Gamepad(0).button(PAD::R1).pressed);
						button[Direction::DOWN] = Gamepad(0).povBackward.clicked && !(Gamepad(0).button(PAD::L1).pressed || Gamepad(0).button(PAD::R1).pressed);
						button[Direction::LEFT] = Gamepad(0).povLeft.clicked;
						button[Direction::RIGHT] = Gamepad(0).povRight.clicked;
						button[Direction::DOWN_RIGHT] = Gamepad(0).povBackward.clicked && Gamepad(0).button(PAD::R1).pressed;
						button[Direction::DOWN_LEFT] = Gamepad(0).povBackward.clicked &&  Gamepad(0).button(PAD::L1).pressed;
						button[Direction::UP_RIGHT] = Gamepad(0).povForward.clicked &&  Gamepad(0).button(PAD::R1).pressed;
						button[Direction::UP_LEFT] = Gamepad(0).povForward.clicked &&  Gamepad(0).button(PAD::L1).pressed;
						decide = Gamepad(0).button(PAD::TWO).clicked;
					}
				}
				if (player_n == 1) {
					if (!Gamepad(1).isConnected()) {
						button[Direction::UP] = Input::KeyUp.clicked && !(Input::KeyL.pressed || Input::KeyR.pressed);
						button[Direction::DOWN] = Input::KeyDown.clicked && !(Input::KeyL.pressed || Input::KeyR.pressed);
						button[Direction::LEFT] = Input::KeyLeft.clicked;
						button[Direction::RIGHT] = Input::KeyRight.clicked;
						button[Direction::DOWN_RIGHT] = Input::KeyDown.clicked && Input::KeyR.pressed;
						button[Direction::DOWN_LEFT] = Input::KeyDown.clicked && Input::KeyL.pressed;
						button[Direction::UP_RIGHT] = Input::KeyUp.clicked && Input::KeyR.pressed;
						button[Direction::UP_LEFT] = Input::KeyUp.clicked && Input::KeyL.pressed;
						decide = Input::KeyV.clicked;
					}
					else {
						button[Direction::UP] = Gamepad(1).povForward.clicked && !(Gamepad(1).button(PAD::L1).pressed || Gamepad(1).button(PAD::R1).pressed);
						button[Direction::DOWN] = Gamepad(1).povBackward.clicked && !(Gamepad(1).button(PAD::L1).pressed || Gamepad(1).button(PAD::R1).pressed);
						button[Direction::LEFT] = Gamepad(1).povLeft.clicked;
						button[Direction::RIGHT] = Gamepad(1).povRight.clicked;
						button[Direction::DOWN_RIGHT] = Gamepad(1).povBackward.clicked && Gamepad(1).button(PAD::R1).pressed;
						button[Direction::DOWN_LEFT] = Gamepad(1).povBackward.clicked &&  Gamepad(1).button(PAD::L1).pressed;
						button[Direction::UP_RIGHT] = Gamepad(1).povForward.clicked &&  Gamepad(1).button(PAD::R1).pressed;
						button[Direction::UP_LEFT] = Gamepad(1).povForward.clicked &&  Gamepad(1).button(PAD::L1).pressed;
						decide = Gamepad(1).button(PAD::TWO).clicked;
					}
				}
			}
			else {
				ai_RandomMarkerGo();
				ai_Check();
			}
			MoveMarker();//マーカーを動かす
			if (decide) {//決定ボタンが押された時の処理

				if (money >= selectedMarker->GetCost() && !selectedMarker->Get_marker_flag()) {
					if (selectedMarker->Marker_Click()) {
						SoundAsset(L"ok").playMulti(VOLUME_OK);
						enemy->RandomMarkerPar();
						for (int i = 0; i < 2; i++) {
							std::shared_ptr<Marker> checkMarker = selectedMarker;
							while (true)
							{
								if (checkMarker && checkMarker->Get_next_block(i) && checkMarker->Get_next_block(i)->Get_block_flag() && checkMarker->Get_next_block(i)->BlockDelete()) {//ブロックが消されたときの処理
									switch (checkMarker->Get_next_block(i)->Get_type()) {
									case Block_Type::NORMAL://相手のHPを消したブロックの数字の分だけ減らす
										if (player_n == 0) {
											SoundAsset(L"break").playMulti();
										}
										else if (player_n == 1) {
											SoundAsset(L"break2").playMulti();
										}
										enemy->Damage(checkMarker->Get_next_block(i)->getNum_inblock());
										break;
									case Block_Type::GETMONEY://相手の金の10分の1を盗む
										money += enemy->GetMoney() / 10 + 1;
										enemy->SetMoney(enemy->GetMoney() - (enemy->GetMoney() / 10 + 1));
										break;
									case Block_Type::THUNDER://ランダムな相手のマーカー5～8個を麻痺させる
										SoundAsset(L"thunder").playMulti();
										{
											int parnum = Random(5, 8);
											for (int k = 0; k < parnum; k++) {
												enemy->RandomMarkerPar();
											}
										}
										break;

									case Block_Type::ALLRESET:resetflag = true; break;
									case Block_Type::HEAL://自分のHPを2から3回復
										SoundAsset(L"heal").playMulti();
										hp += Random(2, 3);
										break;
									}
									if (checkMarker->Side()) {
										if (i == 0)
											checkMarker = checkMarker->Get_next_block_marker(Direction::LEFT);
										else
											checkMarker = checkMarker->Get_next_block_marker(Direction::RIGHT);
									}
									else {
										if (i == 0)
											checkMarker = checkMarker->Get_next_block_marker(Direction::UP);
										else
											checkMarker = checkMarker->Get_next_block_marker(Direction::DOWN);
									}
									if (!checkMarker || checkMarker->Get_marker_flag()) {
										break;
									}
								}
								else {
									break;
								}
							}
						}
						if (selectedMarker->GetMoney_flag()) {
							selectedMarker->SetMoney_flag(false);
							int rand = Random(0, (int)marker.size() - 1);
							marker[rand]->SetMoney_flag(true);
							moneyMarker = marker[rand];
						}
						for (int i = 0; i < (int)notParMarker.size(); i++) {
							if (notParMarker[i] == selectedMarker) {
								notParMarker.erase(notParMarker.begin() + i);
								break;
							}
						}

						money -= selectedMarker->GetCost();
					}
					else {
						SoundAsset(L"back").playMulti(VOLUME_BACK);
					}
				}
				else {
					SoundAsset(L"back").playMulti(VOLUME_BACK);
				}
			}
			if (ai) {
				for (int i = 0; i < DIRECTION_NUM; i++) {
					button[i] = false;
				}
				decide = false;
			}

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if (obj_array_block[i][j]->DeleteUpdate()) {

					}
					if (obj_array_block[i][j]->AppearUpdate(BLOCK_APPEAR_TIME)) {
						//ブロックが出現したときの処理

					}
				}
			}
			if (resetflag) {
				for (int x = 0; x < X_BLOCK_MAX; x++) {
					for (int y = 0; y < Y_BLOCK_MAX; y++) {
						obj_array_block[x][y]->SetBlock();
						obj_array_block[x][y]->Appear();
					}
				}
				for (unsigned int k = 0; k < marker.size(); k++) {
					marker[k]->Set_marker_flag(false);
				}
				resetflag = false;
			}
			for (unsigned int i = 0; i < marker.size(); i++) {
				if (marker[i]->ParUpdate(MARKER_PAR_TIME)) {
					//マーカーの麻痺が治ったときの処理
					notParMarker.emplace_back(marker[i]);
				}
				if (marker[i]->MarkerUpdate(MARKER_DELETE_TIME)) {
					//マーカーのフラグがオフになったときの処理
					notParMarker.emplace_back(marker[i]);
				}
			}

			if (money > MONEY_MAX) {
				money = MONEY_MAX;
			}
			if (hp > HP_MAX) {
				hp = HP_MAX;
			}

			if (TIME_MAX - count +START_TIME< 0) {
				if (!SoundAsset(L"whistle").isPlaying())
					SoundAsset(L"whistle").playMulti();
				if (enemy->GetHp() == hp) {
					draw = true;
				}
				else if (enemy->GetHp() > hp) {
					lose = true;
				}
				else {
					win = true;
				}
				end_flag = true;
				if (!GAME_TIME->isPaused()) {
					GAME_TIME->pause();
				}
			}


			if (enemy->GetHp() <= 0) {
				win = true;
				end_flag = true;
				if (GAME_TIME->isActive()) {
					GAME_TIME->pause();
				}
			}
			if (hp <= 0) {
				lose = true;
				end_flag = true;
				if (GAME_TIME->isActive()) {
					GAME_TIME->pause();
				}
			}
		}
	}

}


void Player::Draw()const {
	int start_x = 0 + Window::Width() / 2 * player_n;

	//TextureAsset(L"frame").draw(start_x + 10, 80);
	//自分の持つブロックとマーカーの描写
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj_array_block[i][j]->Draw();
		}
	}
	TextureAsset(L"frame").draw(start_x+20, 90);
	for (unsigned int i = 0; i < marker.size(); i++) {
		marker[i]->Draw();
	}

	Texture drawTex;
	if (player_n == 0) {
		drawTex = TextureAsset(L"chara1");
	}
	else if (player_n == 1) {
		drawTex = TextureAsset(L"chara2");
	}


	drawTex.drawAt(start_x + 100, 50);

	for (int i = 0; i < hp; i++) {
		TextureAsset(L"hp").scale(2).drawAt(start_x + 70 + 10 * i, 680);
	}
	FontAsset(L"UI")(L"HP:", hp, L"/50 金:", money, L"/50").draw(start_x + 170, 20, Palette::Black);

	//デバッグ用
	/*if (!ai_gotoMarker[0]  && ai) {
		player_font(L"0null").draw(start_x + 170, 40, Palette::Black);
	}
	if (!ai_gotoMarker[1] && ai) {
		player_font(L"1null").draw(start_x + 250, 40, Palette::Black);
	}
	if (ai_wait&&ai) {
		player_font(L"wait").draw(start_x + 330, 40, Palette::Black);
	}*/

	if (end_flag) {
		if (draw) {
			TextureAsset(L"draw").drawAt(start_x + Window::Width() / 4, Window::Height() / 2);

		}
		if (win) {
			TextureAsset(L"win").drawAt(start_x + Window::Width() / 4, Window::Height() / 2);
		}
		if (lose) {
			TextureAsset(L"lose").drawAt(start_x + Window::Width() / 4, Window::Height() / 2);
		}

	}
	if (start_flag && count - START_TIME < 60) {
		TextureAsset(L"start_signal").drawAt(Window::Width() / 2, Window::Height() / 2,Alpha(255 - (count - START_TIME) * 4));
	}
}

void Player::End() {

}

void Player::StaticUpdate()
{
	if (end_flag) {
		if (end_count == 30) {
			SoundAsset(L"result1").play();
		}
		end_count++;
	}
	else {
		count++;
	}
	if (!start_flag && count > START_TIME) {
		start_flag = true;
		SoundAsset(L"whistle").playMulti();
	}
}

void Player::MoveMarker()
{
	for (int i = 0; i < 8; i++) {
		if (button[i] && selectedMarker->Get_next_block_marker(i) != NULL) {
			SoundAsset(L"select").playMulti(VOLUME_SELECT);
			selectedMarker->Set_selected(false);
			selectedMarker = selectedMarker->Get_next_block_marker(i);
			selectedMarker->Set_selected(true);
			break;
		}

	}

}

void Player::Static_Ini_Roop()
{
	GAME_TIME->restart();
	end_count = 0;
	end_flag = false;
	count = 0;
}

void Player::Damage(int damage)
{
	hp -= damage;
}


void Player::ai_Check()
{
	int index = -1;
	if (ai_gotoMarker[0]) {
		if (!ai_wait && !ai_gomoney && (ai_gotoMarker[0]->GetPar_flag())) {
			ai_gotoMarker[0] = nullptr;
			ai_gotoMarker[1] = nullptr;
			ai_count = 0;
		}
	}
	if (ai_gotoMarker[1]) {
		if (!ai_wait && !ai_gomoney && (ai_gotoMarker[1]->GetPar_flag())) {
			ai_gotoMarker[0] = nullptr;
			ai_gotoMarker[1] = nullptr;
			ai_count = 0;
		}
	}
	if (ai_gotoMarker[0] && ai_gotoMarker[1]) {
			index = std::abs(selectedMarker->GetX() - ai_gotoMarker[0]->GetX()) + std::abs(selectedMarker->GetY() - ai_gotoMarker[0]->GetY()) <
				std::abs(selectedMarker->GetX() - ai_gotoMarker[1]->GetX()) + std::abs(selectedMarker->GetY() - ai_gotoMarker[1]->GetY()) ? 0 : 1;
	}
	else if(ai_gotoMarker[0]) {
		index = 0;
	}
	else if (ai_gotoMarker[1]) {
		index = 1;
	}
	if (index >= 0) {
		if (ai_gotoMarker[index] == selectedMarker) {
			if (!ai_gomoney) {
				ai_count++;
				if (ai_count > ai_speed) {
					decide = true;
					/*std::vector<int> list;
					if (selectedMarker->Side()) {
						list.emplace_back(Direction::RIGHT);
						list.emplace_back(Direction::LEFT);
					}
					else {
						list.emplace_back(Direction::UP);
						list.emplace_back(Direction::DOWN);
					}
					while (true) {

						int rand = Random(0, (int)list.size() - 1);
						int dir = list[rand];
						if (selectedMarker->Get_next_block_marker(dir) != NULL && selectedMarker->GetCost() < money) {
							if (!selectedMarker->Get_next_block_marker(dir)->GetPar_flag()) {
								ai_gotoMarker = selectedMarker->Get_next_block_marker(dir);
								break;
							}
							else {
								list.erase(list.begin() + rand);
								if (list.size() == 0) {
									ai_gosand = false;
									break;
								}
							}
						}
						else {
							list.erase(list.begin() + rand);
							if (list.size() == 0) {
								ai_gosand = false;
								break;
							}
						}
					}*/
					ai_count = 0;
					ai_gotoMarker[index] = nullptr;
				}
			}
			else if (ai_gomoney) {
				ai_wait = true;
				ai_gomoney = false;
				ai_gotoMarker[index] = nullptr;
			}
		}
		else {
			if (ai_count == ai_speed) {
				for (int i = 0; i < DIRECTION_NUM; i++) {
					if (selectedMarker->Get_next_block_marker(i) == ai_gotoMarker[index]) {
						button[i] = true;
						break;

					}
				}
				bool goside = ai_gotoMarker[index]->GetY() == selectedMarker->GetY();
				bool golength = ai_gotoMarker[index]->GetX() == selectedMarker->GetX();
				bool goright = ai_gotoMarker[index]->GetX() > selectedMarker->GetX();
				bool godown = ai_gotoMarker[index]->GetY() > selectedMarker->GetY();
				if (goside) {
					if (goright) {
						button[Direction::RIGHT] = true;
					}
					else {
						button[Direction::LEFT] = true;
					}
				}
				else if (golength) {
					if (godown) {
						button[Direction::DOWN] = true;
					}
					else {
						button[Direction::UP] = true;
					}
				}
				else {
					if (goright) {
						if (godown) {
							button[Direction::DOWN_RIGHT] = true;
						}
						else {
							button[Direction::UP_RIGHT] = true;
						}
					}
					else {
						if (godown) {
							button[Direction::DOWN_LEFT] = true;
						}
						else {
							button[Direction::UP_LEFT] = true;
						}
					}
				}
				ai_count = 0;
			}
			ai_count++;
		}
	}
	else if (index == -1) {
		if (ai_wait) {
			if (money > 8) {
				ai_wait = false;
			}
		}
	}
}

void Player::ai_RandomMarkerGo()
{
	if (!ai_gotoMarker[0]&&!ai_gotoMarker[1]&&!ai_wait) {
		double value = -1;

		if (money < 4) {
			ai_gotoMarker[0] = moneyMarker;
			ai_gomoney = true;
		}
		else {
			for (int i = 0; i < X_BLOCK_MAX; i++) {
				for (int j = 0; j < Y_BLOCK_MAX; j++) {
					if (obj_array_block[i][j]->Get_block_flag()) {
						double value1=0, value2=0;
						double lMoney = obj_array_block[i][j]->GetMarker(Direction::UP)->GetCost() + obj_array_block[i][j]->GetMarker(Direction::DOWN)->GetCost();
						double sMoney = obj_array_block[i][j]->GetMarker(Direction::RIGHT)->GetCost() + obj_array_block[i][j]->GetMarker(Direction::LEFT)->GetCost();
						double distance[4];
						for (int k = 0; k < 4; k++) {
							distance[k]= std::abs(selectedMarker->GetX() - obj_array_block[i][j]->GetMarker(k)->GetX()) + std::abs(selectedMarker->GetY() - obj_array_block[i][j]->GetMarker(k)->GetY());
						}
						

						double time[4];
						for (int k = 0; k < 4; k++) {
							time[k] = distance[k] / BLOCK_WIDTH *ai_speed;
						}
						double lTime = (distance[Direction::UP] > distance[Direction::DOWN] ? time[Direction::DOWN]: time[Direction::UP]) + 3 *ai_speed;
						double sTime = (distance[Direction::LEFT] > distance[Direction::RIGHT] ?time[Direction::RIGHT] : time[Direction::LEFT]) + 3*ai_speed;
						bool mon[4];//マーカーフラグがたっていて、そこへ行くまでにフラグがオフにならないならtrue
						for (int k = 0; k < 4; k++) {
							mon[k] = false;
						}
						//片方のマーカーがオンだった場合の処理
						//時間関係で適当なので、改良も必要
						//両方のマーカーがオンの場合は考えていないので必要であればつけたす
						for (int k = 0; k < 4; k++) {
							if (obj_array_block[i][j]->GetMarker(k)->Get_marker_flag() && (MARKER_DELETE_TIME - obj_array_block[i][j]->GetMarker(k)->GetCount_false()) > (time[k] + ai_speed)) {
								mon[k] = true;
								if (k == Direction::UP || k == Direction::DOWN) {
									lMoney -= obj_array_block[i][j]->GetMarker(k)->GetCost();
									lTime = time[(k + 2) % 4]  + ai_speed;
								}
								else {
									sMoney -= obj_array_block[i][j]->GetMarker(k)->GetCost();
									sTime = time[(k + 2) % 4] + ai_speed;
								}
							}
						}
						switch (obj_array_block[i][j]->Get_type()) {
						case Block_Type::NORMAL:
							value1 = (obj_array_block[i][j]->getNum_inblock() > enemy->GetHp() ? obj_array_block[i][j]->getNum_inblock() / (lMoney + lTime / 80 * 3) : enemy->GetHp()) / (lMoney + lTime / 80 * 3);
							value2 = (obj_array_block[i][j]->getNum_inblock() > enemy->GetHp() ? obj_array_block[i][j]->getNum_inblock() / (sMoney + sTime / 80 * 3) : enemy->GetHp()) / (sMoney + sTime / 80 * 3);
							break;
						case Block_Type::HEAL:
							if (HP_MAX - hp > 3) {
								value1 = 2.5 / (lMoney + lTime / 80 * 3);
								value2 = 2.5 / (sMoney + sTime / 80 * 3);;
							}
							else {
								value1 = (HP_MAX - hp) / (lMoney + lTime / 80 * 3);
								value2 = (HP_MAX - hp) / (sMoney + sTime / 80 * 3);;
							}
							break;
						case Block_Type::GETMONEY://3金で1点分と考える
							value1 = (enemy->GetMoney() / 10 + 1) * 2 / 3 / (lMoney + lTime / 80 * 3);
							value2 = (enemy->GetMoney() / 10 + 1) * 2 / 3 / (sMoney + sTime / 80 * 3);
							break;
						case Block_Type::ALLRESET:break;//また考える
						case Block_Type::THUNDER:
							value1 = 1 / (lMoney + lTime / 80 * 3);
							value2 = 1 / (sMoney + sTime / 80 * 3);
							break;
						}
						if (obj_array_block[i][j]->GetMarker(Direction::UP)->GetPar_flag() || obj_array_block[i][j]->GetMarker(Direction::DOWN)->GetPar_flag()) {
							value1 = 0;
						}
						else if (obj_array_block[i][j]->GetMarker(Direction::LEFT)->GetPar_flag() || obj_array_block[i][j]->GetMarker(Direction::RIGHT)->GetPar_flag()) {
							value2 = 0;
						}

						if (value1 > value) {
							value = value1;
							ai_gotoMarker[0] = !mon[Direction::UP] ? obj_array_block[i][j]->GetMarker(Direction::UP) : nullptr;
							ai_gotoMarker[1] = !mon[Direction::DOWN] ? obj_array_block[i][j]->GetMarker(Direction::DOWN) : nullptr;
						}
						else if (value2 > value) {
							value = value2;
							ai_gotoMarker[0] = !mon[Direction::LEFT] ? obj_array_block[i][j]->GetMarker(Direction::LEFT) : nullptr;
							ai_gotoMarker[1] = !mon[Direction::RIGHT] ? obj_array_block[i][j]->GetMarker(Direction::RIGHT) : nullptr;
						}
						break;
					}
				}
			}
		}
		/*else if (notParMarker.size() > 0) {
			int rand = Random(0, (int)notParMarker.size() - 1);
			ai_gotoMarker = notParMarker[rand];
			ai_go = true;
		}*/
	}
}

void Player::RandomMarkerPar()
{
	if (notParMarker.size() > 0) {
		int rand = Random(0, (int)notParMarker.size() - 1);
		notParMarker[rand]->Par();
		notParMarker.erase(notParMarker.begin() + rand);
	}
}
