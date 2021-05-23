
#include"Block.h"
#include"Marker.h"

Block::Block(int x,int y) :x(x),y(y),BlockRect(x-45,y-45,90,90){
	for (int i = 0; i < 4; i++) {
		array_block_marker.emplace_back(nullptr);
	}
	SetBlock();
}

Block::~Block() {

}

void Block::Ini_Roop() {
	block_flag = true;
	count_false = 0;
	count_true = BLOCK_APPEAR_EFFECT_TIME;
}

void Block::Update() {//ブロック消去時trueを返す
	/*
	//ブロック消去
	if ((array_block_marker[0].Get_marker_flag() && array_block_marker[2].Get_marker_flag()) || (array_block_marker[1].Get_marker_flag() && array_block_marker[3].Get_marker_flag()))
	{
		if(Delete())
			return true;
	}
	//ブロック内情報処理

	//ブロック戻ってくるエフェクトなど処理

	//ブロック復活
	if (!block_flag) {
		count_false++;
	}
	if (count_false > 600) {
		count_false = 0;
		Appear();
	}
	*/
}

void Block::Draw()const {


	/*if (block_flag && count_true < BLOCK_APPEAR_EFFECT_TIME) {//出現エフェクト
		if (count_true % 20 > 10) {
			drawTex.drawAt(x, y);
		}
		//TextureAsset(L"shutter").drawAt(x, y);
	}*/
	if(block_flag)
		drawTex.drawAt(x, y);
	
	else {
		if (count_false < BLOCK_DELETE_EFFECT_TIME) {
			int i=0, j=0;
			for (j; count_false > BLOCK_DELETE_EFFECT_TIME * (j + 1) / 4 && j < 4; j++) {

			}
			for (i; count_false - BLOCK_DELETE_EFFECT_TIME * j / 4 > BLOCK_DELETE_EFFECT_TIME * (i + 1) / 16 && i < 4; i++) {

			}
			TextureAsset(L"effect")(200 * i, 200 * j, 200, 200).drawAt(x, y);
			//TextureAsset(L"shutter").drawAt(x, y);
		}
		else {//ブロックを暗くする
			drawTex.drawAt(x, y);
			BlockRect.draw(Color(0, 0, 0, 100));
			int w = TextureAsset(L"shutter").width;
			int h = TextureAsset(L"shutter").height;
			TextureAsset(L"shutter")(0, h-h*(BLOCK_APPEAR_TIME - count_false + BLOCK_DELETE_EFFECT_TIME) / BLOCK_APPEAR_TIME, w, h * (BLOCK_APPEAR_TIME - count_false + BLOCK_DELETE_EFFECT_TIME) / BLOCK_APPEAR_TIME).draw(x - w / 2, y - h / 2);
		}
		/*if (!block_flag && count_false < BLOCK_DELETE_EFFECT_TIME) {//消滅エフェクト
			if (count_false % 20 > 10) {
				drawTex.drawAt(x, y);
			}
			//TextureAsset(L"shutter").drawAt(x, y);
		}*/
	}
}



void Block::End() {

}

void Block::SetBlock()
{
	double rand = Random(0.0, 100.0);
	if (rand <= 90) {
		type = Block_Type::NORMAL;
	}
	else if (rand <= 92) {
		type = Block_Type::GETMONEY;
		drawTex = TextureAsset(L"money"); 
	}
	else if (rand <= 95) {
		type = Block_Type::HEAL;
		drawTex = TextureAsset(L"heal");
	}
	else if (rand <= 96) {
		type = Block_Type::ALLRESET;
		drawTex = TextureAsset(L"reset");
	}
	else {
		type = Block_Type::THUNDER;
		drawTex = TextureAsset(L"thunder");
	}
	if (type == Block_Type::NORMAL) {
		num_inblock = Random(1, 3);
		switch (num_inblock)
		{
		case 1:drawTex = TextureAsset(L"block1"); break;
		case 2:drawTex = TextureAsset(L"block2"); break;
		case 3:drawTex = TextureAsset(L"block3"); break;
		}
	}
	else {
		num_inblock = 0;
	}
}


bool Block::DeleteUpdate() {
	if (block_flag) {
		count_true++;
	}
	return false;
}


bool Block::AppearUpdate(int time)
{
	if (!block_flag) {
		if (count_false == BLOCK_APPEAR_EFFECT_TIME) {
			SetBlock();
		}
		if (count_false == 0) {
			num_inblock = 0;
		}
		count_false++;
	}
	if (count_false > time && !Sanded()) {
		Appear();
		return true;
	}
	return false;
}

bool Block::BlockDelete()
{
	if (Sanded()) {
		block_flag = false;
		count_true = 0;
		return true;
	}
	return false;
}

bool Block::Sanded()
{
	std::shared_ptr<Marker> check;
	auto checkmarker = [&](Direction d){
		check = array_block_marker[d];
		if (check->Get_marker_flag()) {
			return true;
		}
		if (check->GetPar_flag()) {
			return false;
		}
		while (check->Get_next_block_marker(d)) {
			check = check->Get_next_block_marker(d);
			if (check->Get_marker_flag()) {
				return true;
			}
			if (check->GetPar_flag()) {
				break;
			}
		}
		return false;
	};
	return (checkmarker(Direction::UP) && checkmarker(Direction::DOWN)) || (checkmarker(Direction::LEFT) && checkmarker(Direction::RIGHT));

	//return (array_block_marker[0]->Get_marker_flag() && array_block_marker[2]->Get_marker_flag()) || (array_block_marker[1]->Get_marker_flag() && array_block_marker[3]->Get_marker_flag());
}

void Block::Appear()
{
	block_flag = true;
	count_false = 0;
}
