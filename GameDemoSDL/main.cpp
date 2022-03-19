


#include "stdafx.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "MenuGame.h"
 
BaseObject g_background;
TTF_Font* font_time = NULL; //tạo đối tượng font chữ
TTF_Font* g_font_MENU = NULL;

bool InitData() //khởi động thông số cho môi trường của SDL
{
	bool success = true; //biến trả lại 
	int ret = SDL_Init(SDL_INIT_VIDEO); //thiết lập môi trường ban đầu cho SDL
	if (ret < 0) //nếu hàm lỗi
		return false;

	//nếu thành công
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //thiết lập chế độ tỉ lệ về chất lượng

	//tạo cửa số window cho game
	g_window = SDL_CreateWindow("20020062 Trần Quý Nhất",
		                         SDL_WINDOWPOS_UNDEFINED, 
								 SDL_WINDOWPOS_UNDEFINED, 
								 SCREEN_WIDTH, SCREEN_HEIGHT, 
								 SDL_WINDOW_SHOWN);

	if(g_window == NULL) //nếu không tạo đc, bị lỗi
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); //g_window trả ra biến render cho g_screen
		if (g_screen == NULL) //nếu render cho screen ko thành công 
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); //đặt màu được sử dụng cho các thao tác vẽ
			int imgFlags = IMG_INIT_PNG; //cờ
			if (!(IMG_Init(imgFlags) && imgFlags)) //nếu khác nhau 
				success = false;
		}

		if (TTF_Init() == -1) //nếu lỗi
		{
			success = false;
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }

		font_time = TTF_OpenFont("font//dlxfont_.ttf", 15); //đọc file font lên 
		if (font_time == NULL) //nếu ko đọc thành công 
		{
			success = false;
		}
		g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
        if (g_font_MENU == NULL)
        {
            return false;
        }
	}

	return success;
}

bool LoadBackground() //hàm load ảnh background 
{
	bool ret = g_background.LoadImage("img/BG.png", g_screen);
	if (ret == false) // kiểm tra xem load dc ảnh ko 
		return false;

	return  true;
}

void close() //giải phóng các đối tượng 
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatsObject*> MakeThredList() //làm ra 1 list các đối tượng hiểm họa, quái 
{
	std::vector<ThreatsObject*> list_threats;


	ThreatsObject* dynamic_threats = new ThreatsObject[20]; //tọa ra 20 đối tượng hiểm họa 
	for (int i = 0; i < 20; i++) //load từng đối tượng 1
	{
		ThreatsObject* p_threat = (dynamic_threats + i); //khởi tạo từng các 1 
		if (p_threat != NULL) //nếu có giá trị 
		{
			p_threat->LoadImage("img//threat_left.png", g_screen); //load ảnh của hiểm họa 
			p_threat->set_clips(); //load các frame, tạo clip
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT); //kiểu di chuyển 
			p_threat->set_x_pos(500 + i*400);//tạo các vị trí để quái rơi xuống, tránh rơi cùng vị trí quái khác 
			p_threat->set_y_pos(200);
			int pos1 = p_threat->get_x_pos() - 60; //lấy tọa độ để giới hạn di chuyển của quái 
			int pos2 = p_threat->get_x_pos() + 60; 
			p_threat->SetAnimationPos(pos1, pos2); //set các giá trị để tọa ra khoảng giới hạn [a,b]
			p_threat->set_input_left(1); //set trạng thái bắt đầu di chuyển ban đầu là sang trái 
			list_threats.push_back(p_threat); //cho lại vào p_threat
		}
	}



	ThreatsObject* threats_objs = new ThreatsObject[20]; //tạo ra 20 đối tượng hiểm họa 

	for (int i = 0; i < 20; i++) //load từng đối tượng 1
	{
		ThreatsObject* p_threat = (threats_objs + i); //khởi tạo từng các 1 
		if (p_threat != NULL) //nếu có giá trị 
		{
			p_threat->LoadImage("img//threat_level.png", g_screen); //load ảnh của hiểm họa
			p_threat->set_clips(); //load các frame
			p_threat->set_x_pos(700 + i*1000); //xét các vị trí cho quái, kiếm các vị trí thỏa mãn để rơi rải rác sao cho cân bằng 
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT); //kiểu di chuyển 
			p_threat->set_input_left(0); //trạng thái ko di chuyển 

			BulletObject* p_bullet = new BulletObject(); //mua đạn
			p_threat->InitBullet(p_bullet, g_screen); //khởi tạo viên đạn 
			list_threats.push_back(p_threat); //cho lại vào p_threrat 
		}
	}

	return list_threats; //trả về 
}

