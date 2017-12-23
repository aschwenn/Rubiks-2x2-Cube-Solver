#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Cube.h"

using namespace std;

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

void beginnersMethod(Cube &c) {
	/* Solve cube using beginner's method */
	c.displayCube();
	if (c.isSolved()) cout << "Solved!" << endl;
	if (c.isValid()) cout << "Valid!" << endl;
	c.U2();
	c.U2();
	c.R2();
	c.R2();
	c.L2();
	c.L2();
	c.F2();
	c.F2();
	c.B2();
	c.B2();
	c.D2();
	c.D2();
	c.displayCube();
	cout << "Testing solution..." << endl;
	c.U();
	c.R();
	c.U2();
	c.F2();
	c.Up();
	c.R2();
	c.Up();
	c.F2();
	c.R();
	c.displayCube();
	if (c.isSolved()) cout << "Solved!" << endl;
	if (c.isValid()) cout << "Valid!" << endl;
}

void inputTestCube(Cube &c) {
	/* for testing purposes */
	c.set(0, 4, 2, 1, 3); // up
	c.set(3, 4, 4, 2, 5); // front
	c.set(1, 0, 0, 2, 5); // right
	c.set(4, 1, 5, 3, 1); // back
	c.set(2, 1, 0, 2, 3); // left
	c.set(5, 0, 3, 5, 4); // down
}

void inputSolvedCube(Cube &c) {
	c.set(0, 0, 0, 0, 0); // up
	c.set(3, 1, 1, 1, 1); // front
	c.set(1, 2, 2, 2, 2); // right
	c.set(4, 3, 3, 3, 3); // back
	c.set(2, 4, 4, 4, 4); // left
	c.set(5, 5, 5, 5, 5); // down
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

	/* Initialize cube */
	Cube c;

	/* Enter loop */
	while (true) {
		/* Input cube data */
		//inputTestCube(c);
		inputCube(c);

		/* Solve cube */
		//beginnersMethod(c);

	}
	return 0;
}