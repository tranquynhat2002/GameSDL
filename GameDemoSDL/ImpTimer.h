
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer 
{
public:
	ImpTimer();
	~ImpTimer();

	void start(); //bắt đầu chạy,đếm thời gian 
	void stop(); //dừng lại 
	void paused(); //tạm dừng
	void unpaused(); //hủy tạm dừng

	int get_ticks(); //thời điểm hiện tại

	bool is_started(); //hàm trả lại trạng thái
	bool is_paused();

private:
	int start_tick_; //thời điểm bắt đầu chạy
	int paused_tick_; //thời điểm tạm dừng

	bool is_paused_; 
	bool is_started_; 
};

#endif
