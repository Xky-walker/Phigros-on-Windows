#pragma once
#include<string>
using namespace std;
//歌曲类，记录歌名，最佳成绩、评级，最近成绩、评级
class Music {
public:
	Music() = default;
	Music(string Name,int LastS,char LastM,int BestS,char BestM) :name(Name),lastSummary(LastS),lastMark(LastM),bestSummary(BestS),bestMark(BestM) {}
	~Music() {}

	string getname()const;
	int getlastSummary()const;
	char getlastMark()const;
	int getbestSummary()const;
	char getbestMark()const;
	void refresh(int newS,char newM);//更新最佳分数和评级
private:
	string name;
	int lastSummary = 0;
	char lastMark = 'F';
	int bestSummary = 0;
	char bestMark = 'F';
};