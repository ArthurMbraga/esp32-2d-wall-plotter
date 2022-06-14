#include "Stepper.h"
#include <Arduino.h>
#include <math.h>
#include "Canvas.h"

Stepper *motor1;
Stepper *motor2;
Canvas *canvas;

int countTarget = 0;
int currentCount = 0;

bool shouldChangeMovement()
{
  if (currentCount >= countTarget)
  {
    currentCount = 0;
    return true;
  }
  else
  {
    currentCount++;
    return false;
  }
}

void updateCanvas()
{
  if (shouldChangeMovement())
  {

    double move[2] = {0, 0};
    bool hasMove = canvas->nextMove(move);

    if (hasMove)
    {
      int time1 = motor1->move(move[0]);
      int time2 = motor2->move(move[1]);

      countTarget = time1 > time2 ? time1 : time2;
    }
  }
}

void setup()
{
  motor1 = new Stepper(13, 12, 14, 27);
  motor2 = new Stepper(15, 2, 4, 5);

  canvas = new Canvas(50, 50);
  canvas->draw({5, 2});
}

void loop()
{

  motor1->update();
  motor2->update();
  updateCanvas();
  delayMicroseconds(1);
}
