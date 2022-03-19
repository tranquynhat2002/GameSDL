
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL; //xây dựng nên form window cho game
static SDL_Renderer* g_screen = NULL; //
static SDL_Event g_event; //sự kiên từ bàn phím, chuột

// Màn hình
const int FRAME_PER_SECOND = 25; // fps, số frame trên 1 s
const int SCREEN_WIDTH = 1280; //Chiều rộng
const int SCREEN_HEIGHT = 640; //Chiều cao 
const int SCREEN_BPP = 32; //Chỉ số mixer pixel

//Màu sắc phông ảnh(màu trắng)
const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 0Xff; 


#define BLANK_TILE 0 //trạng thái của ô, =0 tức là ko có j,khác 0 là có ảnh hay j đó ở ô đó
#define TILE_SIZE 64 //định nghĩa kích thước mắt lưới-1 ô

#define MAX_MAP_X 400 //định nghĩa kích thước của file map 400 cột 
#define MAX_MAP_Y 10 //định nghĩa kích thước của file map 10 hàng 


#define STATE_MONEY 4 //đồ hỗ trợ(tiền), 4 là số trong bảng bản đồ map text 
#define STATE_FLAG 10 //lá cờ, 10 là số trong bản đồ map text

typedef struct Input //cấu trúc dành cho việc di chuyển 
{
	int left_; //sang trái
	int right_; //tiến lên
	int up_; //dơ lên trên
	int down_; //dơ xuống dưới
	int jump_; //nhảy
};

typedef struct Map //đối tượng thế hiện vị trí,trạng thái và chỉ số của 1 ô trong map 
{
	int start_x_; //vị trí của ô, vd ô 10 là 10*64=640
	int start_y_;

	int max_x_; //chỉ số của ô đấy, ô thứ bao nhiêu
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X]; //mảng 2 chiều lưu toàn bộ trạng thái của ô đấy 
	char* file_name_; //biến lưu tên file 
};


namespace SDLCommonFunc //hàm xử lý tất cả các đối tượng xảy ra va chạm
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); 
}

#endif