//hiển thị hình ảnh ra để đếm
#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class PlayerPower : public BaseObject //kế thừa
{
public:
	PlayerPower();
	~PlayerPower();

	void SetNum(const int& num) { number_ = num;} //hàm nhận vào số mạng 
	void AddPos(const int& xPos); //hàm add vị trị 
	void Show(SDL_Renderer* screen); //hàm show ra màn hình
	void Init(SDL_Renderer* screen); //hàm thiết lập vị trí ban đầu
	
	void InitCrease(); //hàm tăng số mạng 
	void Decrease(); //hàm giảm số mạng

private:
	int number_; //số mạng
	std::vector<int> pos_list_; //các vị trí để hiển thị 

};

class PlayerMoney : public BaseObject
{
public:
	PlayerMoney();
	~PlayerMoney();

	void Init(SDL_Renderer* screen); //hàm thiết lập vị trí ban đầu
	void Show(SDL_Renderer* screen); //hàm show ra màn hình 
	void SetPos(const int& x, const int& y) { x_pos_ = x, y_pos_ = y; } //hàm set vị trí để hiển thị 
private:
	int x_pos_; //tọa độ để xuất hiện ra hình ảnh đồng tiền
	int y_pos_;
};

#endif