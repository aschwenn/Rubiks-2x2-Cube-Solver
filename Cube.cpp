#include "Cube.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Cube::Cube()
{
	createEmpty();
}

void Cube::createEmpty() {
	up.makeBlank();
	right.makeBlank();
	left.makeBlank();
	front.makeBlank();
	back.makeBlank();
	down.makeBlank();
}

Cube::Cube(const Cube &c) {
	up = c.getSide(0);
	right = c.getSide(1);
	left = c.getSide(2);
	front = c.getSide(3);
	back = c.getSide(4);
	down = c.getSide(5);
}

Side Cube::getSide(int a) const {
	switch (a) {
	case 0: return up;
	case 1: return right;
	case 2: return left;
	case 3: return front;
	case 4: return back;
	case 5: return down;
	default: cerr << "Copy constructor error." << endl; exit(0);
	}
}

void Cube::set(int side, int a, int b, int c, int d) {
	/* 0 = up, 1 = right, 2 = left, 3 = front, 4 = back, 5 = down */
	switch (side) {
	case 0:
		up.setupper(Row(a, b));
		up.setlower(Row(c, d));
		break;
	case 1:
		right.setupper(Row(a, b));
		right.setlower(Row(c, d));
		break;
	case 2:
		left.setupper(Row(a, b));
		left.setlower(Row(c, d));
		break;
	case 3:
		front.setupper(Row(a, b));
		front.setlower(Row(c, d));
		break;
	case 4:
		back.setupper(Row(a, b));
		back.setlower(Row(c, d));
		break;
	case 5:
		down.setupper(Row(a, b));
		down.setlower(Row(c, d));
		break;
	default: cerr << "This should not be possible."; exit(1);
	}
}

char num2char(int a) {
	switch (a) {
	case 0: return 'w';
	case 1: return 'r';
	case 2: return 'b';
	case 3: return 'o';
	case 4: return 'g';
	case 5: return 'y';
	default: cerr << "num2char error"; exit(2);
	}
}

void Cube::displayCube() {
	cout << endl;
	cout << "    " << num2char(up.getupper().getleft()) << " " << num2char(up.getupper().getright()) << endl;
	cout << "    " << num2char(up.getlower().getleft()) << " " << num2char(up.getlower().getright()) << endl;
	cout << num2char(left.getupper().getleft()) << " " << num2char(left.getupper().getright()) << " "
		<< num2char(front.getupper().getleft()) << " " << num2char(front.getupper().getright()) << " "
		<< num2char(right.getupper().getleft()) << " " << num2char(right.getupper().getright()) << " "
		<< num2char(back.getupper().getleft()) << " " << num2char(back.getupper().getright()) << endl;
	cout << num2char(left.getlower().getleft()) << " " << num2char(left.getlower().getright()) << " "
		<< num2char(front.getlower().getleft()) << " " << num2char(front.getlower().getright()) << " "
		<< num2char(right.getlower().getleft()) << " " << num2char(right.getlower().getright()) << " "
		<< num2char(back.getlower().getleft()) << " " << num2char(back.getlower().getright()) << endl;
	cout << "    " << num2char(down.getupper().getleft()) << " " << num2char(down.getupper().getright()) << endl;
	cout << "    " << num2char(down.getlower().getleft()) << " " << num2char(down.getlower().getright()) << endl;
	cout << endl;
}

bool Cube::isValid() {
	/* Make sure that there are exactly four of each color */
	int colors[6] = { 0 };
	Side* sides[6];
	sides[0] = &up;
	sides[1] = &right;
	sides[2] = &left;
	sides[3] = &front;
	sides[4] = &back;
	sides[5] = &down;
	for (int i = 0; i < 6; ++i) {
		Side temp = *sides[i];
		colors[temp.getupper().getleft()]++;
		colors[temp.getupper().getright()]++;
		colors[temp.getlower().getleft()]++;
		colors[temp.getlower().getright()]++;
	}
	if (!(colors[0] == 4 && colors[1] == 4 && colors[2] == 4 && colors[3] == 4 && colors[4] == 4 && colors[5] == 4)) {
		return false;
	}

	return true;
}

