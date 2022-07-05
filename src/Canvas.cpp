#include "Canvas.h"
#include <Arduino.h>

double squared(double x)
{
	return x * x;
}

Lengths pointToLenghts(Point p)
{
	double a = sqrt(squared(p.x) + squared(p.y));
	double b = sqrt(squared(CANVA_WIDTH - p.x) + squared(p.y));

	return Lengths{a, b};
}

void Canvas::draw(Point target)
{
	double dist = sqrt(squared(target.x - position.x) + squared(target.y - position.y));
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

		m1[i - 1] = newLen.a - lastLen.a;
		m2[i - 1] = newLen.b - lastLen.b;

		lastLen = newLen;
	}

	position.x = target.x;
	position.y = target.y;
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