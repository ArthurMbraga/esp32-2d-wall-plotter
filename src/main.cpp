#include "Stepper.h"
#include <Arduino.h>
#include <math.h>
#include "Canvas.h"

Stepper *motor1;
Stepper *motor2;
Canvas *canvas;

int countTarget = 0;
int currentCount = 0;

int currentDraw = -1;
Point points[] = {{48.5, 11}, {48.5, 12}, {24, 12}, {16, 22}, {24, 44}, {48.5, 70}, {71, 44}, {80, 22}, {71, 12}, {48.5, 12}, {48.5, 11}};

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

Lengths currentP;

void updateCanvas()
{

  if (currentDraw < 361 && shouldChangeMovement())
  {

    // double move[2] = {0, 0};
    // bool hasMove = canvas->nextMove(move);

    // if (hasMove)
    // {

    Lengths lengths = canvas->getCircleLengths({48.5, 35}, 20, currentDraw);

    // int time1 = motor1->getTimeToMove(move[0]);
    // int time2 = motor2->getTimeToMove(move[1]);

    int time1 = motor1->getTimeToMove(lengths.a - currentP.a);
    int time2 = motor2->getTimeToMove(lengths.b - currentP.b);

    float speed1 = 1;
    float speed2 = 1;

    if (time1 > time2)
    {
      speed2 = float(time2) / float(time1);
      countTarget = time1;
    }
    else
    {
      speed1 = float(time1) / float(time2);
      countTarget = time2;
    }

    motor1->setSpeed(speed1);
    motor2->setSpeed(speed2);

    // motor1->move(move[0]);
    // motor2->move(move[1]);
    motor1->move(lengths.a - currentP.a);
    motor2->move(lengths.b - currentP.b);
    currentDraw++;
    currentP = lengths;
  }
  else
  {
    // currentDraw++;
    // Serial.print("currentDraw: ");
    // Serial.println(currentDraw);
    // canvas->draw(points[currentDraw]);
    // currentCount = countTarget;
  }
  // }
}

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 115200 bps
  delay(5000);
  motor1 = new Stepper(13, 12, 14, 27);
  motor2 = new Stepper(15, 2, 4, 5);

  motor1->invertRotation();
  motor2->invertRotation();

  canvas = new Canvas(97, 73);
  canvas->setPosition({48.5, 11});
  currentP = canvas->pointToLengths({48.5, 11});
}

void loop()
{

  motor1->update();
  motor2->update();
  updateCanvas();
  delayMicroseconds(1);
}
