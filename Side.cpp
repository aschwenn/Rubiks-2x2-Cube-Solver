#include "Side.h"

Side::Side()
{
	color = -1;
}

void Side::CW() {
	// performs clockwise turn (only affects this side)
	int a = upper.getleft();
	int b = upper.getright();
	int c = lower.getleft();
	int d = lower.getright();
	/* Orientation
	| a b |
	| c d |
	*/
	upper.setleft(c);
	upper.setright(a);
	lower.setleft(d);
	lower.setright(b);
}

void Side::CCW() {
	int a = upper.getleft();
	int b = upper.getright();
	int c = lower.getleft();
	int d = lower.getright();
	upper.setleft(b);
	upper.setright(d);
	lower.setleft(a);
	lower.setright(c);
}

bool Side::same() {
	if (upper.getleft() == upper.getright() && upper.getleft() == lower.getleft() && upper.getleft() == lower.getright()) {
		color = upper.getleft();
		return true;
	}
	return false;
}

void Side::makeBlank() {
	upper = Row(0, 0);
	lower = Row(0, 0);
}

Row Side::getupper() const {
	return upper;
}

Row Side::getlower() const {
	return lower;
}

Row Side::getleftside() const {
	return Row(upper.getleft(), lower.getleft());
}

Row Side::getrightside() const {
	return Row(upper.getright(), lower.getright());
}

void Side::setupper(Row r) {
	upper = r;
}

void Side::setlower(Row r) {
	lower = r;
}

void Side::setleftside(Row r) {
	upper.setleft(r.getleft());
	lower.setleft(r.getright());
}

void Side::setrightside(Row r) {
	upper.setright(r.getleft());
	lower.setright(r.getright());
}