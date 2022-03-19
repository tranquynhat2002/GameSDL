
#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() //khởi tạo giá trị cho các biến 
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = 0;
	come_back_time_ = 0;
	frame_ = 0;

	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;
	type_move_ = STATIC_THREAT;

}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen);	//gọi hàm 
	if (ret) //kiểm tra,nếu thành công 
	{
		width_frame_ = rect_.w/THREAT_FRAME_NUM; //lấy giá trị 1 frame 
		height_frame_ = rect_.h;
	}

	return ret;
}

SDL_Rect ThreatsObject::GetRectFrame() //hàm lấy kích thước 1 frame
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	
	return  rect;
}

void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0) //nếu kích thước frame thỏa mãn
	{
		frame_clip_[0].x = 0;  //tương tự vs cách load frame của nhân vật điểu khiển 
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;


		frame_clip_[2].x = 2*width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3*width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4*width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5*width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6*width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7*width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}

void ThreatsObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0) //nếu thời gian quay trở lại bằng 0, ko rơi xuống vực thẳm thì cho phép hiển thị 
	{
		rect_.x = x_pos_ - map_x_; //vị trí thực sự của quái 
		rect_.y = y_pos_ - map_y_;
		frame_++; //tăng liên tục frame lên, làm cho quái tự di chuyển 
		if (frame_ >=8) //nếu frame >8 quay lại frame 0 
		{
			frame_ = 0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_]; 
		SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}
}

void ThreatsObject::DoPlayer(Map& gMap)
{
	if (come_back_time_ == 0) //nếu thời gian quay trở lại bằng 0, ko rơi xuống vực thẳm 
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED; //cộng với 1 lượng rơi tự do 
		if (y_val_ >= THREAT_MAX_FALL_SPEED) //khi tốc rơi lớn hơn tốc độ rơi tự do max 
		{
			y_val_ = THREAT_MAX_FALL_SPEED; //gán luôn bằng giá trị max
		}

		if (input_type_.left_ == 1) //nếu đang di chuyển về bên trái 
		{
			x_val_ -= THREAT_SPEED; //trừ đi x_val 1 lượng tốc độ di chuyển 
		}
		else if (input_type_.right_ == 1) //nếu đang di chuyển về bên phải 
		{
			x_val_ += THREAT_SPEED; //cộng x_val 1 lượng tốc độ di chuyển 
		}

		CheckToMap(gMap); //kiểm tra xem có va chạm vs bản đồ hay ko 
	}
	else if (come_back_time_ > 0) //nếu thời gian quay trở lại >0
	{
		come_back_time_ --; //giảm dần
		if (come_back_time_ == 0) //nếu giảm đến 0
		{
			InitThreats();
		}
	}
}

void ThreatsObject::InitThreats() //set quá trình rơi trở lại màn hình map 
{
			x_val_ = 0; //vị trí bắt đầu rơi trở lại 
			y_val_ = 0;
			if (x_pos_ > 256) //nếu vị trí hiện tại lớn hơn 256 thì giảm đi 256 
			{
				x_pos_ -= 256; //trừ đi 1 lượng để ko phải rơi xuống vực lúc ban đầu rơi 
				animation_a_ -= 256; //cũng phải trừ đi để quái lúc nào cũng trong khoảng a,b
				animation_b_ -= 256; 
			}
			else
			{
				x_pos_ = 0; //nếu ko gán bằng 0
			}
			y_pos_ = 0; //gán vị trí hiện tại =0 ,(làm như này để nhân vật bắt đầu rơi từ trên xuống)
			come_back_time_ = 0; //gán thời gian quay trở lại =0
			input_type_.left_ = 1; //gán để quái di chuyển sang bên trái lúc rơi xuống 
}

void ThreatsObject::RemoveBullet(const int& idx) //hàm xóa đạn 
{
	int size = bullet_list_.size(); //lấy ra kích thước băng đạn của quái
	if (size > 0 && idx < size) //nếu có đạn và đạn cần xóa bé hơn kích thước băng thì xóa đạn 
	{
		BulletObject* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);

		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}


