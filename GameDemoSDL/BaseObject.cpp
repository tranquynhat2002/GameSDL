
#include "stdafx.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	Free(); //xóa đối tượng trước và trỏ sang vùng nhớ mới, tránh hiện tượng rác 
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	// kiểm tra xem có load dc ảnh ko 
	if (load_surface != NULL) //load dc ảnh 
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)); //xóa phông 
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface); //thông số và thuộc tính của tấm ảnh
		if (new_texture != NULL) //gán thông số và thuộc tính của tấm ảnh
		{
			rect_.w = load_surface->w; 
			rect_.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface); //giải phóng
    }

	p_object_ = new_texture; 

	return p_object_ != NULL; //=Null return false, !=Null return true
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */) //load tấm ảnh lên nền	
{
	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, clip, &renderquad); //đẩy toàn bộ thông số từ p_object lên des thông qua renderquar
}

void BaseObject::Free() //giải phóng các đối tượng 
{
	if(p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_); //hủy p_object 
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}