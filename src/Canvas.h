#ifndef Canvas_h
#define Canvas_h

// #define CANVA_RES 0.0141421
#define CANVA_RES 1.41421
#define CANVA_MAX_SIZE 1000

typedef struct Point
{
	double x;
	double y;
} Point;

typedef struct Lengths
{
	double a;
	double b;
} Lenghts;

class Canvas
{
private:
	double height;
	double width;
	int it = 0;
	int size = 0;

	double m1[CANVA_MAX_SIZE];
	double m2[CANVA_MAX_SIZE];

	Point position;

	int currentAngle = 0;

public:
	Lengths pointToLengths(Point p);
	Canvas(double w, double h) : width(w), height(h){};
	void setPosition(Point position);
	void draw(Point target);
	bool nextMove(double move[2]);
	Lengths getCircleLengths(Point center, double radius, double angle);
};

#endif