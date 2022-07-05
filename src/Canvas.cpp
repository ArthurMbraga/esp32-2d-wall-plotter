#include "Canvas.h"
#include <Arduino.h>

double squared(double x)
{
	return x * x;
}

Lengths pointToLenghts(Point p)
{
	double a = sqrt(squared(p.x) + squared(CANVA_HEIGHT - p.y));
	double b = sqrt(squared(CANVA_WIDTH - p.x) + squared(CANVA_HEIGHT - p.y));

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

	// Serial.print("distX: ");
	// Serial.println(distX);
	// Serial.print("distY: ");
	// Serial.println(distY);
	// Serial.print("diffX: ");
	// Serial.println(diffX);
	// Serial.print("diffY: ");
	// Serial.println(diffY);

	size = moves;
	it = 0;

	Lengths lastLen = pointToLenghts(position);

	for (int i = 1; i <= size; i++)
	{
		Point p = {position.x + diffX * i, position.y + diffY * i};
		Lengths newLen = pointToLenghts(p);

		m1[i] = newLen.a - lastLen.a;
		m2[i] = newLen.b - lastLen.b;
		// Serial.print("M1: ");
		// Serial.println(m1[i]);
		// Serial.print("M2: ");
		// Serial.println(m2[i]);
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