#pragma once
//C++11中引进boost中的chrono库，可实现高精度时钟
#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer {
public:
	Timer();
	~Timer() {}
	void update();
	//获取毫秒
	long long getTimerMilliSec();
private:
	time_point<high_resolution_clock>_start;
};

void Timer::update() {
	_start = high_resolution_clock::now();
}

Timer::Timer() {
	update();
}

//当前时钟减去开始时钟
long long Timer::getTimerMilliSec() {
	return duration_cast<milliseconds>(high_resolution_clock::now() - _start).count();
}