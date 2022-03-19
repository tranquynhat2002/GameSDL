
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunc.h"

class TextObject 
{
public:
	TextObject();
	~TextObject();

	enum TextColor //các màu cơ bản
	{
		RED_TEXT = 0, //màu đỏ
		WHITE_TEXT = 1, //trắng
		BLACK_TEXT = 2, //đen
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen); //hàm load font chữ ra màn hình
	void Free();//hàm giải phóng các text
	
	void SetColor(Uint8 red, Uint8 green, Uint8 blue); //hàm set màu bằng truyền trực tiếp màu 
	void SetColor(int type); //hàm set các màu cơ bản của mình

	void RenderText(SDL_Renderer* screen,
		            int xp, int yp, 
					SDL_Rect* clip = NULL, 
					double angle = 0.0, 
					SDL_Point* center = NULL, 
					SDL_RendererFlip flip = SDL_FLIP_NONE); //hàm show text ra màn hình

	int GetWidth() const { return width_ ;} //lấy ra chiều rộng
	int GetHeight() const { return height_ ;} //lấy ra chiều cao

	void SetText(const std::string& text) { str_val_ = text; } //truyền nội dung text vào  
	std::string GetText() const { return str_val_; } //hàm trả ra

private:
	std::string str_val_; //lưu nội dung của text
	SDL_Color text_color_; //màu sắc của text
	SDL_Texture* texture_; //quản lí text đấy 
	int width_; //chiều rộng text
	int height_; //chiều cao text
};




#endif