int main(int argc, char* argv[])
{
	reset:
	ImpTimer fps_timer;

	if (InitData() == false) //nếu việc init thất bại
		return -1;

	 int ret_menu = 2;
	 int check_menu = 0;
	 while (ret_menu ==2 && check_menu == 0)
	 {
		g_background.Free();
		ret_menu = MenuGame::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit","Guide", "img//menu.png");
		if (ret_menu == 1)
		{
			close();
			break;
		}

		if (ret_menu == 0) 
			break;
		g_background.Free();
		check_menu = MenuGame::ShowGuideStory(g_screen,g_font_MENU,"Back","Exit","img//huongdan.png");
			
		if (check_menu == 1)
		{
			close();
			break;
		}
		
	}

	if (LoadBackground() == false) //nếu việc load background thất bại 
		return -1;


	GameMap game_map; //đối tượng để tạo map
	game_map.LoadMap("map/map01.dat"); //file chứa các trạng thái của ô 
	game_map.LoadTiles(g_screen); //load ảnh của tile lên màn hình


	MainObject p_player; 
	p_player.LoadImage("img//player_right.png", g_screen); //ban đầu cứ load ảnh bên phải 
	p_player.set_clips(); //tạo hiệu ứng 

	//khởi tạo 3 mạng, load ảnh ra sẵn,mạng xuất hiện ngay đầu nên ko cần xét tọa độ xuất hiện
	PlayerPower player_power;
	player_power.Init(g_screen);

	//khởi tạo hình ảnh tiền 
	PlayerMoney player_money;
	player_money.Init(g_screen);
	player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);//tọa độ xuất hiện hợp lí

	std::vector<ThreatsObject*> threats_list = MakeThredList(); //dùng hàm đã khởi tạo để load ra mối hiểm họa

	ExplosionObject exp_threat; //tạo hiệu ứng vụ nổ cho viên đạn bắn vào quái vật
	bool tRet = exp_threat.LoadImage("img//exp3.png", g_screen); //load ảnh
	if (!tRet) return -1; //nếu load ko thành công, false
	exp_threat.set_clip(); //tạo frame vụ nổ cho nó 

	ExplosionObject exp_main;
	bool mRet = exp_main.LoadImage("img//exp3.png", g_screen);
	exp_main.set_clip();
	if (!mRet) return -1;

	int num_die = 0; //số lần chết 

	//TEXT
	TextObject time_game; //thêm chữ 
	time_game.SetColor(TextObject::WHITE_TEXT); //set màu cho chữ

	TextObject mark_game; //thêm chữ
	mark_game.SetColor(TextObject::WHITE_TEXT); //set màu cho chữ
	UINT mark_value = 0; //biến quản lí tăng điểm khi bắn chết quái vật 

	TextObject money_game; //thêm chữ
	money_game.SetColor(TextObject::WHITE_TEXT); //set màu cho chữ

	// hàm load ra màn hình mãi mãi đến khi quit
	bool is_quit = false;
	while (!is_quit)
	{
		fps_timer.start(); //xem thời điểm bắt đầu 
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			p_player.HandelInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		//" Các dòng lệnh để load background"

		Map map_data = game_map.getMap();

		p_player.HandleBullet(g_screen); //đạn 
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_); //gán giá trị map_x,map_y đang có 
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);


		game_map.SetMap(map_data); //cập nhật vị trí mới của bản đồ
		game_map.DrawMap(g_screen); //vẽ lại map 

		//Vẽ hình học
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40); //kích thước hình chữ nhật
		ColorData color_data(0, 80, 150); //màu sắc
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen); //vẽ ra màn hình

		GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38); //kích thước dòng kẻ
		ColorData color_data2(255, 255, 255); //màu sắc

		Geometric::RenderOutline(outLineSize, color_data2, g_screen); //vẽ ra màn hình 

		player_power.Show(g_screen); //show ra màn hình
		player_money.Show(g_screen);

		for (int i = 0;i < threats_list.size(); i++) //chạy vòng for để xuất hiện các mối hiểm họa 
		{
			ThreatsObject* p_threat = threats_list.at(i); //load từng cái 1 
			if (p_threat != NULL) //nếu có gía trị
			{
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_); //chạy các hàm để tạo ra quái 
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);

				//check va chạm đạn của quái vs nhân vật 
				SDL_Rect rect_player = p_player.GetRectFrame(); //lấy kích thước của nhân vật, chú ý lấy 1 frame chứ ko phải ảnh 8 frame vì ta chỉ load 1 frame
				bool bCol1 = false; //gán trạng thái kiểm tra va chạm bằng false
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list(); //lấy danh sách của đạn của quái
				for (int jj = 0; jj < tBullet_list.size(); jj++)
				{
					BulletObject* pt_bullet = tBullet_list.at(jj); //lấy ra từng viên đạn của quái 
					if (pt_bullet) //nếu lấy thành công
					{
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player); //check va chạm giữa nhân vật và đạn của quái
						if (bCol1) //nếu va chạm
						{
							p_threat->RemoveBullet(jj); //hủy viên đạn 
							break;
						}
					}
				}

				//check va chạm giữa nhân vật và quái 
				SDL_Rect rect_threat = p_threat->GetRectFrame(); //lấy kích thước của quái, lấy 1 frame
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat); //check va chạm giữa nhân vật và quái 
				if (bCol1 || bCol2) //nếu 1 trong 2 xảy ra( va chạm vs nhau) thì nhân vật game chết 
				{
					Mix_Chunk* beep_sound = Mix_LoadWAV("sound//no.wav");
						if (beep_sound != NULL)
						Mix_PlayChannel(-1, beep_sound, 0);
					//tạo ra vụ nổ khi va chạm nhân vật với các loại đạn hoặc quái
					int	width_exp_frame = exp_main.get_frame_width(); 
					int height_exp_frame = exp_main.get_frame_height();
					for (int ex = 0; ex < 4; ex++)
					{
						int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
						int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - height_exp_frame*0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.Show(g_screen);
						SDL_RenderPresent(g_screen);
					}

					num_die++; //khi va chạm cộng số lần chết lên
					if (num_die <=3) //nếu số lần chết <=3,hồi sinh lại nhân vật
					{
						p_player.SetRect(0, 0); //set lại kích thước
						p_player.set_comeback_time(2); //thời gian trở lại khi chết 
						SDL_Delay(1000); //thời gian delay 
						player_power.Decrease(); //giảm 1 mạng
						player_power.Render(g_screen); //load lại ra màn hình	
						continue;
					}
					else //nếu lớn hơn 3 thì quit game
					{
						int play_die = 0;
						while (play_die ==0)
						{
							play_die = MenuGame::MenuDie(g_screen, g_font_MENU, "Play Again", "Exit", "img//die.png");
							if (play_die == 1)
							{
								close();
								break;
							}
							if (play_die == 0)
							{
								close();
								goto reset;
							}
						}
					}

				}

			}
		}

		int frame_exp_width = exp_threat.get_frame_width(); //lấy ra kích thước frame vụ nổ của tấm ảnh 
		int frame_exp_height = exp_threat.get_frame_height();

		//check va chạm giữa đạn của nhân vật và quái 
		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list(); //lấy danh sách các viên đạn của nhân vật game
		for (int r = 0; r < bullet_arr.size(); ++r) //kiểm tra từng viên đạn 
		{
			BulletObject* p_bullet = bullet_arr.at(r); //lôi từng viên đạn ra
			if (p_bullet != NULL) //nếu có giá trị 
			{
				for (int t =0; t < threats_list.size(); ++t) //kiểm tra từng viên đạn vs từng đối tượng quái vật 
				{
					ThreatsObject* obj_threat = threats_list.at(t); //lôi từng quái ra
					if (obj_threat != NULL) //nếu có giá trị
					{

						SDL_Rect tRect; //lấy đc kích thước của quái
						tRect.x = obj_threat->GetRect().x; //kích thước của quái
						tRect.y = obj_threat->GetRect().y;
						//vì quái chúng ta load là từng frame 1 nên chúng ta chỉ lấy chiều dài và cao của 1 frame chứ ko lấy cả ảnh gồm 8 frame
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect(); //do viên đạn ko có khung hình frame nên ta gọi kích thước trực tiếp luôn 

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect); //kiểm tra có va chạm không 

						if (bCol) //nếu xảy ra va chạm,= true 
						{
							Mix_Chunk* beep_sound = Mix_LoadWAV("sound//no.wav");
						if (beep_sound != NULL)
						Mix_PlayChannel(-1, beep_sound, 0);
							mark_value++; //cộng điểm lên khi bắn chết quái vật
							for (int ex = 0; ex < NUM_FRAME_EXP; ++ex) //chạy các khung hình frame vụ nổ
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5; //vị trí đặt tấm ảnh vụ nổ vào, đạn chạm vào đâu nổ tại đấy
								int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
								//trừ đi 1 lượng frame_exp_...*0.5 để tâm ảnh frame vụ nổ vào đúng vị trí viên đạn để ko bị lệch 

								exp_threat.set_frame(ex);//xem đang ở frame bao nhiêu 
								exp_threat.SetRect(x_pos, y_pos); //set kích thước cho nó
								exp_threat.Show(g_screen); //show lên màn hình 
							}

							p_player.RemoveBullet(r);//xóa viên đạn 
							obj_threat->Free(); //xóa bỏ hoàn toàn quái đó
							threats_list.erase(threats_list.begin() + t); //loại bỏ quái đó khỏi danh sách các quái 

						}

					}
				}
			}
		}

		//In ra thời gian của game
		std::string str_time = "Time: "; //gán
		Uint32 time_val = SDL_GetTicks() / 1000;//thời điểm hiện tại (đổi ra s)
		Uint32 val_time = 300 - time_val;//đếm ngược thời gian từ 300 trở lại 
		if (val_time <= 0) //nếu thời gian bé hơn 0,hết giờ thì kết thúc game
		{
			int play_die = 0;
			while (play_die ==0)
			{
				play_die = MenuGame::MenuDie(g_screen, g_font_MENU, "Play Again", "Exit", "img//die.png");
				if (play_die == 1)
				{
					close();
					break;
				}
				if (play_die == 0)
				{
					close();
					goto reset;
				}
			}
		}
		else //ngược lại
		{
			std::string str_val = std::to_string(val_time);//show text lên trên
			str_time += str_val;//nhãn cộng với thời gian

			time_game.SetText(str_time);//set nội dung 
			time_game.LoadFromRenderText(font_time, g_screen);//truyền vào font 
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15); //load ra màn hình , load ra ở ngóc bên phải nên lấy tọa độ như vậy 
		}
		
		//hiển thị điểm và tiền (tương tự vs in ra thời gian của game)
		std::string val_str_mark = std::to_string(mark_value); 
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15); //tọa độ lấy để hiển thị ra màn hình

		int money_count = p_player.GetMoneyCount();
		if (money_count == 1000)
		{
			int win = 0;
			while (win ==0)
			{
				win = MenuGame::MenuDie(g_screen, g_font_MENU, "Play Again", "Exit", "img//win.png");
				if (win == 1)
				{
					close();
					break;
				}
				if (win == 0)
				{
					close();
					goto reset;
				}
			}
		}
		std::string money_str = std::to_string(money_count);

		money_game.SetText(money_str);
		money_game.LoadFromRenderText(font_time, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15); //tọa độ lấy để hiển thị ra màn hình

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks(); //thời gian thực sự đã trôi qua
		int time_one_frame = 1000/FRAME_PER_SECOND; //1 frame chạy mất bao lâu (1s=1000ms)

		if (real_imp_time < time_one_frame) 
		{
			int delay_time = time_one_frame - real_imp_time; //nếu <0 thì ko cần độ trễ, nếu >0 thì tạo độ trễ
			if (delay_time >= 0) 
			    SDL_Delay(delay_time); //tạo độ trễ,tạo sự cân bằng
		}

	}

	for (int i = 0; i < threats_list.size(); i++) //hủy toàn bộ threat mình đã tạo để tránh rác bộ nhớ 
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if (p_threat)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}

	threats_list.clear(); 

	close();
    return 0;
}