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
	short type;//1~4�ֱ������ɫ����ɫ����ɫ�ͳ���
	int violecity;//�����½��ٶ�
	bool appearance = false;//����������״̬
	int course;/*1~9�����*/
	int y = 0;
    int outTime;//�������ֵ�ʱ��
};