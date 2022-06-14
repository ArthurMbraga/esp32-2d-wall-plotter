#include "Canvas.h"
#include <Arduino.h>

Lengths pointToLenghts(Point p)
{
	double a = sqrt(p.x * p.x + (CANVA_HEIGHT - p.y) * (CANVA_HEIGHT - p.y));
	double b = sqrt((CANVA_WIDTH - p.x) * (CANVA_WIDTH - p.x) + (CANVA_HEIGHT - p.y) * (CANVA_HEIGHT - p.y));

	return Lengths{a, b};
}

void Canvas::draw(Point target)
{
	double dist = sqrt((target.x - position.x) * (target.x - position.x) + (target.y - position.y) * (target).y - position.y);
	int moves = dist / CANVA_RES;

	double distX = target.x - position.x;
	double distY = target.y - position.y;

	double diffX = distX / moves;
	double diffY = distY / moves;

	size = moves;
	it = 0;

	Lengths lastLen = pointToLenghts(position);

	for (int i = 1; i <= size; i++)
	{
		Point p = {position.x + diffX * i, position.y + diffY * i};
		Lengths newLen = pointToLenghts(p);

		m1[i] = newLen.a - lastLen.a;
		m2[i] = newLen.b - lastLen.b;

		lastLen = newLen;
	}
}

bool Canvas::nextMove(double move[2])
{
	if (it < size)
	{
		move[0] = m1[it];
		move[1] = m2[it];
		it++;
		return true;
	}
	return false;
}