
#include "stdafx.h"
#include "MainObject.h"

MainObject::MainObject()
{
	// lưu các giá trị cơ bản, ban đầu 
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
    x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time_ = 0;
	money_count = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen); //sử dụng lại hàm LoadImage của BaseObject 

	if (ret == true) //nếu sử dụng lại thành công 
	{
		width_frame_ = rect_.w/8; //lấy chiều dài của ảnh nhân vật chia cho số lượng frame để lấy 1 frame
		height_frame_ = rect_.h; //chiều cao của ảnh nhân vật 
	}

	return ret;
}

SDL_Rect MainObject::GetRectFrame() //hàm lấy kích thước 1 frame 
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void MainObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		//trạng thái của từng frame 
		frame_clip_[0].x = 0; //frame đầu tiên, tọa độ x =0, y=0
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_; //chiều rộng của 1 frame giữ nguyên 
		frame_clip_[0].h = height_frame_; //chiều cao của frame giữ nguyên 

		frame_clip_[1].x = width_frame_; //frame 2
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;


		frame_clip_[2].x = 2*width_frame_; //fram 3
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3*width_frame_; //frame 4
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4*width_frame_; //frame 5
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5*width_frame_; //frame 6
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6*width_frame_; //frame 7	
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7*width_frame_; //frame 8
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des); 

	if (input_type_.left_ == 1||
		input_type_.right_ == 1) //nếu liên tục bấm vào left hay right thì tăng frame lên 
	{
		frame_++;
	}
	else //nếu ko để nguyên frame
	{
		frame_ = 0;
	}

	if (frame_ >= 8)  //nếu frame >=8 thì chạy về frame ban đầu, nếu ko cộng dần sẽ bị lỗi vì lớn hơn 8 
	{
		frame_ = 0;
	}

	if (come_back_time_ == 0) //nếu thời gian quay trở lại =0 thì  mới load bên dưới, tránh việc load nhiều dẫn đến chương trình bị lag 
	{
		//vị trí hiển thị nhân vật
	     rect_.x = x_pos_ - map_x_; 
		 //nếu giữ nguyên vị trí thì màn hình sẽ bị nhảy đi đến 1 vị trí rất là xa do bị cuốn đi mất 1 lượng, nên trừ đi 1 lượng đó sẽ để nhân vật về đúng vị trí hiển thị lên màn hình
	     rect_.y = y_pos_ - map_y_;

	     SDL_Rect* current_clip = &frame_clip_[frame_]; //kích thước hiện tại, xem đang ở frame thứ mấy 

	     SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_}; //lưu chính xác xem ở tọa độ nào, chiều dài, chiều rộng là bao nhiêu 

	     SDL_RenderCopy(des, p_object_, current_clip, &renderQuad); //sao chếp kết cấu vào mục tiêu hiển thị màn hình hiện tại
	}
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN) //nếu ấn phím
	{
		switch (events.key.keysym.sym) 
		{
		case SDLK_RIGHT: //di chuyển sang phải 
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1; //lưu 1 để kiểm tra ở hàm show
				input_type_.left_ = 0;
				UpdateImagePlayer(screen); //hàm cập nhật hình ảnh , update
			}
			break;
		case SDLK_LEFT: //di chuyển sang trái 
			{
				status_ = WALK_LEFT;
				input_type_.left_ = 1; //lưu 1 để kiểm tra ở hàm show
				input_type_.right_ = 0;
				UpdateImagePlayer(screen); //hàm cập nhật hình ảnh , update
			}
			break;
		}
	} 
	else if (events.type == SDL_KEYUP) //nếu nhả phím
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT: //di chuyển sang phải
			{
				input_type_.right_ = 0; //lưu trạng thái về ban đầu
				dung_im=0; //lưu trạng thái để tí xét đạn bắn
			}
			break;
		case SDLK_LEFT: //di chuyển sang trái
			{
				input_type_.left_ = 0; //lưu trạng thái về ban đầu
				dung_im=1; //lưu trạng thái để tí xét đạn bắn
			}
			break;
		}
	}

	if (events.type == SDL_MOUSEBUTTONDOWN) //nếu ấn chuột
	{
		if (events.button.button == SDL_BUTTON_RIGHT) //nếu ấn chuột phải thì nhảy lên 
		{
			input_type_.jump_ = 1; //lưu 1 để kiểm tra ở hàm show
		}
		else if (events.button.button == SDL_BUTTON_LEFT) //nếu ấn chuột trái thì bắn 
		{
			BulletObject* p_bullet = new BulletObject(); //tọa viên đạn mới 
			p_bullet->set_bullet_type(BulletObject::LASER_BULLET); //hàm chọn loại đạn để load ảnh 
			p_bullet->LoadImgBullet(screen); //load hình ảnh viên đạn

			if (status_ == WALK_LEFT || dung_im==1)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);  //set hướng của đạn 
				p_bullet-> SetRect(this->rect_.x, rect_.y +height_frame_*0.25); //set vị trí cho viên đạn bắn ra, cố gắng viên đạn bắn ra từ nòng súng 
			}
			if (status_ == WALK_RIGHT || dung_im==0)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT); //set hướng của đạn 
				p_bullet-> SetRect(this->rect_.x + width_frame_ - 20, rect_.y +height_frame_*0.25); //set vị trí cho viên đạn bắn ra, cố gắng viên đạn bắn ra từ nòng súng 
			}
			

			p_bullet-> set_x_val(20); //tốc độ đạn di chuyển 
			p_bullet-> set_y_val(20); //tốc độ đạn di chuyển 
			p_bullet-> set_is_move(true); //ấn chuột là đạn bắn 

			p_bullet_list_.push_back(p_bullet); //cho đạn vào danh sách, nạp đạn 

		}
	}
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++) //kiểm tra xem băng đạn có hay ko
	{
		BulletObject* p_bullet = p_bullet_list_.at(i); //nếu có bắn từng viên 1,tại bấm thì ra 1 viên
		if (p_bullet != NULL) //nếu có giá trị 
		{
			if (p_bullet-> get_is_move() == true) //cho phép bắn  
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT); //đạn bắt đầu xuất hiện và di chuyển  
				p_bullet->Render(des); //show ra màn hình 
			}
			else //nếu ko có j 
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i); //nếu viên đạn đc bấn vượt quá màn hình thì hủy đi 
				if (p_bullet != NULL) //nếu có giá trị, chưa xóa 
				{
				   delete p_bullet; //xóa viên đạn 
				   p_bullet = NULL; //gán lại 
				}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx)
{
	int size = p_bullet_list_.size(); //kiểm tra xem có đạn ko
	if (size > 0 && idx < size) //nếu có và viên đạn cần xóa ko vượt quá size viên đạn
	{
		BulletObject* p_bullet = p_bullet_list_.at(idx); //gọi viên đạn ra
		p_bullet_list_.erase(p_bullet_list_.begin() + idx); //hủy viên đạn đó khỏi danh sách đạn 

		if (p_bullet) //xóa viên đạn (làm để chắc ăn để loại bỏ bộ nhớ rác)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time_ == 0) //nếu ko rơi thì làm như bình thường, nằm trong vùng bản đồ
	{
	x_val_ = 0;
	y_val_ += 0.8; //tốc độ rơi của nhân vật 

	if (y_val_ >= MAX_FALL_SPEED) //giới hạn tốc độ rơi 
	{
		y_val_ = MAX_FALL_SPEED;
	}

	if (input_type_.left_ == 1) //nếu bấm trái, thì sẽ trừ đi 1 lượng
	{
		x_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1) //nếu bấm phải, sẽ cộng thêm 1 lượng 
	{
		x_val_ += PLAYER_SPEED;
	}

	if (input_type_.jump_ == 1) //nếu bấm chuột phải 
	{
		if (on_ground_ == true) //nếu nhân vật đang trên mặt đất mới nhảy 
		{
		   y_val_ = - PLAYER_JUMP_VAL; //trừ đi 1 lượng để nhảy lên 
		}
		on_ground_ = false; //nhảy xong ko trên mặt đất nên gán false
		input_type_.jump_ = 0; //nhảy xong gán về vị trí ban đầu
	}

	CheckToMap(map_data); 
	CenterEntityOnMap(map_data);
	}

	if (come_back_time_ > 0) //nếu nhân vật nằm ngoài vùng bản đồ 
	{
		come_back_time_ --; //trừ liên tiếp giá trị đi đến khi về 0
		if (come_back_time_ == 0) // Reset again
		{
			on_ground_ = false; //lúc bắt đầu chạy lại nhân vật rơi nên ko ở trên mặt đất 
			if (x_pos_ > 256) //nếu lớn hơn thì trừ đi 1 lượng, nếu bé hơn thì ko cần trừ tránh việc khi rơi xuống rơi đúng vực ko kịp đi vào 
			{
			    x_pos_ -= 256; // 4 ô map
			}
			else
			{
				x_pos_ = 0;
			}
			//gán lại giá trị cho nhân vật xuất hiện trở lại trên màn hình 
			y_pos_ = 0; 
			x_val_ = 0; 
			y_val_ = 0;
		}
	}
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	//map di chuyển theo chiều ngang 
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2); //vị trí đầu tiên của map = vị trí của nhân vật trừ đi 1/2 chiều dài map
	//nghĩa là khi đi đc nửa chiều dài của map thì map bắt đầu di chuyển 

	if (map_data.start_x_ < 0) //tức là khi lùi 
	{
		map_data.start_x_ = 0; //ko cho phép bản đồ lùi thêm nữa
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) //nếu khi điểm bắt đầu + screen_width bằng đúng chiều dài tối đa của map bản đồ
	{
		map_data.start_x_ = map_data.max_x_ -SCREEN_WIDTH; //thì ko cho bản đồ di chuyển thêm nữa
	}

	//map di chuyển theo chiều dọc 
	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2); //tương tự vs x
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0; 
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}


