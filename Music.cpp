#include"Music.h"
string Music::getname()const {
	return name;
}
int Music::getlastSummary()const {
	return lastSummary;
}
char Music::getlastMark()const {
	return lastMark;
}
int Music::getbestSummary()const {
	return bestSummary;
}
char Music::getbestMark()const {
	return bestMark;
}

void Music::refresh(int newS, char newM) {
	bestSummary = newS;
	bestMark = newM;
}