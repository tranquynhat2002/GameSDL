
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20 //có tối đa 20 các dạng map

class TileMat : public BaseObject  //hàm load ảnh của từng ô map 
{
public:
	TileMat() {;}
	~TileMat() {;}
};


class GameMap //lớp quản lí việc xây dựng map, lắp toàn bộ tilemap vào các vị trí ô vuông của map 
{
public:
	GameMap() {;}
	~GameMap() {;}

	void LoadMap(char* name); //hàm đọc các thông tin trong file sơ đồ map, file text
	void LoadTiles(SDL_Renderer* screen); //hàm load toàn bộ hình ảnh của TileMap, vd 1 phải load ảnh 1
	void DrawMap(SDL_Renderer* screen); //hàm lắp toàn bộ hình ảnh vào các vị trí 
	Map getMap() const {return game_map_;}; //kiểm tra các file bên trong 
	void SetMap(Map& map_data){game_map_ = map_data;}; //hàm set map mới
private:
	Map game_map_; //chứa toàn bộ thông tin về bản đồ, gồm trạng thái, vị trí, chỉ số của ô
	TileMat tile_mat[MAX_TILES]; //đối tương lưu trữ hình ảnh 
};

#endif