bool Cube::isSolved() {
	if (up.same() && right.same() && left.same() && front.same() && back.same() && down.same()) {
		if (front.color == 0 && back.color == 5) {
			switch (right.color) {
			case 1: if (up.color == 2 && left.color == 3 && down.color == 4) return true;
			case 2: if (up.color == 3 && left.color == 4 && down.color == 1) return true;
			case 3: if (up.color == 4 && left.color == 1 && down.color == 2) return true;
			case 4: if (up.color == 1 && left.color == 2 && down.color == 3) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
		else if (front.color == 1 && back.color == 3) {
			switch (right.color) {
			case 2: if (up.color == 0 && left.color == 4 && down.color == 5) return true;
			case 0: if (up.color == 4 && left.color == 5 && down.color == 2) return true;
			case 4: if (up.color == 5 && left.color == 2 && down.color == 0) return true;
			case 5: if (up.color == 2 && left.color == 0 && down.color == 4) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
		else if (front.color == 2 && back.color == 4) {
			switch (right.color) {
			case 0: if (up.color == 1 && left.color == 5 && down.color == 3) return true;
			case 1: if (up.color == 5 && left.color == 3 && down.color == 0) return true;
			case 5: if (up.color == 3 && left.color == 0 && down.color == 1) return true;
			case 3: if (up.color == 0 && left.color == 1 && down.color == 5) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
		else if (front.color == 3 && back.color == 1) {
			switch (right.color) {
			case 0: if (up.color == 2 && left.color == 5 && down.color == 4) return true;
			case 2: if (up.color == 5 && left.color == 4 && down.color == 0) return true;
			case 5: if (up.color == 4 && left.color == 0 && down.color == 2) return true;
			case 4: if (up.color == 0 && left.color == 2 && down.color == 5) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
		else if (front.color == 4 && back.color == 2) {
			switch (right.color) {
			case 0: if (up.color == 3 && left.color == 5 && down.color == 1) return true;
			case 3: if (up.color == 5 && left.color == 1 && down.color == 0) return true;
			case 5: if (up.color == 1 && left.color == 0 && down.color == 3) return true;
			case 1: if (up.color == 0 && left.color == 3 && down.color == 5) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
		else if (front.color == 5 && back.color == 0) {
			switch (right.color) {
			case 1: if (up.color == 4 && left.color == 3 && down.color == 2) return true;
			case 4: if (up.color == 3 && left.color == 2 && down.color == 1) return true;
			case 3: if (up.color == 2 && left.color == 1 && down.color == 4) return true;
			case 2: if (up.color == 1 && left.color == 4 && down.color == 3) return true;
			default: cerr << "Invalid cube."; exit(0);
			}
		}
	}
	return false;
}

/* PERMUTATION NOTE:
 * Right-side corresponds with upper and left-side corresponds with lower.
 * When going between non-corresponding halves, flip() must be used to correct the alignment.
 */

void Cube::U() {
	up.CW(); // turn clockwise on "up" side
	Row temp = front.getupper(); // save to a temporary row as it will be replaced
	front.setupper(right.getupper());
	right.setupper(back.getupper());
	back.setupper(left.getupper());
	left.setupper(temp);
	cout << "U ";
}

void Cube::Up() {
	up.CCW();
	Row temp = front.getupper();
	front.setupper(left.getupper());
	left.setupper(back.getupper());
	back.setupper(right.getupper());
	right.setupper(temp);
	cout << "U' ";
}

void Cube::U2() {
	up.CCW();
	Row temp = front.getupper();
	front.setupper(left.getupper());
	left.setupper(back.getupper());
	back.setupper(right.getupper());
	right.setupper(temp);
	up.CCW();
	temp = front.getupper();
	front.setupper(left.getupper());
	left.setupper(back.getupper());
	back.setupper(right.getupper());
	right.setupper(temp);
	cout << "U2 ";
}

void Cube::R() {
	right.CW();
	Row temp = front.getrightside();
	front.setrightside(down.getrightside());
	down.setrightside(back.getleftside().flip());
	back.setleftside(up.getrightside().flip());
	up.setrightside(temp);
	cout << "R ";
}

void Cube::Rp() {
	right.CCW();
	Row temp = front.getrightside();
	front.setrightside(up.getrightside());
	up.setrightside(back.getleftside().flip());
	back.setleftside(down.getrightside().flip());
	down.setrightside(temp);
	cout << "R' ";
}

void Cube::R2() {
	right.CW();
	Row temp = front.getrightside();
	front.setrightside(down.getrightside());
	down.setrightside(back.getleftside().flip());
	back.setleftside(up.getrightside().flip());
	up.setrightside(temp);
	right.CW();
	temp = front.getrightside();
	front.setrightside(down.getrightside());
	down.setrightside(back.getleftside().flip());
	back.setleftside(up.getrightside().flip());
	up.setrightside(temp);
	cout << "R2 ";
}

void Cube::L() {
	left.CW();
	Row temp = front.getleftside();
	front.setleftside(up.getleftside());
	up.setleftside(back.getrightside().flip());
	back.setrightside(down.getleftside().flip());
	down.setleftside(temp);
	cout << "L ";
}

void Cube::Lp() {
	left.CCW();
	Row temp = front.getleftside();
	front.setleftside(down.getleftside());
	down.setleftside(back.getrightside().flip());
	back.setrightside(up.getleftside().flip());
	up.setleftside(temp);
	cout << "L' ";
}

void Cube::L2() {
	left.CW();
	Row temp = front.getleftside();
	front.setleftside(up.getleftside());
	up.setleftside(back.getrightside().flip());
	back.setrightside(down.getleftside().flip());
	down.setleftside(temp);
	left.CW();
	temp = front.getleftside();
	front.setleftside(up.getleftside());
	up.setleftside(back.getrightside().flip());
	back.setrightside(down.getleftside().flip());
	down.setleftside(temp);
	cout << "L2 ";
}

void Cube::F() {
	front.CW();
	Row temp = up.getlower();
	up.setlower(left.getrightside().flip());
	left.setrightside(down.getupper());
	down.setupper(right.getleftside().flip());
	right.setleftside(temp);
	cout << "F ";
}

void Cube::Fp() {
	front.CCW();
	Row temp = up.getlower();
	up.setlower(right.getleftside());
	right.setleftside(down.getupper().flip());
	down.setupper(left.getrightside());
	left.setrightside(temp.flip());
	cout << "F' ";
}

void Cube::F2() {
	front.CW();
	Row temp = up.getlower();
	up.setlower(left.getrightside().flip());
	left.setrightside(down.getupper());
	down.setupper(right.getleftside().flip());
	right.setleftside(temp);
	front.CW();
	temp = up.getlower();
	up.setlower(left.getrightside().flip());
	left.setrightside(down.getupper());
	down.setupper(right.getleftside().flip());
	right.setleftside(temp);
	cout << "F2 ";
}

void Cube::B() {
	back.CW();
	Row temp = right.getrightside();
	right.setrightside(down.getlower().flip());
	down.setlower(left.getleftside());
	left.setleftside(up.getupper().flip());
	up.setupper(temp);
	cout << "B ";
}

void Cube::Bp() {
	back.CCW();
	Row temp = right.getrightside();
	right.setrightside(up.getupper());
	up.setupper(left.getleftside().flip());
	left.setleftside(down.getlower());
	down.setlower(temp.flip());
	cout << "B' ";
}

void Cube::B2() {
	back.CW();
	Row temp = right.getrightside();
	right.setrightside(down.getlower().flip());
	down.setlower(left.getleftside());
	left.setleftside(up.getupper().flip());
	up.setupper(temp);
	back.CW();
	temp = right.getrightside();
	right.setrightside(down.getlower().flip());
	down.setlower(left.getleftside());
	left.setleftside(up.getupper().flip());
	up.setupper(temp);
	cout << "B2 ";
}

void Cube::D() {
	down.CW();
	Row temp = front.getlower();
	front.setlower(left.getlower());
	left.setlower(back.getlower());
	back.setlower(right.getlower());
	right.setlower(temp);
	cout << "D ";
}

void Cube::Dp() {
	down.CCW();
	Row temp = front.getlower();
	front.setlower(right.getlower());
	right.setlower(back.getlower());
	back.setlower(left.getlower());
	left.setlower(temp);
	cout << "D' ";
}

void Cube::D2() {
	down.CW();
	Row temp = front.getlower();
	front.setlower(left.getlower());
	left.setlower(back.getlower());
	back.setlower(right.getlower());
	right.setlower(temp);
	down.CW();
	temp = front.getlower();
	front.setlower(left.getlower());
	left.setlower(back.getlower());
	back.setlower(right.getlower());
	right.setlower(temp);
	cout << "D2 ";
}