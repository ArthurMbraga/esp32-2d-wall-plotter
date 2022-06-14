#include "Stepper.h"
#include <Arduino.h>

const int ctr_a = 12;
const int ctr_b = 13;
const int ctr_c = 14;
const int ctr_d = 27;
const int t = 2050;
const int stepsPerRevolution = 2052;
int currentStep = 0;

Stepper *motor1;
Stepper *motor2;

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
