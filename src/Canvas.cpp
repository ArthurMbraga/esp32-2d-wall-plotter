#include "Canvas.h"
#include <Arduino.h>

double squared(double x)
{
	return x * x;
}

Lengths Canvas::pointToLengths(Point p)
{
	double a = sqrt(squared(p.x) + squared(p.y));
	double b = sqrt(squared(this->width - p.x) + squared(p.y));

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

	Lengths lastLen = pointToLengths(position);

	for (int i = 1; i <= size; i++)
	{
		Point p = {position.x + diffX * i, position.y + diffY * i};
		Lengths newLen = pointToLengths(p);

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

void Canvas::setPosition(Point position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

Lengths Canvas::getCircleLengths(Point center, double radius, double angle)
{
	double x = center.x + radius * cos(angle * M_PI / 180);
	double y = center.y + radius * sin(angle * M_PI / 180);

	Serial.print("currentDraw: ");
	Serial.println(x);
	Serial.println(y);
	return pointToLengths({x, y});
}