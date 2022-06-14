#include "Stepper.h"
#include <Arduino.h>
#include <math.h>

const int ctr_a = 12;
const int ctr_b = 13;
const int ctr_c = 14;
const int ctr_d = 27;
const int t = 2050;
const int stepsPerRevolution = 2052;
int currentStep = 0;

Stepper *motor1;
Stepper *motor2;
#define H 10
#define L 10

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Lengths {
    double a;
    double b;
    Lengths(int l1, int l2) : a(l1), b(l2) {}
    Lengths(Point p) : a(sqrt(p.x* p.x + (H - p.y) * (H - p.y))), b(sqrt((L - p.x)* (L - p.x) + (H - p.y) * (H - p.y))) {}
} Lenghts;

void oneRevolution(float angle)
{
  const int numberOfSteps = stepsPerRevolution * abs(angle) / 360;
  for (int i = 0; i < numberOfSteps; i++)
  {
    switch (currentStep)
    {
    case 0: // AB
      digitalWrite(ctr_a, LOW);
      digitalWrite(ctr_b, LOW);
      digitalWrite(ctr_c, HIGH);
      digitalWrite(ctr_d, HIGH);
      break;

void setup()
{
  motor1 = new Stepper(13, 12, 14, 27);
  motor2 = new Stepper(15, 2, 4, 5);

  motor1->move(100);
  motor2->move(100);
}

void loop()
{
  motor1->update();
  motor2->update();

  delayMicroseconds(1);
}
