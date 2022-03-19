
#include "stdafx.h"
#include "BulletObject.h"
 
 
BulletObject::BulletObject()
{
    x_val_ = 0; //thiết lập các giá trị 
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = SPHERE_BULLET;
}
 
 
BulletObject::~BulletObject()
{
 
}
 
bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false; 
    if (bullet_type_ == LASER_BULLET)
    {
        ret = LoadImage("img//laser_bullet.png", des);
    }
    else
    {
        ret = LoadImage("img//player_bullet.png", des);
    }
 
    return ret;
}
 
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT) //nếu bắn sang bên phải
    {
        rect_.x += x_val_; //tăng dần tọa độ viên đạn lên 
        if (rect_.x > x_border) //nếu vượt quá màn hình 
        {
            is_move_ = false; //xóa đạn 
        }
    }
    else if (bullet_dir_ == DIR_LEFT) //nếu bắn sang bên trái 
    {
        rect_.x -= x_val_; //giảm tọa độ của viên đạn 
        if (rect_.x < 0) //nếu vượt quá màn hình 
        {
            is_move_ = false; //xóa đạn 
        }
    }
    else if (bullet_dir_ == DIR_UP) //tương tự với các trường hợp còn lại 
    {
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
 
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
 
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
 
        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
 
        }
 
        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}