
#include "stdafx.h"
#include "game_map.h"

void GameMap::LoadMap(char* name)
{
	FILE* fp = NULL; 
	fopen_s(&fp, name, "rb"); //đọc file 
	if (fp == NULL) //nếu ko thành công 
	{
		return;
	}

	game_map_.max_x_ = 0; //thời điểm ban đầu
	game_map_.max_y_ = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)	//load lần lượt các chỉ số của hàng
	{
		for (int j = 0; j < MAX_MAP_X; j++) //load lần lượt các chỉ số của cột
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]); //đọc dữ liệu
			int val = game_map_.tile[i][j]; //lưu để kiểm tra
			if (val > 0) //nếu giá trị ko phải 0 mà là 1,2,3,..
			{
				if (j > game_map_.max_x_) //nếu j lớn hơn chỉ số hiện tại của max_x_
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_) //nếu i lớn hơn chỉ số hiện tại của max_y_
				{
					game_map_.max_y_ = i;
				}
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE; //sau khi load xong sẽ đc giá trị tối đa của bản đồ 
	game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;

	game_map_.start_x_ = 0; //lưu lại để đôi khi mình cần load lại 
	game_map_.start_y_ = 0;

	game_map_.file_name_ = name;
	fclose(fp); //đóng chương trình

}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[30]; //tên chỉ số của tấm ảnh, 30 là kí tự 
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILES; i++) //chạy chỉ số của tấm ảnh
	{
		sprintf_s(file_img, "map/%d.png", i); //chuyển đổi chỉ số vào tên file 

		fopen_s(&fp, file_img, "rb"); //kiểm tra xem mở đc file ko 
		if (fp == NULL) //nếu tấm ảnh ko có hoặc ko đọc đc thì bỏ qua
		{
			continue;
		}

		fclose(fp); //nếu đọc thì close con trỏ đó đi 

		tile_mat[i].LoadImage(file_img, screen); //load sẵn ảnh lên, chỉ chờ lắp ráp 
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_/TILE_SIZE; //vị trí ô thứ bao nhiêu (lấy phần nguyên của đoạn từ đầu đến start_x chia cho kích thước 1 ô)
	x1 = (game_map_.start_x_%TILE_SIZE)*-1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_/TILE_SIZE; //vị trí ô thứ bao nhiêu 
	y1 = (game_map_.start_y_%TILE_SIZE)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) //chạy chỉ số của các ô trong map 
	{
		map_x = game_map_.start_x_/TILE_SIZE; //sau mỗi lần chạy phải lấy lại map_x
		for (int j = x1; j < x2; j += TILE_SIZE) //chạy chỉ số của các ô trong map
		{
			int val = game_map_.tile[map_y][map_x];
			if (val > 0) //nếu lớn hơn 0, vd 1,2,3.. thì lắp ảnh vào
			{
				tile_mat[val].SetRect(j, i); //lấy tọa độ của ô
				tile_mat[val].Render(screen); //lắp ảnh vào 
			}
			map_x++; //tăng dần các ô của map lên
		}
		map_y++; //tăng dần các ô của map lên 
	}
}