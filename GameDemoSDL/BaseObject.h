
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y){rect_.x = x, rect_.y = y;} //set kích thước cho rect 
	SDL_Rect GetRect() const {return rect_;} //lấy ra kích thước của tấm ảnh 
	SDL_Texture* GetObject() const {return p_object_;}

	virtual bool LoadImage(std::string path, SDL_Renderer* screen); //lấy ảnh 
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object_; //biến lưu trữ hình ảnh
	SDL_Rect rect_; //biến lưu kích thước của ảnh
};



#endif