void MainObject::CheckToMap(Map& map_data)
{
	//giới hạn kiểm tra từ a đến b theo chiều x
	int x1 = 0;
	int x2 = 0;

	//giới hạn kiểm tra từ a đến b theo chiều y 
	int y1 = 0;
	int y2 = 0;

	//Check theo chiều ngang 
	//chiều cao nhỏ nhất 
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE; //so sánh chiều cao của nhân vật vs kích thước 1 ô, nếu ai nhỏ hơn thì lấy

	//x1=vị trí hiện tại của nhân vật + 1 lượng tăng lên khi di chuyển xong chia cho kích thước 1 ô lấy phần nguyên sẽ ra đang ở ô thứ bao nhiêu 
	x1 = (x_pos_ + x_val_)/TILE_SIZE; 
	/*x2=vị trí hiện tại của nhân vât+1 lượng tăng lên khi di chuyển+chiều rộng của map
	nếu chia luôn cho tile sẽ ra ô thứ bao nhiêu, nhưng để check va chạm nên sẽ trừ đi 1*/
	x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

	//tương tự ta cũng có y 
	y1 = (y_pos_)/TILE_SIZE;
	y2 = (y_pos_ + height_min - 1)/TILE_SIZE;
	//(mục đích x1,x2,y1,y2 là để xác định xem nhân vật nằm ở ô thứ bao nhiêu đến ô thứ bao nhiêu trên bản đồ)

	/*
	    x1,y1.........x2,y1
		..................
		..................
		..................
		x2,y1.........x2,y2
	*/

	//kiểm tra x1,x2,y1,y2 có nằm trong phạm vi tối đa của bàn đồ hay ko 
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // đối tượng đang di chuyển sang bên phải 
		{

            int val1 = map_data.tile[y1][x2]; 
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_FLAG || val2 == STATE_FLAG) //nếu tại vị trí đó có lá cờ
			{
				money_count=1000;
			}

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) //nếu tại vị trí đó có đồ hỗ trợ(tiền)
			{
				map_data.tile[y1][x2] = 0; //ô đó ko hiện lên nữa(biến mất)
				map_data.tile[y2][x2] = 0;
				IncreaseMoney(); //đếm tiền ăn đc 
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) //nếu tại vị trí đó có hình ảnh hay vật gì đó 
			     {
				   x_pos_ = x2*TILE_SIZE; //khi di chuyển 1 lượng gặp chướng ngại vậy sẽ ko để cho nhân vật di chuyển nữa mà sẽ dừng tại vị trí đấy 
				   x_pos_ -= width_frame_ + 1; // do lúc đầu trừ đi 1 nên sẽ phải cộng thêm 1 để trở về ô ngay trước vật cản 
				   x_val_ = 0; //gán =0 để không thể tăng đc nữa, sẽ dừng ở vị trí đó 
			     }
			}
		}
		else if (x_val_ < 0) //nếu đối tượng đi lùi 
		{
            int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) //tương tự như ở trên 
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				IncreaseMoney();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) //nếu tại vị trí đó có hình ảnh hay vật gì đó 
			     {
				    x_pos_ = (x1 + 1)*TILE_SIZE; //lúc trc bớt 1 nên sẽ cộng thêm 1
				    x_val_ = 0; //gán=0 để ko lùi đc nữa
			     }

			}
		}
	}


	// Check theo chiều dọc 

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE; //tương tự như check theo chiều ngang
	//lấy tọa độ
	x1 = (x_pos_)/TILE_SIZE;
	x2 = (x_pos_ + width_min)/TILE_SIZE;

	y1 = (y_pos_ + y_val_)/TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) //nếu như nằm trong khoảng bản đồ 
	{
		if (y_val_ > 0) //trạng thái rơi tự do 
		{

			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) //xem tại vị trí đó có hình ảnh ko,nếu có 
			    {
				   y_pos_ = y2*TILE_SIZE; //đứng trên mặt đất 
				   y_pos_ -= (height_frame_ + 1);
				   y_val_ = 0; //ko tăng lên nữa, nếu tăng nữa sẽ chui xuống dưới 
				
				   on_ground_ = true; //nếu check đc va chạm rơi tự do, lưu =true có nghĩa là đang trên mặt đất
				   if (status_ = WALK_NONE)
				   {
					  status_ = WALK_RIGHT;
				   }
			    }
			}
		}
		else if (y_val_ < 0) //nhân vật nhảy lên trên 
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney();
			}
			else 
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) //check xem có hình ảnh ko,nếu có 
			    {
				   y_pos_ = (y1 + 1)*TILE_SIZE; //ko cho phép vượt quá hình ảnh đó, 1 là sai số
				   y_val_ = 0;
			    }
			}
		}
	}

	x_pos_ += x_val_; //nếu ko va chạm sẽ đi bình thường, di chuyển bình thường
	y_pos_ += y_val_;

	if (x_pos_ < 0) //nếu lừi quá mức về đến bàn đồ sẽ ko cho lùi nữa
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) //nếu cứ tiến mãi quá giới hạn bản đồ thì gán x_pos_ = như dưới trừ đi 1 lượng sai số 1, có nghĩa là làm cho bản đồ di chuyển đến max của bản đồ
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_) //khi rơi xuống vực vì ko va chạm nên chiều cao được cộng liên tiếp
		                         //nếu chiều cao vượt quá chiều cao cho phép của bản đồ 
	{
		come_back_time_ = 50; //thời gian quay trở lại, độ trễ
	}
}

void MainObject::IncreaseMoney() 
{
	money_count++;//đếm số lượng tiền ăn đc
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground_ == true) //nếu đang ở trên mặt đất
	{
		if (status_ == WALK_LEFT) //nếu ấn trái
		{
			LoadImage("img//player_left.png", des); //load ảnh trái
		}
		if (status_ == WALK_RIGHT) //nếu ấn phải
		{
			LoadImage("img//player_right.png", des); //load ảnh phải
		}
	}
	else //nếu ko ở trên mặt đất
	{
		if (status_ == WALK_LEFT) //nếu ấn trái
		{
			LoadImage("img//jum_left.png", des); //load ảnh nhảy trái
		}
		if (status_ == WALK_RIGHT) //nếu ấn phải 
		{
			LoadImage("img//jum_right.png", des); //load ảnh nhảy phải
		}
	}
}