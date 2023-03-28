#include "StepperMotor28BYJ48.h"

StepperMotor28BYJ48::StepperMotor28BYJ48(const unsigned int kPin1, const unsigned int kPin2, const unsigned int kPin3, const unsigned int kPin4) : _kPin1(kPin1), _kPin2(kPin2), _kPin3(kPin3), _kPin4(kPin4)
{
  pinMode(kPin1, OUTPUT);
  pinMode(kPin2, OUTPUT);
  pinMode(kPin3, OUTPUT);
  pinMode(kPin4, OUTPUT);

  setSpeed(100);
}

void StepperMotor28BYJ48::setSpeed(const unsigned int kSpeed)
{
  time_between_steps_ = 6e+7 / (((15 * (step_mode_ == StepModeEnum::HALF_STEP ? 4075 : 2037)) / 100) * (kSpeed > 100 ? 100 : kSpeed));
}

void StepperMotor28BYJ48::setRotationDirection(const RotationDirectionEnum kRotationDirection)
{
  rotation_direction_ = kRotationDirection;
}

void StepperMotor28BYJ48::setStepMode(const StepModeEnum kStepMode)
{
  step_mode_ = kStepMode;
}

void StepperMotor28BYJ48::step(const unsigned int kTotalSteps)
{
  unsigned int remaining_steps = kTotalSteps;
  unsigned long time_since_last_step;

  while (remaining_steps > 0)
  {
    if (micros() - time_since_last_step >= time_between_steps_)
    {
      time_since_last_step = micros();

      if (rotation_direction_ == RotationDirectionEnum::CLOCKWISE)
      {
        current_step_++;

        if (current_step_ == kTotalSteps)
          current_step_ = 0;
      }
      else if (rotation_direction_ == RotationDirectionEnum::COUNTER_CLOCKWISE)
      {
        if (current_step_ == 0)
          current_step_ = kTotalSteps;

        current_step_--;
      }

      remaining_steps--;

      if (step_mode_ == StepModeEnum::HALF_STEP)
      {
        switch (current_step_ % 8)
        {
        case 0:
          digitalWrite(_kPin1, HIGH);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, HIGH);
          break;
        case 1:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, HIGH);
          break;
        case 2:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, HIGH);
          digitalWrite(_kPin4, HIGH);
          break;
        case 3:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, HIGH);
          digitalWrite(_kPin4, LOW);
          break;
        case 4:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, HIGH);
          digitalWrite(_kPin3, HIGH);
          digitalWrite(_kPin4, LOW);
          break;
        case 5:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, HIGH);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, LOW);
          break;
        case 6:
          digitalWrite(_kPin1, HIGH);
          digitalWrite(_kPin2, HIGH);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, LOW);

          break;
        case 7:
          digitalWrite(_kPin1, HIGH);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, LOW);
          break;
        }
      }
      else if (step_mode_ == StepModeEnum::FULL_STEP)
      {
        switch (current_step_ % 4)
        {
        case 0:
          digitalWrite(_kPin1, HIGH);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, HIGH);
          break;
        case 1:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, LOW);
          digitalWrite(_kPin3, HIGH);
          digitalWrite(_kPin4, HIGH);
          break;
        case 2:
          digitalWrite(_kPin1, LOW);
          digitalWrite(_kPin2, HIGH);
          digitalWrite(_kPin3, HIGH);
          digitalWrite(_kPin4, LOW);
          break;
        case 3:
          digitalWrite(_kPin1, HIGH);
          digitalWrite(_kPin2, HIGH);
          digitalWrite(_kPin3, LOW);
          digitalWrite(_kPin4, LOW);
          break;
        }
      }
    }
  }
}

unsigned int StepperMotor28BYJ48::getCurrentStep()
{
  return 0;
}