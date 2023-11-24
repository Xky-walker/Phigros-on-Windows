#pragma once
#include"Note.h"
class Judgeline {
public:
	Judgeline() = default;
	~Judgeline() {}
	//三种判定：perfect，good，miss，同时需要记录perfect，good，miss的数量
	void perfect();
	void good();
	void miss();
	int getperfectNum()const;
	int getgoodNum()const;

	//蓝色、黄色、红色、长条音符的判定函数
	void bluejudge(Note&a,char c);
	void yellowjudge(Note& a,char c);
	void redjudge(Note& a,char c);
	void longjudge(Note& a, char c);

	void buttonTOjudge(char c, Note& a);

	void calculate(int size);// 统计分数

	//输出总分、评级、连击数
	int getsummary() const;
	char getmark() const;
	int getcombo()const;
private:
	int summary = 0;
	char mark = 'F';

	int Tempcombo = 0;
	int Maxcombo = 0;
	int perfectNum = 0;
	int goodNum = 0;
	int missNum = 0;
};