#include "Row.h"

Row::Row(){
	same = false;
	color = -1;
	left = 0;
	right = 0;
}

Row::Row(const Row & r){
	same = false;
	color = -1;
	left = r.getleft();
	right = r.getright();
}

Row::Row(int l, int r) {
	same = false;
	color = -1;
	left = l;
	right = r;
}

int Row::getleft() const {
	return left;
}

int Row::getright() const {
	return right;
}

void Row::setleft(int c) {
	left = c;
}

void Row::setright(int c) {
	right = c;
}

Row Row::flip() {
	int temp = left;
	left = right;
	right = temp;
	return Row(left,right);
}