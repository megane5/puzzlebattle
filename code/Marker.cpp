
#include"Block.h"
#include"Marker.h"

Marker::Marker(int x,int y,bool side) :count_par(0),x(x),y(y),side(side){

	next_block_marker.resize(DIRECTION_NUM);
	next_block.resize(2);

	marker_flag = false;

	debug_count = 0;

	count_false = MARKER_COUNT_INI;				//�@=�O�@�Ƃ���ƁCMarker_CalcFalse�@�ŕs�s��
}

Marker::~Marker() {

}

void Marker::Ini_Roop() {
	selected = false;
	par_flag = false;
	money_flag = false;
}

void Marker::Update(){

}


void Marker::Draw() const {		
	Texture drawTex;
	if (money_flag) {
		drawTex = TextureAsset(L"img_button_money");
	}
	else if (marker_flag) {
		drawTex = TextureAsset(L"img_button_on");
	}
	else {
		drawTex = TextureAsset(L"img_button_off");
	}
	if (selected) {
		//TextureAsset(L"img_select_circle").drawAt(x, y);
		drawTex.scale(1.2, 1.2).drawAt(x, y);	
		if(!money_flag)
			FontAsset(L"cost")(GetCost()).drawAt(x, y, Palette::White);	
		else
			FontAsset(L"cost")(GetCost()).drawAt(x, y, Palette::Black);
		if (par_flag) {
			TextureAsset(L"img_button_par").scale(1.2, 1.2).drawAt(x, y);
		}
	}
	else {

		drawTex.scale(0.8,0.8).drawAt(x, y);		if (par_flag) {
			TextureAsset(L"img_button_par").scale(0.8, 0.8).drawAt(x, y);
		}
	}



}

void Marker::End() {

}
int Marker::GetCost() const{
	std::shared_ptr<Marker> check;
	int cost = 0;
	auto checkmarker = [&](Direction d) {
		cost = GetSimpleCost();
		if (next_block_marker[d]) {
			check = next_block_marker[d];
			if (check->Get_marker_flag()) {
				return cost;
			}

			if (check->GetPar_flag()) {
				return -1;
			}
			cost += check->GetSimpleCost();
			while (check->Get_next_block_marker(d)) {
				check = check->Get_next_block_marker(d);
				if (check->Get_marker_flag()) {
					return cost;
				}
				if (check->GetPar_flag()) {
					break;
				}
				cost += check->GetSimpleCost();
			}
		}
		return -1;
	};
	if (side) {
		auto hoge = checkmarker(Direction::LEFT);
		if (hoge != -1) {
			return hoge;
		}
		hoge = checkmarker(Direction::RIGHT);
		if (hoge != -1) {
			return hoge;
		}
	}
	else {
		auto hoge = checkmarker(Direction::UP);
		if (hoge != -1) {
			return hoge;
		}
		hoge = checkmarker(Direction::DOWN);
		if (hoge != -1) {
			return hoge;
		}
	}
	return GetSimpleCost();
}



bool Marker::Marker_Click()
{
	if (!par_flag){
		//&& (next_block[0]==NULL ? true : next_block[0]->Get_block_flag()) && (next_block[1] == NULL ? true : next_block[1]->Get_block_flag())) {//��Ⴢ��Ă��Ȃ��ėׂ̃u���b�N�����݂���Ƃ��X�C�b�`���I���ɂ���
		//�ׂ̃u���b�N�����݂��Ȃ��Ƃ��ɉ�����悤�ɂ���Ə����Ă�u���b�N���͂߂Ă��܂��A���炩���߈͂�ł������Ƃł����̃u���b�N�����ꂽ�u�ԏ����Ă��܂�
		marker_flag = true;
		return true;
	}
	return false;
}


bool Marker::MarkerUpdate(int MaxCount) {		//���R�Ɏ���}�[�J�[�ƁC�����Ă����}�[�J�[�̍S�����Ԃ��ς����
	if (marker_flag == true) {
		count_false++;
	}

	if (count_false % MaxCount == 0) {
		marker_flag = false;
		count_false = MARKER_COUNT_INI;					//�@=�O�@�Ƃ���ƁCMarker_CalcFalse�@�ŕs�s��
		return true;
	}

	return false;
}

bool Marker::ParUpdate(int MaxCount)
{

	if (par_flag) {
		count_par++;
	}
	if (count_par > MaxCount) {
		count_par = 0;
		par_flag = false;
		return true;
	}
	return false;
}