void ThreatsObject::CheckToMap(Map& map_data)
{
	int x1 = 0; //tương tự check to map ở bên MainObject 
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_)/TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

	y1 = (y_pos_)/TILE_SIZE;
	y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // main object is moving to right
		{

            int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
	
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
			{
				x_pos_ = x2*TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		
		}
		else if (x_val_ < 0)
		{
            int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) //xử lí nếu gặp đồng tiên thì bỏ qua, coi như chưa có gì 
			{
				x_pos_ = (x1 + 1)*TILE_SIZE;
				x_val_ = 0;
			}
		}
	}


	// Check vertical 

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_)/TILE_SIZE;
	x2 = (x_pos_ + width_min)/TILE_SIZE;

	y1 = (y_pos_ + y_val_)/TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{

			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

		    if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
			{
				y_pos_ = y2*TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				
				on_ground_ = true;
		    }
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

		    if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
			{
				y_pos_ = (y1 + 1)*TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) 
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_)
	{
		come_back_time_ = 50;
	}
}


void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THREAT) //nếu quái đứng yên 
	{
		;//
	}
	else //nếu di chuyển
	{
		if (on_ground_ == true) //nếu đứng trên mặt đất
		{
			if (x_pos_ > animation_b_) //nếu vị trí di chuyển của quá vượt quá điểm b,bắt đầu quay ngược lại đi về
			{
				input_type_.left_ = 1; // gán 1 để di chuyển về bên trái 
				input_type_.right_ = 0; //lúc đố ko di chuyển về bên phải 
				LoadImage("img//threat_left.png", screen); //load ảnh frame đi về bên trái 
			}
			else if (x_pos_ < animation_a_) //nếu vị trí di chuyển của quá vượt quá điểm a, bắt đầu quay ngược lại đi về  
			{
				input_type_.left_ = 0; //lúc đó ko di chuyển về bên trái 
				input_type_.right_ = 1; //gán 1 để di chuyển về bên phải 
				LoadImage("img//threat_right.png", screen); //load ảnh frame đi về bên phải 
			}
		}
		else //nếu ko đứng trên mặt đất 
		{
			if (input_type_.left_ == 1) //nếu đang di chuyển về bên trái 
			{ 
				LoadImage("img//threat_left.png", screen); //load ảnh frame đi về bên trái 
			}
		}
	}
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL) //kiểm tra xem có đạn hay ko 
	{
		p_bullet->set_bullet_type(BulletObject::LASER_BULLET); //set loại đạn bắn ra 
		bool ret = p_bullet->LoadImgBullet(screen);//load ảnh đạn đó 
		if (ret) //nếu load đc ảnh 
		{
		p_bullet->set_is_move(true); //trạng thái đạn 
		p_bullet->set_bullet_dir(BulletObject::DIR_LEFT); //hướng bắn sang trái 
		p_bullet->SetRect(rect_.x + 5, rect_.y + 10); //set vị trí cho đạn bắn ra, làm sao để bắn ra từ quái vật 
		p_bullet->set_x_val(15);//tốc độ đạn bắn ra
		bullet_list_.push_back(p_bullet); //cho vào lại p_bullet
		}
	}
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_.size(); i++) //kiểm tra băng đạn
	{
		BulletObject* p_bullet = bullet_list_.at(i); //lấy từng viên đạn 
		if (p_bullet != NULL) //nếu có giá trị, lấy đc
		{
			if (p_bullet->get_is_move()) //nếu đạn bắn ra ko chạm giới hạn tăng dần vị trí đạn  
			{
				int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x; 
				// vị trí hiện tại của quái + kích thước 1 frame - tọa độ của đạn ra khoảng cách giữa nhân vật và quái mình cần để bắt đầu bắn đạn 
				if (bullet_distance < 300 && bullet_distance > 0) //nếu trong khoảng 0 đến 300
				{
				   p_bullet->HandleMove(x_limit, y_limit); //cho phép đạn bắn
				   p_bullet->Render(screen);
				}
				else //còn nếu ko cho phép đạn biến mất
				{
					p_bullet->set_is_move(false); //ko bắn ra nữa 
				}
			}
			else //nếu quá giới hạn thì set lại viên đạn về vị trí ban đầu 
			{
				p_bullet->set_is_move(true); //gán ban đầu ko quá giới trị
				p_bullet->SetRect(rect_.x + 5, rect_.y + 10); //tọa lại vị trí đạn bắt đầu bắn ra 
			}		
		}
	}
}