
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8 //tốc độ rơi 
#define MAX_FALL_SPEED 10 //tốc độ rơi tối đa
#define PLAYER_SPEED 8 //tốc độ di chuyển của nhân vật 
#define PLAYER_JUMP_VAL 18 //độ cao khi nhảy lên

class MainObject : public BaseObject //(kế thừa)
{
public:
	MainObject();
	~MainObject();

	enum WalkType //di chuyển 
	{
		WALK_NONE = 0, //ko di chuyển
		WALK_RIGHT = 1, //sang phải 
		WALK_LEFT = 2, //sang trái 
	};

	bool LoadImage(std::string path, SDL_Renderer* screen); //thông số riêng cho kích thước của tấm ảnh
	void Show(SDL_Renderer* des); //hàm show từng frame 1 
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen); //hàm xử lí sự kiện khi bấm để di chuyển 
	void set_clips(); //hàm tạo hiệu ứng clip, hiệu ứng animation cho nhân vật

	void DoPlayer(Map& map_data); //cộng trừ lên 1 lượng cho nhân vật di chuyển 
	void CheckToMap(Map& map_data); //hàm check va chạm giữa nhân vật với map 
	void SetMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}; //hàm để set 2 tham số của bản đồ 
	void CenterEntityOnMap(Map& map_data); //hàm tính toán ra thông số của map khi di chuyển nhân vật 
	void UpdateImagePlayer(SDL_Renderer* des); //hàm update hình ảnh 
	SDL_Rect GetRectFrame(); //hàm chuyên môn lấy kích thước frame

	void set_bullet_list(std::vector<BulletObject*> bullet_list) //hàm set, get cho p_bullet_list
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
	void HandleBullet(SDL_Renderer* des); //hàm xử lí đạn bắn 
	void RemoveBullet(const int& idx); //hàm xóa viên đạn
	void IncreaseMoney(); //hàm đếm số lượng tiền ăn đc
	int get_frame_width() const {return width_frame_;}
	int get_frame_height() const {return height_frame_;}
	void set_comeback_time(const int& cb_time) {come_back_time_ = cb_time;} //thời gian trở lại khi chết
	int GetMoneyCount() const {return money_count; } //hàm lấy tiền ra
private:

	int money_count;
	std::vector<BulletObject*> p_bullet_list_; //lưu tọa độ từng viên đạn (băng đạn)
	float x_val_; //tăng lên bao nhiêu, lùi lại bao nhiêu 
	float y_val_;

	float x_pos_; //vị trí hiện tại của nhân vật 
	float y_pos_;

	int width_frame_; //biến lưu kích thước của 1 frame 
	int height_frame_;

	SDL_Rect frame_clip_[8]; //biến lưu các frame
	Input input_type_; //biến lưu trạng thái 
	int frame_; //biến lưu chỉ số của frame, vd frame 1 hay 2,..
	int status_; //biến lưu trạng thái của 2 kiểu di chuyển, vd sang trái hay sang phải 
	bool on_ground_; //biến lưu trạng thái nhân vật đứng trên mặt đất

	int map_x_; //vị trí mới của bản đồ khi di chuyển 
	int map_y_;

	int come_back_time_; //thời gian xuất hiện trở lại khi rơi xuống vực
	int dung_im; // biến lưu trạng thái để tí xét đạn bắn
};


#endif

