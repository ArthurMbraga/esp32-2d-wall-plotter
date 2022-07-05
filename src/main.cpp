#include "Stepper.h"
#include <Arduino.h>
#include <math.h>
#include "Canvas.h"

Stepper *motor1;
Stepper *motor2;
Canvas *canvas;

int countTarget = 0;
int currentCount = 0;

int currentDraw = 0;
Point points[] = {{54, 28}, {44, 28}, {44, 18}, {64, 18}, {64, 28}, {54, 28}, {54, 13}};

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

  if (currentDraw < 7 && shouldChangeMovement())
  {

    double move[2] = {0, 0};
    bool hasMove = canvas->nextMove(move);

    if (hasMove)
    {
      int time1 = motor1->getTimeToMove(move[0]);
      int time2 = motor2->getTimeToMove(move[1]);


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

      motor1->move(move[0]);
      motor2->move(move[1]);
      
    }
    else
    {
      Serial.print("currentDraw: ");
      Serial.println(currentDraw);
      canvas->draw(points[currentDraw]);
      currentDraw++;
    }
  }
}

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 115200 bps

  motor1 = new Stepper(13, 12, 14, 27);
  motor2 = new Stepper(15, 2, 4, 5);

  motor1->invertRotation();
  motor2->invertRotation();

  canvas = new Canvas(54, 13);
}

void loop()
{

  motor1->update();
  motor2->update();
  updateCanvas();
  delayMicroseconds(1);
}
