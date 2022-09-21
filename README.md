<h1 align="center">StepperMotor28BYJ48</h1>

StepperMotor28BYJ48 is a library for controlling the 28BYJ-48 stepper motor in conjunction with a driver based on the Darlington transistor assembly (ULN2003APG).

The library supports:
  - Control of the engine operation mode (full-step | half-step)
  - Control of the engine speed (from 0 to 100%)
  - Control of the direction of rotation of the engine (clockwise | counterclockwise)

<h1 align="center">Installing the library</h1>

Installation via **library Manager** (*arduino IDE*):
  - Enter the menu: Manage Libraries
  - Find the StepperMotor28BYJ48 library and install the latest version

Installing the **local library** (*arduino IDE*):
  - Enter the menu: Sketch > Connect Library > Add .zip library
  - Select yashz file StepperMotor28BYJ48.zip

Installation **manually** (*cross-platform for IDE*):
  - Go to This computer > Documents > Arduino > libraries
  - Unpack the zip file StepperMotor28BYJ48.zip along this path

<h1 align="center">How to get started? & Example</h1>

First of all, to use the library, you need to install it (**see the point above**) and connect it to the sketch.

After connecting to the library, create a class object with an arbitrary name for accessing it, 4 arguments must be passed to the class object. Pay attention to your arduino board and the contacts to which you have connected the stepper motor (there should be 4 of them), their numbers in order and will serve as arguments for creating a class object.

To change the engine speed, call the **\<setSpeed>** function and pass an argument (number) to it. The argument is the percentage component (from <0%> to <100%>), in case of specifying a number more than <100> - <100> will be used. By default, <100%> of the engine speed is used.

To change the engine operation mode, call the **\<setStepMode>** function and pass an argument to it (type \<StepModeType>), after specifying the type, refer to its variants via the binary operator <::> and choose one of the options. \<StepModeType::fullStep> - full-step engine operation mode. \<StepModeType::halfStep> - half-step engine operation mode. When using the full-step engine operation mode, the engine acquires the highest rated rotation speed and higher torque, but loses the accuracy of step rotation, when using the half-step mode, everything is exactly the opposite. By default, the full-step engine operation mode is used.

To change the direction of rotation of the engine, call the function **\<setRotationDirection>** and pass an argument to it (type \<RotationDirectionType>), after specifying the type, refer to its variants via the binary operator <::> and choose one of the options. \<RotationDirectionType::clockwise> - clockwise rotation of the motor. \<RotationDirectionType::counterClockwise> - engine rotations counterclockwise. By default, clockwise rotation is used.

To start the engine, call the **\<step>** function and pass an argument (number) to it. The expected number of steps by the engine is used as an argument.

A basic example of using the library.

```cpp
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
```

For more examples for working with the engine, see the folder **\</examples>**

<h1 align="center">License</h1>

Copyright (c) Xlebp Rjanoi (xlebpushek). All rights reserved.

Licensed under the [MIT](LICENSE) license.
