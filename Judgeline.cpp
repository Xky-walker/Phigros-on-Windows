#include"Judgeline.h"
#include<Windows.h>

void Judgeline::perfect() {
	++perfectNum;
	++Tempcombo;//操作临时连击数
	Maxcombo = (Maxcombo <= Tempcombo) ? Tempcombo : Maxcombo;//刷新最大连击数
}
void Judgeline::good() {
	++goodNum;
	++Tempcombo;
	Maxcombo = (Maxcombo <= Tempcombo) ? Tempcombo : Maxcombo;
}
void Judgeline::miss() {
	Tempcombo = 0;
	++missNum;
}
int Judgeline::getperfectNum()const {
	return perfectNum;
}
int Judgeline::getgoodNum()const {
	return goodNum;
}

void Judgeline::bluejudge(Note&a,char c) {
	if (GetAsyncKeyState(c) & 0x8000) {
		int distance = 600 - a.getY();//通过点击键盘时音符到判定线的距离来判定perfect、good和miss
			if (distance<70 && distance>-30) {
				this->perfect();
					a.disappear();
			}
			else if ((distance < 150 && distance >= 70) || distance >= -80&&distance<=-30) {
				this->good();
					a.disappear();
			}
			else if (distance >= 150 && distance <= 260) {
				this->miss();
				a.disappear();
			}
	}
}
void Judgeline::yellowjudge(Note& a,char c) {//黄色音符属于接住，只判定perfect
	if (GetAsyncKeyState(c) & 0x8000) {
		int distance = 600 - a.getY();
		if (distance<80 && distance>-30) {
			this->perfect();
			a.disappear();
		}
	}
}
void Judgeline::redjudge(Note& a,char c) {
	if (GetAsyncKeyState(c) & 0x8000) {
		int distance = 600 - a.getY();
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && distance<70 && distance>-30) {
			this->perfect();
			a.disappear();
		}
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) &&( (distance < 150 && distance >= 70) && (distance >= -60 &&distance<=-30) )){
			this->good();
			a.disappear();
		}
	}
}
void Judgeline::longjudge(Note& a,char c) {
	int distance = 600 - a.getY();
	if (GetAsyncKeyState(c) & 0x8000) {
		if (distance < 30 && distance >= -10) {
			this->perfect();
			a.disappear();
		}
	}
}

void Judgeline::buttonTOjudge(char c, Note&a) {
	switch (a.gettype()) {
	case 1:
		this->bluejudge(a,c);
		break;
	case 2:
		this->yellowjudge(a,c);
		break;
	case 3:
		this->redjudge(a,c);
		break;
	case 4:
		this->longjudge(a, c);
		break;
	}
}


//计分系统
void Judgeline::calculate(int size) {
	int unit = 900000 / size + 1;
	int gradehit = perfectNum * unit + static_cast<int>(0.65 * goodNum * unit);
	int grade1 = (gradehit < 900000 ? gradehit : 900000);
	int grade2 = (Maxcombo * 100000) / size;
	summary = grade1 + grade2;

	if (summary == 1000000) {
		mark = 'P';//φ
	}		
	else if (summary < 1000000 && summary >= 950000) {
		mark = 'V';
	}
	else if (summary < 950000 && summary >= 850000) {
		mark = 'S';
	}
	else if (summary < 850000 && summary >= 700000) {
		mark = 'A';
	}
	else if (summary < 700000 && summary >= 500000) {
		mark = 'B';
	}
	else if (summary < 500000 && summary >= 140000) {
		mark = 'C';
	}
	else {
		mark = 'F';
	}
}

int Judgeline::getsummary()const {
	return summary;
}
char Judgeline::getmark()const {
	return mark;
}
int Judgeline::getcombo()const {
	return Tempcombo;
}