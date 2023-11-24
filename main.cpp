#include"Music.h"
#include"Note.h"
#include"Judgeline.h"
#include"Timer.h"
#include<graphics.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#include <fstream>
#include <sstream>
#include<Windows.h>
#include <string>
#include<vector>

using namespace std;
//图像大小设置为1200*800
//以下x，y坐标的原点为图像左上角

IMAGE Background, Guide, Face[2], Album[2], bNote, yNote, rNote, lNote, Jline;//图片对象
void loadimg() {
	loadimage(&Background, "./images/Entrance.jpg");
	loadimage(&Guide, "./images/Guide.png");

	loadimage(&Face[0], "./images/Music1_small.png");
	loadimage(&Face[1], "./images/Music2_small.jpg");

	loadimage(&Album[0], "./images/Music1.png");
	loadimage(&Album[1], "./images/Music2.jpg");

	loadimage(&bNote, "./images/BlueNote.jpg");
	loadimage(&yNote, "./images/YellowNote.jpg");
	loadimage(&rNote, "./images/RedNote.jpg");
	loadimage(&lNote, "./images/LongNote.jpg");
	loadimage(&Jline, "./images/Jline.jpg");
}

void setFont(int fontH) {
	LOGFONT k;
	gettextstyle(&k);// 获取当前字体设置
	k.lfHeight = fontH;// 设置字体高度
	_tcscpy_s(k.lfFaceName, _T("Microsoft YaHei"));// 设置字体
	k.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
	settextstyle(&k);// 设置字体样式
}

//在主界面展示最佳成绩和最近成绩
void showLastGrade(int Lsummary, char Lmark,int Bsummary,char Bmark,short position,string Songname) {
	outtextxy(70, position, Songname.c_str());
	outtextxy(70, position + 35, _T("最近成绩："));
	outtextxy(70, position + 70, _T("最近评级："));
	outtextxy(70, position + 105, _T("最佳成绩："));
	outtextxy(70, position + 140, _T("最佳评级："));
	char LS[9] = { 0 };
	_itoa_s(Lsummary, LS, 10);//将int转化为char[]，10进制
	char BS[9] = { 0 };
	_itoa_s(Bsummary, BS, 10);
	outtextxy(180, position+35, LS);
	outtextxy(180, position+70, Lmark);
	outtextxy(180, position + 105, BS);
	outtextxy(180, position + 140, Bmark);
}


