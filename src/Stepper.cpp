#include "stepper.h"
#include <Arduino.h>

Stepper::Stepper(int pinA, int pinB, int pinC, int pinD) : PIN_A(pinA), PIN_B(pinB), PIN_C(pinC), PIN_D(pinD)
{
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
}

int Stepper::deg2step(double angle)
{
  return abs(angle) * STEPS_PER_REVOLUTION / 360;
}

double Stepper::length2deg(double length)
{
  return 360 * abs(length) / (2 * PI * PULLEY_RADIUS);
}

void Stepper::move(double length)
{
  double angle = length2deg(length);
  stepCountTarget = deg2step(angle);
  currentDirection = length > 0 ? COUNTER_CLOCKWISE : CLOCKWISE;
  stepCount = 0;
  stepIntervalCount = STEP_DELAY;
}

int Stepper::rotate(double angle)
{
  stepCountTarget = deg2step(angle);
  currentDirection = angle > 0 ? COUNTER_CLOCKWISE : CLOCKWISE;
  stepCount = 0;
  stepIntervalCount = STEP_DELAY;

  return stepCountTarget * STEP_DELAY;
}

bool Stepper::shouldMove()
{
  return stepCount < stepCountTarget;
}

bool Stepper::shouldChangeCoilCombination()
{
  if (stepIntervalCount >= STEP_DELAY / speed)
  {
    stepIntervalCount = 0;
    return true;
  }
  else
  {
    stepIntervalCount++;
    return false;
  }
}

void Stepper::changeCoilCombination()
{
  switch (currentCoilCombination)
  {
  case 0: // AB
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, HIGH);
    break;

  case 1: // BC
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
    digitalWrite(PIN_D, HIGH);
    break;
  case 2: // CD
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
    digitalWrite(PIN_D, LOW);
    break;
  case 3: // DA
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, LOW);
    break;
  }
  currentCoilCombination += currentDirection * directionInverter;

  if (currentCoilCombination > 3)
    currentCoilCombination = 0;
  else if (currentCoilCombination < 0)
    currentCoilCombination = 3;
}

void Stepper::update()
{
  if (shouldMove() && shouldChangeCoilCombination())
  {
    stepCount++;
    changeCoilCombination();
  }
}

void Stepper::invertRotation()
{
  directionInverter = -directionInverter;
}

void Stepper::setSpeed(double speed)
{
  this->speed = speed;
}

int Stepper::getTimeToMove(double length)
{
  int numberOfSteps = deg2step(length2deg(length));
  return numberOfSteps * STEP_DELAY;
}
