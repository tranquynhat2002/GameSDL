// load chướng ngại vật, quái vật 
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_MAX_FALL_SPEED 10 //tốc độ rơi tự do max
#define THREAT_GRAVITY_SPEED 0.8 //tốc độ rơi tự do 
#define THREAT_FRAME_NUM 8 //số frame trong 1 ảnh
#define THREAT_SPEED 3 //tốc độ di chuyển

class ThreatsObject : public BaseObject //kế thừa từ lớp BaseObject
{
public:
	ThreatsObject(); //hàm cơ bản
	~ThreatsObject();

	enum TypeMove //các kiểu di chuyển 
	{
		STATIC_THREAT = 0, //đứng yên 
		MOVE_IN_SPACE_THREAT = 1, //di chuyển trong 1 phạm vi 
	};

	void set_x_val(const float& xVal) {x_val_ = xVal;} //hàm set, get cơ bản 
	void set_y_val(const float& yVal) {y_val_ = yVal;} //biến x_val ko cần lấy giá trị ra nên ko cần get 

	void set_x_pos(const float& xp) {x_pos_ = xp;} //hàm set, get cơ bản
	void set_y_pos(const float& yp) {y_pos_ = yp;}
	float get_x_pos() const {return x_pos_;} //biến x_pos cần lấy giá trị ra  nên cần hàm get 
	float get_y_pos() const {return y_pos_;}
	void SetMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;} //hàm set map 

	void set_clips(); //hàm set frame trong ảnh để chạy
	bool LoadImage(std::string path, SDL_Renderer* screen); ;//hàm load ảnh 
	void Show(SDL_Renderer* des); //hàm show ra 
	int get_width_frame() const {return width_frame_;} //hàm set, get cơ bản
	int get_height_frame() const {return height_frame_;}
	void DoPlayer(Map& gMap); //quá trình xử lí nhân vật di chuyển hay va chạm bản đồ, đứng yên 
	void CheckToMap(Map& gMap); //hàm check map 
	void InitThreats(); //set quá trình rơi trở lại màn hình map 
	void set_type_move(const int& typeMove) {type_move_ = typeMove;} //hàm set cơ bản 
	void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a, animation_b_ = pos_b;} //hàm set vị trí để mối hiểm họa di chuyển 
	void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;} //thiết lập trạng thái của quái là di chuyển về bên trái khi bắt đầu
	void ImpMoveType(SDL_Renderer* screen); //hàm xử lí vấn đề di chuyển trong phạm vi a đến b 
	SDL_Rect GetRectFrame(); //hàm lấy kích thước 1 frame của quái 

	std::vector<BulletObject*> get_bullet_list() const {return bullet_list_;}  //set,get cơ bản 
	void set_bullet_list(const std::vector<BulletObject*>& bl_list) {bullet_list_ = bl_list;}

	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen); //khởi tạo các thông số của đạn bắn
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit); //giơi hạn đạn bắn ra đến đâu thì mất 
	void RemoveBullet(const int& idx);//hàm xóa đạn 
private:

	int map_x_; //xác định giới hạn vs bản đồ 
	int map_y_; //xác định giới hạn vs bản đồ
	float x_val_; //biến tăng giá trị
	float y_val_; //biến tăng giá trị
	float x_pos_; //vị trí hiện tại
	float y_pos_; //vị trí hiện tại
    bool on_ground_; //nằm trên mặt đất hay chưa
	int come_back_time_; //thời gian trở lại khi rơi xuống vực thẳm 
	SDL_Rect frame_clip_[THREAT_FRAME_NUM]; //mảng lưu thứ tự các frame
	int width_frame_; //kích thước 1 frame
	int height_frame_; //kích thước 1 frame
	int frame_; //quản lí chỉ số frame

	int type_move_; //kiểu di chuyển 
	int animation_a_; //vị trí a (giới hạn di chuyển a,b cho mỗi hiểm họa 
	int animation_b_; //vị trí b
	Input input_type_; //biến quản lí việc di chuyển 

	std::vector<BulletObject*> bullet_list_; //biến quản lí vấn đề đạn bắn
};



#endif