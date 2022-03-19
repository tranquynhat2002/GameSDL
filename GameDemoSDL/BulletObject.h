
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
 
#include "BaseObject.h"
#include "CommonFunc.h"
 
class BulletObject : public BaseObject //kế thừa từ lớp BaseObject 
{
 
public:
    BulletObject();
    ~BulletObject();
 
    enum BulletDir 
    {
        DIR_RIGHT = 20, //bắn sang phải 
        DIR_LEFT = 21, //bắn sang trái 
        DIR_UP = 22, //bắn lên trên
        DIR_UP_LEFT = 23, //bắn lên trên sang trái 
        DIR_UP_RIGHT = 24, //bắn lên trên sang phải 
        DIR_DOWN_LEFT = 25, //bắn xuống dưới bên trái 
        DIR_DOWN_RIGHT = 26, //bắn xuống dưới bên phải 
        DIR_DOWN = 27, //bắn xuống dưới
    };
 
    enum BulletType
    {
        SPHERE_BULLET = 50, //đạn sphere
        LASER_BULLET = 51, //đạn laser
    };
 
    void set_x_val(const int& xVal) {x_val_ = xVal;} //hàm set giá trị 
    void set_y_val(const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;} //hàm get giá trị 
    int get_y_val() const {return y_val_;}
 
    void set_is_move(const bool& isMove) {is_move_ = isMove;} //hàm set, get cho is_move
    bool get_is_move() const {return is_move_;}
 
    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;} //hàm set,get cho bullet_dir
    unsigned int get_bullet_dir() const {return bullet_dir_;}
 
    void set_bullet_type(const unsigned int& bulletType) {bullet_type_ = bulletType;}  //hàm set,get cho bullet_type
    unsigned int get_bullet_type() const {return bullet_type_;}
 
    void HandleMove(const int& x_border, const int& y_border); //hàm xử lí vấn đề di chuyển cho viên đạn 
    bool LoadImgBullet(SDL_Renderer* des); //hàm load hình ảnh của các loại đạn 
private:
    int x_val_; //biến lưu lượng giá trị thay đổi bao nhiêu 
    int y_val_; //biến lưu lượng giá trị thay đổi bao nhiêu 
    bool is_move_; //biến kiểm tra xem đạn như thế nào để xóa đạn,nếu ra ngoài màn hình thì xóa 
    unsigned int bullet_dir_; //hướng của đạn 
    unsigned int bullet_type_; //loại đạn 
 
};

#endif;