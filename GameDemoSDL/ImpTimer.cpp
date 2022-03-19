
#include "stdafx.h"
#include "ImpTimer.h"
#include "CommonFunc.h"


ImpTimer::ImpTimer()
{
	start_tick_ = 0; //khởi tạo
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
	is_started_ = true; 
	is_paused_ = false;
	start_tick_ = SDL_GetTicks(); //liên tục lấy thời gian trôi qua
}

void ImpTimer::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void ImpTimer::paused()
{
	if (is_started_ == true && is_paused_ == false) //kiểm tra xem đã bắt đầu và chưa dừng mới dừng
	{
		is_paused_ = true ;
		paused_tick_ = SDL_GetTicks() - start_tick_; //thời gian hiện tại trừ đi thời gian đã trôi qua ra thời điểm pause
	}
}

void ImpTimer::unpaused()
{
	if (is_paused_ == true) //nếu đang dừng mới unpaused
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_; //thời gian hiện tại - đi thời gian paused
		paused_tick_ = 0;//gán bằng 0 để nếu paused sẽ lấy thời gian paused mới 
	}
}

int ImpTimer::get_ticks()
{
	if (is_started_ == true) //chỉ xem thời điểm hiện tại khi đang chạy
	{
		if (is_paused_ == true) //nếu đang dừng 
		{
			return paused_tick_; //trả về thời điểm paused
		}
		else
		{
			return SDL_GetTicks() - start_tick_; //trả về thời gian hiện tại - đi thời điểm ban đầu ra thời gian trôi qua 
		}
	}

	return 0;
}

//kiểm tra xem thời điểm hiện tại đang chạy hay dừng
bool ImpTimer::is_started() 
{
	return is_started_;
}

bool ImpTimer::is_paused()
{
	return is_paused_;
}