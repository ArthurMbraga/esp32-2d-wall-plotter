#ifndef Stepper_h
#define Stepper_h

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE -1

class Stepper
{
private:
  static const int STEPS_PER_REVOLUTION = 2052;
  static const int STEP_DELAY = 2050;
  static const int PULLEY_RADIUS = 1.6; // Em cm 

  const int PIN_A;
  const int PIN_B;
  const int PIN_C;
  const int PIN_D;

  int stepIntervalCount = 0;
  int stepCountTarget = 0;
  int stepCount = 0;
  // 0 = AB, 1 = BC, 2 = CD, 3 = DA
  int currentCoilCombination = 0;
  // 1 = CLOCKWISE, -1 = COUNTER_CLOCKWISE
  int direction = 0;

private:
  bool shouldMove();
  bool shouldChangeCoilCombination();
  void changeCoilCombination();
  int deg2step(double angle);
  double length2deg(double length);

public:
  Stepper(int pinA, int pinB, int pinC, int pinD);
  void move(double length);
  void update();
};

#endif