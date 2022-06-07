#include <Arduino.h>
#include <Stepper.h>
#include <math.h>

//   // change this to fit the number of steps per revolution
// // // for your motor

// // // initialize the stepper library on pins 8 through 11:
// Stepper myStepper(stepsPerRevolution, 12, 13, 14, 27);

// void setup() {
//   Serial.begin(9600);
//   delay(1000);
//    myStepper.setSpeed(5);
//   // step one revolution  in one direction:
//   Serial.println("clockwise");
//   myStepper.step(stepsPerRevolution);
// }

// void loop() {
//   myStepper.setSpeed(5);
//   // step one revolution  in one direction:
//   Serial.println("clockwise");
//   myStepper.step(stepsPerRevolution);
//   // delay(500);

//   // // step one revolution in the other direction:
//   // Serial.println("counterclockwise");
//   // myStepper.step(-stepsPerRevolution);
//   // delay(500);
// }

const int ctr_a = 12;
const int ctr_b = 13;
const int ctr_c = 14;
const int ctr_d = 27;
const int t = 2050;
const int stepsPerRevolution = 2052;
int currentStep = 0;

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

    case 1: // BC
      digitalWrite(ctr_a, HIGH);
      digitalWrite(ctr_b, LOW);
      digitalWrite(ctr_c, LOW);
      digitalWrite(ctr_d, HIGH);
      break;
    case 2: // CD
      digitalWrite(ctr_a, HIGH);
      digitalWrite(ctr_b, HIGH);
      digitalWrite(ctr_c, LOW);
      digitalWrite(ctr_d, LOW);
      break;
    case 3: // DA
      digitalWrite(ctr_a, LOW);
      digitalWrite(ctr_b, HIGH);
      digitalWrite(ctr_c, HIGH);
      digitalWrite(ctr_d, LOW);
      break;
    }
    if (angle > 0)
      currentStep++;
    else
      currentStep--;

    if (currentStep > 3)
      currentStep = 0;
    else if (currentStep < 0)
      currentStep = 3;

    delayMicroseconds(t);
  }
  digitalWrite(ctr_a, LOW);
  digitalWrite(ctr_b, LOW);
  digitalWrite(ctr_c, LOW);
  digitalWrite(ctr_d, LOW);
}

void setup()
{
  // pinMode(sd,OUTPUT);
  // pinMode(pwm1,OUTPUT);
  // pinMode(pwm2,OUTPUT);
  pinMode(ctr_a, OUTPUT);
  pinMode(ctr_b, OUTPUT);
  pinMode(ctr_c, OUTPUT);
  pinMode(ctr_d, OUTPUT);
  delay(3000);
  oneRevolution(360*20);
  // digitalWrite(sd,HIGH);
  // digitalWrite(pwm1,HIGH);
  // digitalWrite(pwm2,HIGH);
  //    digitalWrite(ctr_a,LOW);
  //    digitalWrite(ctr_b,LOW);
  //    digitalWrite(ctr_c,LOW);
  //    digitalWrite(ctr_d,LOW);
}

void loop()
{
}
