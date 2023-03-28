#ifndef StepperMotor28BYJ48_h
#define StepperMotor28BYJ48_h

#include <Arduino.h>

enum class RotationDirectionEnum
{
  CLOCKWISE,
  COUNTER_CLOCKWISE
};

enum class StepModeEnum
{
  HALF_STEP,
  FULL_STEP
};

class StepperMotor28BYJ48
{
public:
  StepperMotor28BYJ48(const unsigned int kPin1, const unsigned int kPin2, const unsigned int kPin3, const unsigned int kPin4);

  void setStepMode(const StepModeEnum kStepMode);

  void setSpeed(const unsigned int kSpeed);

  void setRotationDirection(const RotationDirectionEnum kRotationDirection);

  void step(const unsigned int kSteps);

  unsigned int getCurrentStep();

private:
  const unsigned int _kPin1;
  const unsigned int _kPin2;
  const unsigned int _kPin3;
  const unsigned int _kPin4;

  StepModeEnum step_mode_ = StepModeEnum::FULL_STEP;

  RotationDirectionEnum rotation_direction_ = RotationDirectionEnum::CLOCKWISE;

  unsigned long time_between_steps_ = 0;

  unsigned int current_step_ = 0;
};

#endif
