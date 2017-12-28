#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <time.h>

#include "Cube.h"

using namespace std;

string iv = "Invalid cube -- no solutions possible. Make sure you have entered your cube's state correctly.";
bool errorsig;

int readChar() {
	while (true) {
		char c = getchar();
		if (cin.fail()) { cerr << "Input error."; exit(0); }
		c = tolower(c);
		switch (c) {
		case 'w': return 0;
		case 'r': return 1;
		case 'b': return 2;
		case 'o': return 3;
		case 'g': return 4;
		case 'y': return 5;
		}
		cout << "Input invalid. Please enter the first letter of the color: " << endl;
	}
}

bool opposite(int a, int b) {
	/* Returns true if the two colors are opposites */
	if (a == 1 && b == 3) { return true; }
	if (a == 3 && b == 1) { return true; }
	if (a == 2 && b == 4) { return true; }
	if (a == 4 && b == 2) { return true; }
	if (a == 0 && b == 5) { return true; }
	if (a == 5 && b == 0) { return true; }
	return false;
}

void firstLayer(Cube &c) {
	/* Reference: 0 = up, 1 = right, 2 = left, 3 = front, 4 = back, 5 = down */
	if (c.getSide(0).same() && c.getSide(0).color == 0) {
		cout << "Side is already solved.";
		return;
	}

	/* Color notation:
	* 0: white
	* 1: red
	* 2: blue
	* 3: orange
	* 4: green
	* 5: yellow
	*/
	
	Cube temp = c;
	string a = "Cubie is already in position.";

	/* We want the top face to be all white */
	/* Find and place top left cubie */
	cout << "Placing the top left cubie: ";
	Side u = c.getSide(0);
	Side b = c.getSide(4);
	Side l = c.getSide(2);
	Side r = c.getSide(1);
	Side f = c.getSide(3);
	Side d = c.getSide(5);
	if (!u.getupper().getleft() &&
		b.getupper().getright() == 3 &&
		l.getupper().getleft() == 4) {
		// already in correct position
		cout << a;
	}
	// check for cubie in top left of another face
	else if (!l.getupper().getleft() && u.getupper().getleft() == 3) {
		c.Up();
		c.Lp();
	}
	else if (!f.getupper().getleft() && u.getlower().getleft() == 3) {
		c.Lp();
	}
	else if (!r.getupper().getleft() && u.getlower().getright() == 3) {
		c.U();
		c.Lp();
	}
	else if (!b.getupper().getleft() && u.getupper().getright() == 3) {
		c.U2();
		c.Lp();
	}
	else if (!d.getupper().getleft() && f.getlower().getleft() == 3) {
		c.L2();
	}
	// check for cubie in top right
	else if (!u.getupper().getright() && r.getupper().getright() == 3) {
		c.Up();
	}
	else if (!l.getupper().getright() && f.getupper().getleft() == 3) {
		c.Up();
		c.Fp();
		c.Lp();
	}
	else if (!f.getupper().getright() && r.getupper().getleft() == 3) {
		c.Fp();
		c.Lp();
	}
	else if (!r.getupper().getright() && b.getupper().getleft() == 3) {
		c.U();
		c.Fp();
		c.Lp();
	}
	else if (!b.getupper().getright() && l.getupper().getleft() == 3) {
		c.U2();
		c.Fp();
		c.Lp();
	}
	else if (!d.getupper().getright() && f.getlower().getright() == 4) {
		c.R();
		c.Fp();
		c.Lp();
	}
	// check for cubie in bottom left
	else if (!u.getlower().getright() && f.getupper().getright() == 3) {
		c.U2();
	}
	else if (!l.getlower().getleft() && b.getlower().getright() == 3) {
		c.D();
		c.F();
		c.Lp();
	}
	else if (!f.getlower().getleft() && l.getlower().getright() == 3) {
		c.F();
		c.Lp();
	}
	else if (!r.getlower().getleft() && f.getlower().getright() == 3) {
		c.Dp();
		c.F();
		c.Lp();
	}
	else if (!b.getlower().getleft() && r.getlower().getright() == 3) {
		c.D2();
		c.F();
		c.Lp();
	}
	else if (!d.getlower().getleft() && b.getlower().getright() == 4) {
		c.L2();
		c.U();
	}
	// check for cubie in bottom right
	else if (!u.getlower().getleft() && l.getupper().getright() == 3) {
		c.U();
	}
	else if (!l.getlower().getright() && f.getlower().getleft() == 4) {
		c.D();
		c.F2();
		c.Lp();
	}
	else if (!f.getlower().getright() && r.getlower().getleft() == 4) {
		c.F2();
		c.Lp();
	}
	else if (!r.getlower().getright() && b.getlower().getleft() == 4) {
		c.Dp();
		c.F2();
		c.Lp();
	}
	else if (!b.getlower().getright() && l.getlower().getleft() == 4) {
		c.D2();
		c.F2();
		c.Lp();
	}
	else if (!d.getlower().getright() && b.getlower().getleft() == 3) {
		c.D2();
		c.L2();
	}
	else {
		temp.displayCube();
		throw iv;
	}
	// check that cube was properly placed
	u = c.getSide(0);
	b = c.getSide(4);
	l = c.getSide(2);
	r = c.getSide(1);
	f = c.getSide(3);
	d = c.getSide(5);
	if (!(!u.getupper().getleft() &&
		b.getupper().getright() == 3 &&
		l.getupper().getleft() == 4)) {
		cout << endl;
		temp.displayCube();
		throw "Invalid cube or logic error -- cube cannot be solved.";
	}
	cout << flush << endl;

	/* The top left cubie is placed correctly */
	/* Find and place the top right cubie */
	temp = c;
	cout << "Placing the top right cubie: ";
	if (!u.getupper().getright() &&
		b.getupper().getleft() == 3 &&
		r.getupper().getright() == 2) {
		// already in correct position
		cout << a;
	}
	// check for cubie in top left of another face
	else if (!u.getupper().getleft() && b.getupper().getright() == 2) {
		// not possible
		throw iv;
	}
	else if (!l.getupper().getleft() && u.getupper().getleft() == 2) {
		// not possible
		throw iv;
	}
	else if (!f.getupper().getleft() && u.getlower().getleft() == 2) {
		c.F();
		c.R();
	}
	else if (!r.getupper().getleft() && u.getlower().getright() == 2) {
		c.U();
		c.Fp();
		c.Up();
		c.F2();
		c.R();
	}
	else if (!b.getupper().getleft() && u.getupper().getright() == 2) {
		c.R2();
		c.Fp();
		c.R();
	}
	else if (!d.getupper().getleft() && f.getlower().getleft() == 2) {
		c.D();
		c.R2();
	}
	// check for cubie in top right
	else if (!l.getupper().getright() && f.getupper().getleft() == 2) {
		c.F();
		c.Rp();
		c.Fp();
		c.R();
	}
	else if (!f.getupper().getright() && r.getupper().getleft() == 2) {
		c.R();
	}
	else if (!r.getupper().getright() && b.getupper().getleft() == 2) {
		c.U();
		c.F();
		c.Up();
		c.Fp();
		c.R();
	}
	else if (!b.getupper().getright() && l.getupper().getleft() == 2) {
		c.U2();
		c.F();
		c.U2();
		c.Fp();
		c.R();
	}
	else if (!d.getupper().getright() && f.getlower().getright() == 3) {
		c.R2();
	}
	// check for cubie in bottom left
	else if (!u.getlower().getleft() && l.getupper().getright() == 2) {
		c.Fp();
		c.D();
		c.Fp();
		c.R();
	}
	else if (!l.getlower().getleft() && b.getlower().getright() == 2) {
		c.D();
		c.F2();
		c.R();
	}
	else if (!f.getlower().getleft() && l.getlower().getright() == 2) {
		c.F2();
		c.R();
	}
	else if (!r.getlower().getleft() && f.getlower().getright() == 2) {
		c.Dp();
		c.F2();
		c.R();
	}
	else if (!b.getlower().getleft() && r.getlower().getright() == 2) {
		c.D2();
		c.F2();
		c.R();
	}
	else if (!d.getlower().getleft() && b.getlower().getright() == 3) {
		c.D2();
		c.R2();
	}
	// check for cubie in bottom right
	else if (!u.getlower().getright() && f.getupper().getright() == 2) {
		c.Rp();
		c.Fp();
		c.R();
	}
	else if (!l.getlower().getright() && f.getlower().getleft() == 3) {
		c.D();
		c.Fp();
		c.R();
	}
	else if (!f.getlower().getright() && r.getlower().getleft() == 3) {
		c.Fp();
		c.R();
	}
	else if (!r.getlower().getright() && b.getlower().getleft() == 3) {
		c.Dp();
		c.Fp();
		c.R();
	}
	else if (!b.getlower().getright() && l.getlower().getleft() == 3) {
		c.D2();
		c.Fp();
		c.R();
	}
	else if (!d.getlower().getright() && b.getlower().getleft() == 2) {
		c.Dp();
		c.R2();
	}
	else {
		temp.displayCube();
		throw iv;
	}
	// check that cube was properly placed
	u = c.getSide(0);
	b = c.getSide(4);
	l = c.getSide(2);
	r = c.getSide(1);
	f = c.getSide(3);
	d = c.getSide(5);
	if (!(!u.getupper().getleft() &&
		b.getupper().getright() == 3 &&
		l.getupper().getleft() == 4) ||
		!(!u.getupper().getright() &&
			b.getupper().getleft() == 3 &&
			r.getupper().getright() == 2)) {
		cout << endl;
		temp.displayCube();
		throw "Invalid cube or logic error -- cube cannot be solved.";
	}
	cout << flush << endl;

	/* The top cubies are placed correctly */
	/* Find and place the bottom left cubie */
	temp = c;
	cout << "Placing the bottom left cubie: ";
	if (!u.getlower().getleft() &&
		f.getupper().getleft() == 1 &&
		l.getupper().getright() == 4) {
		// already in correct position
		cout << a;
	}
	// check for cubie in top left of another face
	else if (!u.getupper().getleft() && l.getupper().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!l.getupper().getleft() && u.getupper().getleft() == 4) {
		// not possible
		throw iv;
	}
	else if (!f.getupper().getleft() && u.getlower().getleft() == 4) {
		c.Fp();
		c.Bp();
		c.Lp();
		c.B();
	}
	else if (!r.getupper().getleft() && u.getlower().getright() == 4) {
		c.Fp();
	}
	else if (!b.getupper().getleft() && u.getupper().getright() == 4) {
		// not possible
		throw iv;
	}
	else if (!d.getupper().getleft() && f.getlower().getleft() == 4) {
		c.D();
		c.F2();
	}
	// check for cubie in top right
	else if (!u.getupper().getright() && r.getupper().getright() == 4) {
		// not possible
		throw iv;
	}
	else if (!l.getupper().getright() && f.getupper().getleft() == 4) {
		c.F();
		c.Rp();
		c.Dp();
		c.R();
		c.F();
	}
	else if (!f.getupper().getright() && r.getupper().getleft() == 4) {
		c.F();
		c.Dp();
		c.F();

	}
	else if (!r.getupper().getright() && b.getupper().getleft() == 4) {
		// not possible
		throw iv;
	}
	else if (!b.getupper().getright() && l.getupper().getleft() == 4) {
		// not possible
		throw iv;
	}
	else if (!d.getupper().getright() && f.getlower().getright() == 1) {
		c.F2();
	}
	// check for cubie in bottom left
	else if (!l.getlower().getleft() && b.getlower().getright() == 4) {
		c.D();
		c.Bp();
		c.Lp();
		c.B();
	}
	else if (!f.getlower().getleft() && l.getlower().getright() == 4) {
		c.Bp();
		c.Lp();
		c.B();
	}
	else if (!r.getlower().getleft() && f.getlower().getright() == 4) {
		c.Dp();
		c.Bp();
		c.Lp();
		c.B();
	}
	else if (!b.getlower().getleft() && r.getlower().getright() == 4) {
		c.D2();
		c.Bp();
		c.Lp();
		c.B();
	}
	else if (!d.getlower().getleft() && b.getlower().getright() == 1) {
		c.D2();
		c.F2();
	}
	// check for cubie in bottom right
	else if (!u.getlower().getright() && f.getupper().getright() == 4) {
		c.Rp();
		c.Dp();
		c.R();
		c.F();
	}
	else if (!l.getlower().getright() && f.getlower().getleft() == 1) {
		c.F();
	}
	else if (!f.getlower().getright() && r.getlower().getleft() == 1) {
		c.Dp();
		c.F();
	}
	else if (!r.getlower().getright() && b.getlower().getleft() == 1) {
		c.D2();
		c.F();
	}
	else if (!b.getlower().getright() && l.getlower().getleft() == 1) {
		c.D();
		c.F();
	}
	else if (!d.getlower().getright() && b.getlower().getleft() == 4) {
		c.Dp();
		c.F2();
	}
	else {
		temp.displayCube();
		throw iv;
	}
	// check that cube was properly placed
	u = c.getSide(0);
	b = c.getSide(4);
	l = c.getSide(2);
	r = c.getSide(1);
	f = c.getSide(3);
	d = c.getSide(5);
	if (!(!u.getupper().getleft() &&
			b.getupper().getright() == 3 &&
			l.getupper().getleft() == 4) ||
		(!(!u.getupper().getright() &&
			b.getupper().getleft() == 3 &&
			r.getupper().getright() == 2)) ||
		!(!u.getlower().getleft() &&
			f.getupper().getleft() == 1 &&
			l.getupper().getright() == 4)) {
		cout << endl;
		temp.displayCube();
		throw "Invalid cube or logic error -- cube cannot be solved.";
	}
	cout << flush << endl;

	/* The top and left cubies are placed correctly */
	/* Find and place the final bottom right cubie */
	temp = c;
	cout << "Placing the bottom right cubie: ";
	if (!u.getlower().getright() &&
		f.getupper().getright() == 1 &&
		r.getupper().getleft() == 2) {
		// already in correct position
	}
	// check for cubie in top left of another face
	else if (!l.getupper().getleft() && u.getupper().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!f.getupper().getleft() && u.getlower().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!r.getupper().getleft() && u.getlower().getright() == 1) {
		c.Rp();
		c.Dp();
		c.R();
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	else if (!b.getupper().getleft() && u.getupper().getright() == 1) {
		// not possible
		throw iv;
	}
	else if (!d.getupper().getleft() && f.getlower().getleft() == 1) {
		c.D();
		c.Rp();
		c.D2();
		c.R();
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	// check for cubie in top right
	else if (!l.getupper().getright() && f.getupper().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!f.getupper().getright() && r.getupper().getleft() == 1) {
		c.Rp();
		c.D();
		c.R();
		c.B();
		c.R();
		c.Bp();
	}
	else if (!r.getupper().getright() && b.getupper().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!b.getupper().getright() && l.getupper().getleft() == 1) {
		// not possible
		throw iv;
	}
	else if (!d.getupper().getright() && f.getlower().getright() == 2) {
		c.Rp();
		c.D2();
		c.R();
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	// check for cubie in bottom left
	else if (!l.getlower().getleft() && b.getlower().getright() == 1) {
		c.D2();
		c.Lp();
		c.Fp();
		c.L();
	}
	else if (!f.getlower().getleft() && l.getlower().getright() == 1) {
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	else if (!r.getlower().getleft() && f.getlower().getright() == 1) {
		c.Lp();
		c.Fp();
		c.L();
	}
	else if (!b.getlower().getleft() && r.getlower().getright() == 1) {
		c.Dp();
		c.Lp();
		c.Fp();
		c.L();
	}
	else if (!d.getlower().getleft() && b.getlower().getright() == 2) {
		c.D2();
		c.Lp();
		c.F2();
		c.L();
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	// check for cubie in bottom right
	else if (!l.getlower().getright() && f.getlower().getleft() == 2) {
		c.D();
		c.B();
		c.R();
		c.Bp();
	}
	else if (!f.getlower().getright() && r.getlower().getleft() == 2) {
		c.B();
		c.R();
		c.Bp();
	}
	else if (!r.getlower().getright() && b.getlower().getleft() == 2) {
		c.Dp();
		c.B();
		c.R();
		c.Bp();
	}
	else if (!b.getlower().getright() && l.getlower().getleft() == 2) {
		c.D2();
		c.B();
		c.R();
		c.Bp();
	}
	else if (!d.getlower().getright() && b.getlower().getleft() == 1) {
		c.Dp();
		c.Lp();
		c.F2();
		c.L();
		c.D();
		c.Lp();
		c.Fp();
		c.L();
	}
	else {
		temp.displayCube();
		throw iv;
	}
	// check that cube was properly placed
	u = c.getSide(0);
	b = c.getSide(4);
	l = c.getSide(2);
	r = c.getSide(1);
	f = c.getSide(3);
	d = c.getSide(5);
	if ((!(!u.getupper().getleft() &&
			b.getupper().getright() == 3 &&
			l.getupper().getleft() == 4) ||
		!(!u.getlower().getright() &&
			f.getupper().getright() == 1 &&
			r.getupper().getleft() == 2)) ||
		(!(!u.getupper().getright() &&
			b.getupper().getleft() == 3 &&
			r.getupper().getright() == 2)) ||
		!(!u.getlower().getleft() &&
			f.getupper().getleft() == 1 &&
			l.getupper().getright() == 4)) {
		cout << endl;
		temp.displayCube();
		throw "Invalid cube or logic error -- cube cannot be solved.";
	}
	cout << flush;
}

void orientFinal(Cube &c) {
	/* Reference: 0 = up, 1 = right, 2 = left, 3 = front, 4 = back, 5 = down */
	if (c.getSide(5).same() && c.getSide(5).getupper().getleft() == 5) {
		cout << "Flipping the cube: ";
		c.L2();
		c.R2();
		cout << endl; 
		cout << "Side is already solved.";
		return;
	}
	if (!c.isValid()) { throw iv; }

	/* Color notation:
	* 0: white
	* 1: red
	* 2: blue
	* 3: orange
	* 4: green
	* 5: yellow
	*/

	Cube temp = c;

	cout << "Flipping the cube: ";
	c.L2();
	c.R2();
	cout << endl;

	Side u = c.getSide(0);
	Side b = c.getSide(4);
	Side l = c.getSide(2);
	Side r = c.getSide(1);
	Side f = c.getSide(3);
	Side d = c.getSide(5);
	
	/* Determine which of the orientations the cube is in */
	int or = -1; // orientation
	cout << "To align: ";
	string n = "No alignment necessary.";
	// U orientation == 0
	if ((u.getupper().getright() == 5 && u.getlower().getright() == 5) &&
		(l.getupper().getleft() == 5 && l.getupper().getright() == 5)){
		cout << n;
		or = 0;
	}
	else if ((u.getupper().getleft() == 5 && u.getupper().getright() == 5) &&
		(f.getupper().getleft() == 5 && f.getupper().getright() == 5)) {
		c.U();
		or = 0;
	}
	else if ((u.getupper().getleft() == 5 && u.getlower().getleft() == 5) &&
		(r.getupper().getleft() == 5 && r.getupper().getright() == 5)) {
		c.U2();
		or = 0;
	}
	else if ((u.getlower().getleft() == 5 && u.getlower().getright() == 5) &&
		(b.getupper().getleft() == 5 && b.getupper().getright() == 5)) {
		c.Up();
		or = 0;
	}
	// T orientation == 1
	else if ((u.getupper().getright() == 5 && u.getlower().getright() == 5) &&
		(b.getupper().getright() == 5 && f.getupper().getleft() == 5)) {
		cout << n;
		or = 1;
	}
	else if ((u.getupper().getleft() == 5 && u.getupper().getright() == 5) &&
		(l.getupper().getright() == 5 && r.getupper().getleft() == 5)) {
		c.U();
		or = 1;
	}
	else if ((u.getupper().getleft() == 5 && u.getlower().getleft() == 5) &&
		(b.getupper().getleft() == 5 && f.getupper().getright() == 5)) {
		c.U2();
		or = 1;
	}
	else if ((u.getlower().getleft() == 5 && u.getlower().getright() == 5) &&
		(l.getupper().getleft() == 5 && r.getupper().getright() == 5)) {
		c.Up();
		or = 1;
	}
	// L orientation == 2
	else if ((u.getupper().getleft() == 5 && u.getlower().getright() == 5) &&
		(r.getupper().getright() == 5 && f.getupper().getleft() == 5)) {
		cout << n;
		or = 2;
	}
	else if ((u.getupper().getright() == 5 && u.getlower().getleft() == 5) &&
		(b.getupper().getright() == 5 && r.getupper().getleft() == 5)) {
		c.U();
		or = 2;
	}
	else if ((u.getupper().getleft() == 5 && u.getlower().getright() == 5) &&
		(l.getupper().getright() == 5 && b.getupper().getleft() == 5)) {
		c.U2();
		or = 2;
	}
	else if ((u.getupper().getright() == 5 && u.getlower().getleft() == 5) &&
		(f.getupper().getright() == 5 && l.getupper().getleft() == 5)) {
		c.Up();
		or = 2;
	}
	// S orientation == 3
	else if ((u.getlower().getleft() == 5 && b.getupper().getright() == 5) &&
		(r.getupper().getright() == 5 && f.getupper().getright() == 5)) {
		cout << n;
		or = 3;
	}
	else if ((u.getlower().getright() == 5 && l.getupper().getright() == 5) &&
		(b.getupper().getright() == 5 && r.getupper().getright() == 5)) {
		c.U();
		or = 3;
	}
	else if ((u.getupper().getright() == 5 && f.getupper().getright() == 5) &&
		(l.getupper().getright() == 5 && b.getupper().getright() == 5)) {
		c.U2();
		or = 3;
	}
	else if ((u.getupper().getleft() == 5 && r.getupper().getright() == 5) &&
		(f.getupper().getright() == 5 && l.getupper().getright() == 5)) {
		c.Up();
		or = 3;
	}
	// As orientation == 4
	else if ((u.getupper().getright() == 5 && r.getupper().getleft() == 5) &&
		(f.getupper().getleft() == 5 && l.getupper().getleft() == 5)) {
		cout << n;
		or = 4;
	}
	else if ((u.getupper().getleft() == 5 && b.getupper().getleft() == 5) &&
		(f.getupper().getleft() == 5 && r.getupper().getleft() == 5)) {
		c.U();
		or = 4;
	}
	else if ((u.getlower().getleft() == 5 && l.getupper().getleft() == 5) &&
		(b.getupper().getleft() == 5 && r.getupper().getleft() == 5)) {
		c.U2();
		or = 4;
	}
	else if ((u.getlower().getright() == 5 && f.getupper().getleft() == 5) &&
		(l.getupper().getleft() == 5 && b.getupper().getleft() == 5)) {
		c.Up();
		or = 4;
	}
	// Pi orientation == 5
	else if ((b.getupper().getleft() == 5 && f.getupper().getright() == 5) &&
		(l.getupper().getleft() == 5 && l.getupper().getright() == 5)) {
		cout << n;
		or = 5;
	}
	else if ((l.getupper().getleft() == 5 && r.getupper().getright() == 5) &&
		(f.getupper().getleft() == 5 && f.getupper().getright() == 5)) {
		c.U();
		or = 5;
	}
	else if ((b.getupper().getright() == 5 && f.getupper().getleft() == 5) &&
		(r.getupper().getleft() == 5 && r.getupper().getright() == 5)) {
		c.U2();
		or = 5;
	}
	else if ((l.getupper().getright() == 5 && r.getupper().getleft() == 5) &&
		(b.getupper().getleft() == 5 && b.getupper().getright() == 5)) {
		c.Up();
		or = 5;
	}
	// H orientation == 6
	else if ((b.getupper().getleft() == 5 && b.getupper().getright() == 5) &&
		(f.getupper().getleft() == 5 && f.getupper().getright() == 5)) {
		cout << n;
		or = 6;
	}
	else if ((l.getupper().getleft() == 5 && l.getupper().getright() == 5) &&
		(r.getupper().getleft() == 5 && r.getupper().getright() == 5)) {
		c.U();
		or = 6;
	}
	else {
		temp.displayCube();
		throw iv;
	}
	cout << flush << endl;
	if (c.getSide(5).same() && c.getSide(5).getupper().getleft() == 5) {
		cout << "Side is solved.";
		return;
	}

	/* Solve based on orientation */
	temp = c;
	cout << "Solve layer and orient sides: ";
	switch (or) {
	case 0: 
		c.F();
		cout << "( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ";
		c.Fp();
		break;
	case 1:
		cout << "( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.F();
		c.R();
		c.Fp();
		cout << ")";
		break;
	case 2:
		c.F();
		cout << "( ";
		c.R();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.Up();
		c.R();
		c.U();
		cout << ") ( ";
		c.Rp();
		c.Fp();
		cout << ")";
		break;
	case 3:
		cout << "( ";
		c.R();
		c.U();
		c.Rp();
		c.U();
		cout << ") ( ";
		c.R();
		c.U2();
		c.Rp();
		cout << ")";
		break;
	case 4:
		cout << "( ";
		c.R();
		c.U2();
		c.Rp();
		c.Up();
		cout << ") ( ";
		c.R();
		c.Up();
		c.Rp();
		cout << ")";
		break;
	case 5:
		c.F();
		cout << "( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ";
		c.Fp();
		break;
	case 6:
		c.R2();
		c.U2();
		c.R();
		c.U2();
		c.R2();
		break;
	default: throw iv;
	}

	u = c.getSide(0);
	if (!(u.same() && u.color == 5)) {
		cout << endl;
		temp.displayCube();
		throw "Invalid cube or logic error -- cube cannot be solved.";
	}
	cout << flush;
}

void solveFinal(Cube &c) {
	/* Reference: 0 = up, 1 = right, 2 = left, 3 = front, 4 = back, 5 = down */
	if (c.isSolved()) {
		cout << "The final layer is already solved.";
		return;
	}
	if (!c.isValid()) { throw iv; }

	/* Color notation:
	* 0: white
	* 1: red
	* 2: blue
	* 3: orange
	* 4: green
	* 5: yellow
	*/

	Cube temp = c;

	Side u = c.getSide(0);
	Side b = c.getSide(4);
	Side l = c.getSide(2);
	Side r = c.getSide(1);
	Side f = c.getSide(3); // orange is now the front side
	Side d = c.getSide(5);

	/* Determine which of the two cases we're in */
	int or = -1;
	string a = "No alignment necessary.";
	cout << "To align: ";
	// If already solved, but not aligned
	if (f.getupper().same() && l.getupper().same()
		&& b.getupper().same() && r.getupper().same()) {
		if (f.getupper().getleft() == 4) c.U();
		else if (f.getupper().getleft() == 2) c.Up();
		else c.U2();
	}
	// Adjacent corners
	else if (f.getupper().same()) {
		if (f.getupper().getleft() == 3) c.Dp();
		else if (f.getupper().getleft() == 1) c.D();
		else if (f.getupper().getleft() == 2) c.D2();
		c.U();
		or = 0;
	}
	else if (l.getupper().same()) {
		if (l.getupper().getleft() == 4) cout << a;
		else if (l.getupper().getleft() == 3) c.Dp();
		else if (l.getupper().getleft() == 1) c.D();
		else if (l.getupper().getleft() == 2) c.D2();
		or = 0;
	}
	else if (b.getupper().same()) {
		if (b.getupper().getleft() == 3) c.Dp();
		else if (b.getupper().getleft() == 1) c.D();
		else if (b.getupper().getleft() == 2) c.D2();
		c.Up();
		or = 0;
	}
	else if (r.getupper().same()) {
		if (r.getupper().getleft() == 3) c.Dp();
		if (r.getupper().getleft() == 1) c.D();
		if (r.getupper().getleft() == 2) c.D2();
		c.U2();
		or = 0;
	}
	// Diagonal corners
	else if (opposite(f.getupper().getleft(), b.getupper().getleft())) {
		if (f.getupper().getleft() == 3) cout << a;
		else if (f.getupper().getright() == 3) c.U2();
		else if (f.getupper().getleft() == 4) c.Up();
		else if (f.getupper().getright() == 4) c.U();
		or = 1;
	}
	else {
		temp.displayCube();
		throw iv;
	}
	cout << flush << endl;
	if (c.isSolved()) {
		cout << "The final layer is solved.";
		return;
	}

	/* Perform algorithm */
	temp = c;
	if (!or ) {
		cout << "Adjacent corners: ";
		cout << "( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.F();
		cout << ") ( ";
		c.R2();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.Up();
		c.R();
		c.U();
		cout << ") ( ";
		c.Rp();
		c.Fp();
		cout << ")";
	}
	else if (or == 1) {
		cout << "Diagonal corners: ";
		cout << "( ";
		c.F();
		c.R();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.Up();
		c.R();
		c.U();
		cout << ") ( ";
		c.Rp();
		c.Fp();
		cout << ") ( ";
		c.R();
		c.U();
		c.Rp();
		c.Up();
		cout << ") ( ";
		c.Rp();
		c.F();
		c.R();
		c.Fp();
		cout << ")";
	}
	else {
		temp.displayCube();
		throw iv;
	}
}

void beginnersMethod(Cube &c) {
	/* Solve cube using beginner's method */
	cout << endl << "----- SOLUTION -----" << endl;
	cout << "STEP 1: To solve the first layer:" << endl;
	firstLayer(c);
	cout << endl << endl << "Your cube should now look like this:";
	c.displayCube();
	cout << "STEP 2: To orient the final layer:" << endl;
	orientFinal(c);
	cout << endl << endl << "Your cube should now look like this:";
	c.displayCube();
	cout << "STEP 3: To solve the final layer:" << endl;
	solveFinal(c);
	cout << endl << endl;
	if (c.isSolved()) {
		cout << "Your cube is solved." << endl << endl;
	}
	else cout << "Logic error: cube cannot be solved." << endl << endl;
}

void inputSolvedCube(Cube &c) {
	c.set(0, 0, 0, 0, 0); // up
	c.set(3, 1, 1, 1, 1); // front
	c.set(1, 2, 2, 2, 2); // right
	c.set(4, 3, 3, 3, 3); // back
	c.set(2, 4, 4, 4, 4); // left
	c.set(5, 5, 5, 5, 5); // down
}

void generateTestCube(Cube &c) {
	cout << "Generating a test cube..." << endl;
	inputSolvedCube(c);
	/* Perform 20 random turns to scramble the cube */
	int turn;
	cout << "Turns from solved cube: ";
	for (int i = 0; i < rand() % 30 + 10; ++i) {
		turn = rand() % 18; // 18 possible turns
		switch (turn) {
		case 0: c.U(); break;
		case 1: c.Up(); break;
		case 2: c.U2(); break;
		case 3: c.R(); break;
		case 4: c.Rp(); break;
		case 5: c.R2(); break;
		case 6: c.L(); break;
		case 7: c.Lp(); break;
		case 8: c.L2(); break;
		case 9: c.F(); break;
		case 10: c.Fp(); break;
		case 11: c.F2(); break;
		case 12: c.B(); break;
		case 13: c.Bp(); break;
		case 14: c.B2(); break;
		case 15: c.D(); break;
		case 16: c.Dp(); break;
		case 17: c.D2(); break;
		default: cout << "This should not be possible." << flush; exit(10);
		}
	}

	c.displayCube();
}

void testbench(Cube &c) {
	cout << "Running test bench... " << endl;
	srand(time(NULL));
	int passed = 0;
	int timesum = 0;
	int testno = 1000;
	clock_t tbt = clock();
	clock_t max = 0;
	for (int i = 0; i < testno; ++i) {
		clock_t t;

		errorsig = false;
		generateTestCube(c);
		try {
			t = clock(); // start stopwatch
			beginnersMethod(c);
		}
		catch (string error) {
			errorsig = true;
			cout << endl << error << endl;
		}
		catch (char* error) {
			errorsig = true;
			cout << endl << error << endl;
		}
		catch (...) {
			errorsig = true;
			cout << "Unknown error. Aborting program..." << endl;
			system("pause");
			exit(99);
		}
		int elapsed = clock() - t; // end stopwatch
		if (errorsig) {
			cout << "Test " << i+1 << ": FAILED ***************************************************" << endl;
		}
		else {
			cout << "Test " << i+1 << ": PASSED" << endl;
			passed++;
			timesum += elapsed;
			if (elapsed > max) max = elapsed;
		}
		cout << endl << endl << "------------------------------------" << endl;
	}
	cout << passed << "/" << testno << " tests passed." << endl;
	cout << "Average time to compute solution: " << timesum / passed << " ms" << endl;
	cout << "Max time to compute solution: " << max << " ms" << endl;
	cout << "Test bench took " << (clock() - tbt)*1.0/CLOCKS_PER_SEC << " s to complete." << endl;
}

void inputCube(Cube &c) {
	/* Inputs cube from user */

	/* Color notation:
	* 0: white
	* 1: red
	* 2: blue
	* 3: orange
	* 4: green
	* 5: yellow
	*/
	cout << "Please enter your cube's arrangement in the following format:" << endl << endl;
	cout << "    U U" << endl;
	cout << "    U U" << endl;
	cout << "L L F F R R B B" << endl;
	cout << "L L F F R R B B" << endl;
	cout << "    D D" << endl;
	cout << "    D D" << endl;
	cout << "\t\tHere, U represents the 'up' face," << endl
		<< "\t\tL represents the 'left' face," << endl
		<< "\t\tF represents the 'front' face which you're currently looking at," << endl
		<< "\t\tR represents the 'right' face," << endl
		<< "\t\tB represents the 'back' face opposite to you," << endl
		<< "\t\tand D represents the 'down' face." << endl;
	cout << endl << "Enter a letter corresponding to the color on each square." << endl
		<< "(w for white, r for red, b for blue, o for orange, g for green, or y for yellow)" << endl;
	cout << endl << "Please enter colors for the following:" << endl << endl;

	string input;
	int w, x, y, z;
	while (true) {
		cout << "Top-left on L face: ";
		w = readChar();
		cout << "Top-right on L face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on L face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on L face: ";
		cin.ignore();
		z = readChar();
		c.set(2, w, x, y, z);
		cout << "Top-left on U face: ";
		cin.ignore();
		w = readChar();
		cout << "Top-right on U face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on U face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on U face: ";
		cin.ignore();
		z = readChar();
		c.set(0, w, x, y, z);
		cout << "Top-left on F face: ";
		cin.ignore();
		w = readChar();
		cout << "Top-right on F face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on F face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on F face: ";
		cin.ignore();
		z = readChar();
		c.set(3, w, x, y, z);
		cout << "Top-left on R face: ";
		cin.ignore();
		w = readChar();
		cout << "Top-right on R face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on R face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on R face: ";
		cin.ignore();
		z = readChar();
		c.set(1, w, x, y, z);
		cout << "Top-left on B face: ";
		cin.ignore();
		w = readChar();
		cout << "Top-right on B face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on B face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on B face: ";
		cin.ignore();
		z = readChar();
		c.set(4, w, x, y, z);
		cout << "Top-left on D face: ";
		cin.ignore();
		w = readChar();
		cout << "Top-right on D face: ";
		cin.ignore();
		x = readChar();
		cout << "Bottom-left on D face: ";
		cin.ignore();
		y = readChar();
		cout << "Bottom-right on D face: ";
		cin.ignore();
		z = readChar();
		c.set(5, w, x, y, z);

		c.displayCube();
		if (!c.isValid()) {
			cout << "Cube is invalid. Please enter a valid cube." << endl;
			cin.ignore();
			cin.clear();
			continue;
		}
		if (c.isSolved()) {
			cout << "Cube is already solved." << endl;
			break;
		}
		cout << "Is this correct? (y/n) ";
		cin.ignore();
		getline(cin, input);
		if (cin.fail()) { cerr << "Input error."; exit(0); }
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "y" || input == "yes" || input == "ye" || input == " y" || input == "y " || input == " y ") {
			return;
		}
	}
}

int main() {
	cout << "Welcome to the 2x2 Rubik's Cube Solver!" << endl << endl;
	string input;

	/* Initialize cube */
	Cube c;

	/* Enter loop */
	while (true) {
		/* To test the program */
		testbench(c);

		/* Input cube data */
		//inputCube(c);

		/* Solve cube */
		try {
			//beginnersMethod(c);
		}
		catch (string error) {
			errorsig = true;
			cout << endl << error << endl;
		}
		catch (char* error) {
			errorsig = true;
			cout << endl << error << endl;
		}
		catch (...) {
			errorsig = true;
			cout << "Unknown error. Aborting program..." << endl;
			system("pause");
			exit(9);
		}

		cout << "Would you like to solve another cube? (y/n) ";
		getline(cin, input);
		if (cin.fail()) { cerr << "Input error."; exit(0); }
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "y" || input == "yes" || input == "ye" || input == " y" || input == "y " || input == " y ") {
			continue;
		}
		else {
			break;
		}
	}
	return 0;
}