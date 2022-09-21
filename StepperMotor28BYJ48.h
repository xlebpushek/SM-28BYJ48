#ifndef StepperMotor28BYJ48_h
#define StepperMotor28BYJ48_h

#include <Arduino.h>

enum class RotationDirectionType
{
  clockwise,
  counterClockwise
};

enum class StepModeType
{
  halfStep,
  fullStep
};

class StepperMotor28BYJ48
{
public:
  StepperMotor28BYJ48(const unsigned int kPin1, const unsigned int kPin2, const unsigned int kPin3, const unsigned int kPin4);

  void setStepMode(const StepModeType kStepMode);

  void setSpeed(const unsigned int kSpeed);

  void setRotationDirection(const RotationDirectionType kRotationDirection);

  void step(const unsigned int kSteps);

private:
  StepModeType _step_mode;

  RotationDirectionType _rotation_direction;

  unsigned long _time_between_steps;

  const unsigned int _kPin1;
  const unsigned int _kPin2;
  const unsigned int _kPin3;
  const unsigned int _kPin4;
};

#endif
