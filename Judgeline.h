#pragma once
#include"Note.h"
class Judgeline {
public:
	Judgeline() = default;
	~Judgeline() {}
	//�����ж���perfect��good��miss��ͬʱ��Ҫ��¼perfect��good��miss������
	void perfect();
	void good();
	void miss();
	int getperfectNum()const;
	int getgoodNum()const;

	//��ɫ����ɫ����ɫ�������������ж�����
	void bluejudge(Note&a,char c);
	void yellowjudge(Note& a,char c);
	void redjudge(Note& a,char c);
	void longjudge(Note& a, char c);

	void buttonTOjudge(char c, Note& a);

	void calculate(int size);// ͳ�Ʒ���

	//����ܷ֡�������������
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