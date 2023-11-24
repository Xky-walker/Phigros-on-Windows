#include"Note.h"

int Note::getY() const {
	return y;
}
int Note::getX() const {
	return (100 * course + 50);
}
int Note::getoutTime() const {
	return outTime;
}
int Note::getviolecity() const {
	return violecity;
}
short Note::gettype() const {
	return type;
}
int Note::getcourse()const {
	return course;
}

void Note::drop() {
	y += violecity;
}

bool Note::getappearance() const {
	return appearance;
}
void Note::appear() {
	appearance = true;
}
void Note::disappear() {
	appearance = false;
	y = -100;
}