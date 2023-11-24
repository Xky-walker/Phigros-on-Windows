#pragma once
//C++11������boost�е�chrono�⣬��ʵ�ָ߾���ʱ��
#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer {
public:
	Timer();
	~Timer() {}
	void update();
	//��ȡ����
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

//��ǰʱ�Ӽ�ȥ��ʼʱ��
long long Timer::getTimerMilliSec() {
	return duration_cast<milliseconds>(high_resolution_clock::now() - _start).count();
}