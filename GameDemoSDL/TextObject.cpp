
#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject() //khởi tạo các giá trị đầu tiên 
{
	text_color_.r = 255; 
	text_color_.g = 255;
	text_color_.b = 255;
	texture_ = NULL;
}

TextObject::~TextObject() //hàm hủy
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_); //đưa tấm ảnh về dạng sdl_surface
	if (text_surface) //kiểm tra xem có đưa về đc ko,nếu ok
	{
		texture_ = SDL_CreateTextureFromSurface(screen, text_surface); //chuyển đổi từ surface sang texture
		width_ = text_surface->w; //lấy đc chiều dài
		height_ = text_surface->h; //lấy đc chiều cao

		SDL_FreeSurface(text_surface); //giải phóng surface đi 
	}

	return texture_ != NULL; //nếu khác NULL trả về true, = trả về false
}

void TextObject::Free() //hàm giải phóng
{
	if (texture_ != NULL) //nếu texture  có giá trị
	{
		SDL_DestroyTexture(texture_); //truyền texture vào
		texture_ = NULL; //gàn bằng NUll
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}

void TextObject::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255 , 0 , 0 };
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255 , 255 , 255 };
		text_color_ = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0 , 0 , 0 };
		text_color_ = color;
	}
}

void TextObject::RenderText(SDL_Renderer* screen,
		                    int xp, int yp, 
					        SDL_Rect* clip /*= NULL*/ , 
					        double angle /*= 0.0*/ , 
					        SDL_Point* center /*= NULL*/ , 
					        SDL_RendererFlip flip /*= SDL_FLIP_NONE*/ )
{
	SDL_Rect renderQuad = { xp, yp, width_, height_ }; 
	if (clip != NULL) 
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}