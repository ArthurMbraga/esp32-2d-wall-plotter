#ifndef Canvas_h
#define Canvas_h


#define CANVA_HEIGHT 70
#define CANVA_WIDTH 90

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
	int it = 0;
	int size = 0;

	double m1[CANVA_MAX_SIZE];
	double m2[CANVA_MAX_SIZE];

	Point position;

public:
	Canvas(double x, double y) : position(Point{x, y}) {}
	void draw(Point target);
	bool nextMove(double move[2]);
};

#endif