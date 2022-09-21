#include "StepperMotor28BYJ48.h"

StepperMotor28BYJ48::StepperMotor28BYJ48(const unsigned int kPin1, const unsigned int kPin2, const unsigned int kPin3, const unsigned int kPin4)
    : _kPin1(kPin1), _kPin2(kPin2), _kPin3(kPin3), _kPin4(kPin4), _step_mode(StepModeType::fullStep), _rotation_direction(RotationDirectionType::clockwise), _time_between_steps(0)
{
  pinMode(kPin1, OUTPUT);
  pinMode(kPin2, OUTPUT);
  pinMode(kPin3, OUTPUT);
  pinMode(kPin4, OUTPUT);

  StepperMotor28BYJ48::setSpeed(100);
}

void StepperMotor28BYJ48::setSpeed(const unsigned int kSpeed)
{
  _time_between_steps = 6e+7 / (((15 * (_step_mode == StepModeType::halfStep ? 4075 : 2037)) / 100) * (kSpeed > 100 ? 100 : kSpeed));
}

void StepperMotor28BYJ48::setRotationDirection(const RotationDirectionType kRotationDirection)
{
  _rotation_direction = kRotationDirection;
}

void StepperMotor28BYJ48::setStepMode(const StepModeType kStepMode)
{
  _step_mode = kStepMode;
}

void StepperMotor28BYJ48::step(const unsigned int kSteps)
{
  unsigned int steps = kSteps;
  unsigned int current_step;
  unsigned long time_since_last_step;

  while (steps > 0)
  {
    if (micros() - time_since_last_step >= _time_between_steps)
    {
      time_since_last_step = micros();

      if (_rotation_direction == RotationDirectionType::clockwise)
      {
        current_step++;
        if (current_step == kSteps)
          current_step = 0;
      }
      else
      {
        if (current_step == 0)
          current_step = kSteps;
        current_step--;
      }

      steps--;

      if (_step_mode == StepModeType::halfStep)
      {
        /*
          O - Orange pin.
          Y - Yellow pin.
          P - Pink pin.
          B - Blue pin.

          ┏━━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓
          ┃ step ┃  O  ┃  Y  ┃  P  ┃  B  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  8	 ┃  1  ┃  0  ┃  0  ┃  1  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  7	 ┃  0  ┃  0  ┃  0  ┃  1  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  6	 ┃  0  ┃  0  ┃  1  ┃  1  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  5	 ┃  0  ┃  0  ┃  1  ┃  0  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  4	 ┃  0  ┃  1  ┃  1  ┃  0  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  3	 ┃  0  ┃  1  ┃  0  ┃  0  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  2   ┃  1  ┃  1  ┃  0  ┃  0  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  1   ┃  1  ┃  0  ┃  0  ┃  0  ┃
          ┗━━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┛

        */
        switch (current_step % 8)
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
      else
      {

        /*
          O - Orange pin.
          Y - Yellow pin.
          P - Pink pin.
          B - Blue pin.

          ┏━━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓
          ┃ step ┃  O  ┃  Y  ┃  P  ┃  B  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  3   ┃  1  ┃  0  ┃  0  ┃  1  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  2   ┃  0  ┃  0  ┃  1  ┃  1  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  1   ┃  0  ┃  1  ┃  1  ┃  0  ┃
          ┣━━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫
          ┃  0	 ┃  1  ┃  1  ┃  0  ┃  0  ┃
          ┗━━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┛
        */
        switch (current_step % 4)
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
