#ifndef Cube_h
#define Cube_h
#include "Side.h"
#include "Row.h"

using namespace std;

/* Keep a virtual cube in the program to keep track of the permutations being applied */

class Cube {
private:
	/* Virtual cube contains a side for each side of the actual cube (6 total) */
	Side up, right, left, front, back, down;
	bool solved;

	void createEmpty(); // initializes an empty cube

public:
	Cube();
	Cube(const Cube &c);
	Side getSide(int a) const;

	/* Input/Output */
	void set(int side, int a, int b, int c, int d);
	void displayCube();

	/* Validation */
	bool isValid();
	bool isSolved();

	/* Permutations */
	void U(); // U clockwise
	void Up(); // U counterclockwise
	void U2();

	void R();
	void Rp();
	void R2();
	
	void L();
	void Lp();
	void L2();
	
	void F();
	void Fp();
	void F2();

	void B();
	void Bp();
	void B2();

	void D();
	void Dp();
	void D2();
};

/* Algorithm notation: 
 * U, R, L, F, B, D corresponds to the up, right, left, front, back, and down faces.
 * The default is clockwise; ' (prime) denotes counterclockwise.
 */

/* Color notation:
 * 0: white
 * 1: red
 * 2: blue
 * 3: orange
 * 4: green
 * 5: yellow
 */
#endif