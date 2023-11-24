#pragma once
class Note {
public:
    Note(short Ntype, int Ncourse, int Nviolecity, int Ntime/*ms*/):type(Ntype), course(Ncourse), violecity(Nviolecity), outTime(Ntime) {}
	~Note() {}
	int getY()const;
	int getX()const;
	int getoutTime()const;
	int getviolecity()const;
	short gettype()const;
	int getcourse()const;

	void drop();

	bool getappearance()const;
	void appear();
	void disappear();
private:
	short type;//1~4分别代表蓝色、黄色、红色和长条
	int violecity;//音符下降速度
	bool appearance = false;//音符的生存状态
	int course;/*1~9轨道数*/
	int y = 0;
    int outTime;//音符出现的时间
};