
#include "stdafx.h"
#include "PlayerPower.h"

PlayerPower::PlayerPower() //hàm khởi tạo 
{
	number_ = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::Init(SDL_Renderer* screen)
{
	LoadImage("img//player_pw.png",screen); //load ảnh ra màn hình
	number_ = 3;//gán số mạng bằng 3 
	if (pos_list_.size() > 0) //kiểm tra nếu có size thì xóa đi
	{
		pos_list_.clear();
	}

	AddPos(20); //gán mặc định 3 vị trí để hiển thị ảnh ra màn hình
	AddPos(60);
	AddPos(100);
}

void PlayerPower::AddPos(const int& xp) 
{
	pos_list_.push_back(xp); //nhập vị trí
}

void PlayerPower::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++) //show tất cả ảnh ở các vị trí ra màn hình 
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void PlayerPower::Decrease()
{
	number_--; //nếu chết thì mất 1 mạng
	pos_list_.pop_back(); //xóa hình ảnh ở vị trí cuối cùng đi 
}

void PlayerPower::InitCrease()
{
	number_++; //tăng mạng 
	int last_pos = pos_list_.back(); //thêm vị trí cuối cùng
	last_pos += 40; //vị trí đó cách vị trí trc 40
	pos_list_.push_back(last_pos); //thêm hình ảnh mạng vào vị trí đó 

}


PlayerMoney::PlayerMoney() //khởi tạo thông số ban đầu
{
	x_pos_ = 0;
	y_pos_ = 0;
}

PlayerMoney::~PlayerMoney() //hàm hủy
{

}

void PlayerMoney::Init(SDL_Renderer* screen)
{
	bool ret = LoadImage("img//money_img.png", screen); //load ảnh ra màn hình
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_; //thiết lập kích thước
	rect_.y = y_pos_;
	Render(screen); //xuất ra màn hình ảnh ở kích thước trên 
}