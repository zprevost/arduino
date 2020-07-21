#include <Stepper.h>

#define LIMIT1 (!digitalRead(A0))
#define LIMIT2 (!digitalRead(A1))

#define STEPS_PER_REV 2048 // Steps per revolution for this motor
#define SPEED 12

#define STEPSIZE 1
#define LENGTH1 7
#define LENGTH2 7.5

Stepper stepper1(STEPS_PER_REV, 8, 10, 9, 11);
Stepper stepper2(STEPS_PER_REV, 4, 5, 3, 6);

int stepperPos1 = 0;
int stepperPos2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  stepper1.setSpeed(SPEED);
  stepper2.setSpeed(SPEED);
  stepperGo1(-1000);
  stepperGo2(-1000);
  Serial.println("/////");
}

void stepperGo1(int moveToDeg) {
  angle1 = moveToDeg;
  long stepsToTake = (moveToDeg / 360.0) * STEPS_PER_REV - stepperPos1;
  Serial.print("stepper1 stepsToTake: ");
  Serial.println(stepsToTake);

  // Forward
  if (stepsToTake > 0) {
    Serial.print("Going forward to ");
    Serial.println(moveToDeg);
    for (int i = 1; i <= abs(stepsToTake); i += STEPSIZE) {
      stepper1.step(STEPSIZE);
      stepperPos1 += STEPSIZE;
    }
  }

  // Reverse
  if (stepsToTake < 0) {
    Serial.print("Going reverse to");
    Serial.println(moveToDeg);
    for (int i = 1; i <= abs(stepsToTake); i += STEPSIZE) {
      if (LIMIT1) {
        Serial.println("Hit LIMIT1");
        stepperPos1 = 0;
        break;
      }
      stepper1.step(-STEPSIZE);
      stepperPos1 -= STEPSIZE;
    }
  }

  Serial.print("stepperPos1: ");
  Serial.println(stepperPos1);
}
l
void stepperGo2(int moveToDeg) {
  angle2 = moveToDeg;
  long stepsToTake = (moveToDeg / 360.0) * STEPS_PER_REV - stepperPos2;
  Serial.print("stepper2 stepsToTake: ");
  Serial.println(stepsToTake);

  // Forward
  if (stepsToTake > 0) {
    Serial.print("Going forward to ");
    Serial.println(moveToDeg);
    for (int i = 1; i <= abs(stepsToTake); i += STEPSIZE) {
      stepper2.step(-STEPSIZE); // This is flipped for stepper 2
      stepperPos2 -= STEPSIZE;
    }
  }

  // Reverse
  if (stepsToTake < 0) {
    Serial.print("Going reverse to ");
    Serial.println(moveToDeg);
    for (int i = 1; i <= abs(stepsToTake); i += STEPSIZE) {
      if (LIMIT2) {
        Serial.println("Hit LIMIT2");
        stepperPos2 = 0;
        break;
      }
      stepper2.step(+STEPSIZE); // This is flipped for stepper 2
      stepperPos2 += STEPSIZE;
    }
  }

  Serial.print("stepperPos2: ");
  Serial.println(stepperPos2);
}

void checkSerial() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'h':
        Serial.println("hello");
        break;
      case 'g':
        Serial.print(LIMIT1);
        Serial.print(" ");
        Serial.println(LIMIT2);
        break;
      case 'j':
        calculateLocation();
        break;
      case '0':
        Serial.println('0');
        stepperGo1(-1000);
        Serial.println("/////");
        break;
      case '1':
        Serial.println('1');
        stepperGo1(15);
        Serial.println("/////");
        break;
      case '2':
        Serial.println('2');
        stepperGo1(30);
        Serial.println("/////");
        break;
      case '3':
        Serial.println('3');
        stepperGo1(35);
        Serial.println("/////");
        break;
      case ')':
        Serial.println(')');
        stepperGo2(-1000);
        Serial.println("/////");
        break;
      case '!':
        Serial.println('!');
        stepperGo2(15);
        Serial.println("/////");
        break;
      case '@':
        Serial.println('@');
        stepperGo2(30);
        Serial.println("/////");
        break;
      case '#':
        Serial.println('#');
        stepperGo2(45);
        Serial.println("/////");
        break;
      case '$':
        Serial.println('$');
        stepperGo2(60);
    }
  }
}

void loop() {
  checkSerial();
  delay(500);
}