int main() {
	initgraph(1200,800);
	loadimg();
	
	while (1) {   //主循环
		//基础信息初始化
		short Selection = 0;//曲目的按顺序选择
		Music* ptr;
		ptr = new Music[2];
		
		//读取相应的最近的记录
		{
			ifstream is1("./record/Music1.txt", ios_base::in);
			string Name1;
			int LastS1;//最近分数
			char LastM1;//最近评级
			int BestS1;//最佳分数
			char BestM1;//最佳评级
			is1 >> Name1 >> LastS1 >> LastM1 >> BestS1 >> BestM1;
			ptr[0] = Music(Name1, LastS1, LastM1, BestS1, BestM1);
			is1.close();

			ifstream is2("./record/Music2.txt", ios_base::in);
			string Name2;
			int LastS2;
			char LastM2;
			int BestS2;
			char BestM2;
			is2 >> Name2 >> LastS2 >> LastM2 >> BestS2 >> BestM2;
			ptr[1] = Music(Name2, LastS2, LastM2, BestS2, BestM2);
			is2.close();
		}

		BeginBatchDraw();
		while (1) {//主界面
			putimage(0, 0, &Background);//进入背景
			putimage(20, 100, &Face[0]);//歌曲1封面
			putimage(20, 440, &Face[1]);//歌曲2封面
			setFont(30);
			//1
			showLastGrade(ptr[0].getlastSummary(), ptr[0].getlastMark(), ptr[0].getbestSummary(), ptr[0].getbestMark(), 120, "劣等上等");
			//2
			showLastGrade(ptr[1].getlastSummary(), ptr[1].getlastMark(), ptr[1].getbestSummary(), ptr[1].getbestMark(), 460, "有友如你");
			//显示歌曲的选择
			setFont(45);
			switch (Selection) {
			case 0:
				outtextxy(0, 755, _T("当前歌曲选择：1（上下键选择）"));
				break;
			case 1:
				outtextxy(0, 755, _T("当前歌曲选择：2（上下键选择）"));
			}

			FlushBatchDraw();

			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {//使用按位与运算，使键的按下和松开和返回值第一位一一对应
				while (1) {
					putimage(0, 0, &Guide);//空格跳转到教程页面
					FlushBatchDraw();
					if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
						cleardevice();
						break;
					}
				}
			}

			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				Selection = 0;//进行歌曲的选中
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				Selection = 1;
			}

			if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
				cleardevice();
				break;
			}
		}
		EndBatchDraw();

		//定义Note对象数组
		vector<Note>notes;
		//根据选中进行乐谱的初始化
		if (Selection == 0) {
			ifstream inFile("./book/Music1.csv", ios::in);
			string line;
			while (getline(inFile, line))//按行读取.csv中的数据
			{
				string field;
				int a, b, c, d;
				istringstream sin(line); //将整行字符串line读入到字符串流sin中

				getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
				a = atoi(field.c_str());// 将刚刚读取的字符串转换成int
				getline(sin, field, ',');
				b = atoi(field.c_str());
				getline(sin, field, ',');
				c = atoi(field.c_str());
				getline(sin, field, ',');
				d = atoi(field.c_str());

				notes.push_back(Note(a, b, c, d));
				//一个音符构造完成
			}
			inFile.close();
		}
		else if (Selection == 1) {
			ifstream inFile("./book/Music2.csv", ios::in); string line;
			while (getline(inFile, line))//按行读取.csv中的数据
			{
				string field;
				int a, b, c, d;
				istringstream sin(line); //将整行字符串line读入到字符串流sin中

				getline(sin, field, ','); //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
				a = atoi(field.c_str());// 将刚刚读取的字符串转换成int
				getline(sin, field, ',');
				b = atoi(field.c_str());
				getline(sin, field, ',');
				c = atoi(field.c_str());
				getline(sin, field, ',');
				d = atoi(field.c_str());

				notes.push_back(Note(a, b, c, d));
				//一个音符构造完成
			}
			inFile.close();
		}

		Judgeline player;
		Timer TC;
		if (Selection == 0) {
			mciSendString("open ./music/Music1.wav alias A", NULL, 0, NULL);//播放音乐
			mciSendString("play A", NULL, 0, NULL);
		}
		else if (Selection == 1) {
			mciSendString("open ./music/Music2.wav alias A", NULL, 0, NULL);//播放音乐	
			mciSendString("play A", NULL, 0, NULL);
		}		

		TC.update();

		BeginBatchDraw();//双缓冲区绘图
		while (TC.getTimerMilliSec() <= notes.back().getoutTime() + 6000) {
			putimage(0, 0, &Album[Selection]);
			putimage(0, 586, &Jline);
			
			//打歌情况的实时显示
			{
				setFont(30);

				outtextxy(0, 0, _T("perfect:"));
				outtextxy(0, 30, _T("good:   "));
				outtextxy(0, 60, _T("combo: "));
				//显示perfect数
				char perfectNOW[6] = { 0 };
				_itoa_s(player.getperfectNum(), perfectNOW, 10);
				outtextxy(100, 0, perfectNOW);
				//显示good数
				char goodNOW[6] = { 0 };
				_itoa_s(player.getgoodNum(), goodNOW, 10);
				outtextxy(100, 30, goodNOW);
				//显示combo数
				char comboNOW[6] = { 0 };
				_itoa_s(player.getcombo(), comboNOW, 10);
				outtextxy(100, 60, comboNOW);
			}

			for (int i = 0; i < notes.size(); ++i) {
				if (notes[i].getoutTime()<=TC.getTimerMilliSec()&&notes[i].getY()==0) {
					notes[i].appear();//音符的产生
				}
				if (notes[i].getappearance() == true) {   //音符的绘制
					switch (notes[i].gettype()) {
					case 1:
						putimage(notes[i].getX(), notes[i].getY(), &bNote);
						break;
					case 2:
						putimage(notes[i].getX(), notes[i].getY(), &yNote);
						break;
					case 3:
						putimage(notes[i].getX(), notes[i].getY(), &rNote);
						break;
					case 4:
						putimage(notes[i].getX(), notes[i].getY(), &lNote);
						break;
					}
				}
			}
			FlushBatchDraw();//刷新页面

			for (int i = 0; i < notes.size(); ++i) {   //音符状态判断
				if (notes[i].getappearance() == true) {   //在谱面区域的音符运动
					notes[i].drop();
				}
				if (notes[i].getappearance() == false)
					continue;
			}
			//每条轨道上的最近选取
			int index[9] = { 0,0,0,0,0,0,0,0,0 };//代表各个轨道上出现的音符是全曲的第几个音符
			int distance[9] = { 600, 600, 600, 600, 600, 600, 600, 600, 600 };
			for (int i = 0; i < notes.size(); ++i) {
				if (notes[i].getappearance()==true&&abs(600 - notes[i].getY()) < distance[notes[i].getcourse()-1]) {//判断：音符是否存在且高度小于上一个音符的高度
					index[notes[i].getcourse() - 1] = i;
					distance[notes[i].getcourse() - 1] = abs(600 - notes[i].getY());//将距离更新
				}
			}
			//对于最近的音符进行分轨道判定
			player.buttonTOjudge('A', notes[index[0]]);
			player.buttonTOjudge('S', notes[index[1]]);
			player.buttonTOjudge('D', notes[index[2]]);
			player.buttonTOjudge('F', notes[index[3]]);
			player.buttonTOjudge('G', notes[index[4]]);
			player.buttonTOjudge('H', notes[index[5]]);
			player.buttonTOjudge('J', notes[index[6]]);
			player.buttonTOjudge('K', notes[index[7]]);
			player.buttonTOjudge('L', notes[index[8]]);						
			
			for (int i = 0; i < notes.size(); ++i) {
			//miss消失
				if (notes[i].gettype()<=3&&notes[i].getY() > 680) {
					notes[i].disappear();
					player.miss();
				}
				if (notes[i].getappearance()==true&&notes[i].gettype() == 4&& notes[i].getY() > 625) {
					notes[i].disappear();
					player.miss();
				}
			}

			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {   //esc退出
				break;
			}
		}
		EndBatchDraw();
		//结束音乐
		mciSendString("stop A", NULL, 0, NULL);
		mciSendString("close A", NULL, 0, NULL);
		cleardevice();

		player.calculate(notes.size());
		//最佳成绩的记录
		if (ptr[Selection].getbestSummary() < player.getsummary()) {
			ptr[Selection].refresh(player.getsummary(), player.getmark());
		}
		//成绩写入TXT文件
		switch (Selection) {
		case 0: {
			ofstream os1("./record/Music1.txt", ios_base::out);
			os1 << ptr[0].getname() << ' ' << player.getsummary() << ' ' << player.getmark() << ' ' << ptr[0].getbestSummary() << ' ' << ptr[0].getbestMark();
			os1.close();
			break;
		}
		case 1: {
			ofstream os2("./record/Music2.txt", ios_base::out);
			os2 << ptr[1].getname() << ' ' << player.getsummary() << ' ' << player.getmark() << ' ' << ptr[1].getbestSummary() << ' ' << ptr[1].getbestMark();
			os2.close();
			break;
		}
		}
		
		BeginBatchDraw();
		while (1) {
			putimage(0, 0, &Album[Selection]);
			{
				setFont(40);
				outtextxy(200, 300, _T("总分： "));
				outtextxy(200, 340, _T("评级： "));
				outtextxy(200, 380, _T("轻击方向左键返回主界面"));

				//分数显示
				char score[9] = { 0 };
				_itoa_s(player.getsummary(), score, 10);
				outtextxy(320, 300, score);
				outtextxy(320, 340, player.getmark());
			}
			FlushBatchDraw();

			//左键下一步
			if (GetAsyncKeyState(VK_LEFT) & 0x8000){
				cleardevice();
				break;
			}
		}
		EndBatchDraw();
		delete[] ptr;
	}
	return 0;
}