#include <StepperMotor28BYJ48.h>

// Creating a Class object
StepperMotor28BYJ48 stepperMotor28BYJ48(2, 3, 4, 5);

void setup()
{
  /*
    Default is 100%.
    Changing the engine speed (from 1% to 100%).
  */
  stepperMotor28BYJ48.setSpeed(90);
  // (90% of the rated engine speed)

  /*
    By default - StepModeType::fullStep (full-step engine operation mode).
    Changing the engine operation mode (full-step | half-step).
  */
  stepperMotor28BYJ48.setStepMode(StepModeType::halfStep);
  // (half-step engine operation mode)

  /*
    By default - RotationDirectionType::clockwise (the direction of rotation of the motor clockwise).
    Changing the direction of rotation of the engine (clockwise | counterclockwise).
  */
  stepperMotor28BYJ48.setRotationDirection(RotationDirectionType::counterClockwise);
  // (the direction of rotation of the motor is counterclockwise)

  
  // Calling the engine start function (the number of steps expected to be executed by the engine).
  stepperMotor28BYJ48.step(2037);
}

void loop()
{
}
