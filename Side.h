#pragma once
#include "Row.h"

using namespace std;

class Side {
private:
	/* Each side in our virtual cube has 2 rows, an upper and a lower */
	Row upper, lower;
	
public:
	Side();

	bool same(); // whether or not all cubies are the same color, sets color if true
	int color; // -1 if !same, color id if same

	void CW(); // performs clockwise turn on this side
	void CCW(); // performs counterclockwise turn on this side

	void makeBlank(); // creates a blank side (all white)

	Row getupper() const;
	Row getlower() const;
	Row getleftside() const;
	Row getrightside() const;
	void setupper(Row r);
	void setlower(Row r);
	void setleftside(Row r);
	void setrightside(Row r);
};