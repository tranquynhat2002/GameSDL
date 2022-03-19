//hàm quản lí vụ nổ
#ifndef EXP_H_	
#define EXP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 8 //số frame vụ nổ: 8


class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

public: //các hàm khởi tạo và gọi ra 
	void set_clip(); 
	void set_frame(const int& fr) { frame_ = fr; }
	virtual bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	int get_frame_width() const {return frame_width_;}
	int get_frame_height() const {return frame_height_;}

private:
	int frame_width_; //kích thước của 1 frame 
	int frame_height_;

	unsigned int frame_; //biến quản lí đang là frame bao nhiêu
	SDL_Rect frame_clip_[8]; //biến để tạo clip chạy frame 

};

#endif