#pragma once
#include <math.h>

#define CANVA_HEIGHT 10
#define CANVA_WIDTH 10

#define CANVA_RES 0.0141421
#define CANVA_MAX_SIZE 1000

typedef struct Point {
	double x;
	double y;
} Point;

typedef struct Lengths {
	double a;
	double b;
} Lenghts;

Lengths pointToLenghts(Point p) {
	double a = sqrt(p.x * p.x + (CANVA_HEIGHT - p.y) * (CANVA_HEIGHT - p.y));
	double b = sqrt((CANVA_WIDTH - p.x) * (CANVA_WIDTH - p.x) + (CANVA_HEIGHT - p.y) * (CANVA_HEIGHT - p.y));

	return Lengths{ a, b };
}

class Canvas {
private:
	int it = 0;
	int size = 0;

	double m1[CANVA_MAX_SIZE];
	double m2[CANVA_MAX_SIZE];

	Point position;

public:
	Canvas(double x, double y) : position(Point{x, y}) {}
	void draw(Point target);
	double* nextMove();

};
