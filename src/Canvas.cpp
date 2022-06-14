#include "Canvas.h" 

void Canvas::draw(Point target) {
	double dist = sqrt((target.x - position.x) * (target.x - position.x) + (target.y - position.y) * (target).y - position.y));
	int moves = dist / CANVA_RES;

	double distX = target.x - position.x;
	double distY = target.y - position.y;

	double diffX = distX / moves;
	double diffY = distY / moves;

	size = moves;
	it = 0;
	
	Lengths lastLen = pointToLenghts(position);

	for (int i = 1; i <= size; i++) {
		Point p = { position.x + diffX * i, position.y + diffY * i };
		Lengths newLen = pointToLenghts(p);

		m1[i] = newLen.a - lastLen.a;
		m2[i] = newLen.b - lastLen.b;

		lastLen = newLen;
	}
}

double* Canvas::nextMove() {
	if (it < size) {
		double move[2] = { m1[it], m2[it] };
		it++;
		return move;
	}

	return nullptr;
}