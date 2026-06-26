# Master-Slave Robotic Arm using ESP32 and PCA9685

Built independently from concept, electronics, mechanical assembly, wiring, programming, testing, and integration.

## Project Overview

This project is a 6-DOF (Degrees of Freedom) Master-Slave Robotic Arm controlled using six potentiometers. The master arm uses potentiometers to capture joint movements, while the slave arm replicates those movements using servo motors driven by a PCA9685 servo controller and an ESP32.

The system demonstrates real-time robotic manipulation, joint control, servo synchronization, and embedded system integration.

## Hardware Used

* ESP32 Dev Module
* PCA9685 16-Channel Servo Driver
* 6 × Potentiometers
* 2 × MG90S Servo Motors
* 4 × MG996R Servo Motors
* 2S Li-ion Battery Pack
* External Servo Power Distribution
* Blue LED Status Indicator
* Mechanical Robotic Arm Structure
* Wiring, Connectors, and Mounting Hardware

## Joint Mapping

| Joint | Function      | ESP32 Pin | PCA9685 Channel | Servo Type |
| ----- | ------------- | --------- | --------------- | ---------- |
| A     | Gripper       | GPIO 32   | 0               | MG90S      |
| B     | Wrist Roll    | GPIO 33   | 2               | MG90S      |
| C     | Wrist Pitch   | GPIO 34   | 4               | MG996R     |
| D     | Elbow         | GPIO 35   | 6               | MG996R     |
| E     | Shoulder      | GPIO 25   | 8               | MG996R     |
| F     | Base Rotation | GPIO 26   | 10              | MG996R     |

## PCA9685 Wiring

| PCA9685 | ESP32   |
| ------- | ------- |
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | GPIO 18 |
| SCL     | GPIO 19 |

## Features

* Real-time master-slave robotic arm control
* Six independent degrees of freedom
* ESP32-based control system
* PCA9685 hardware PWM servo control
* Potentiometer-based joint replication
* Blue LED movement status indicator
* Live serial monitoring and debugging
* Safe operating range for MG90S servos
* Servo C initializes at 90° during startup
* Expandable architecture for wireless control and future automation

## Approximate Project Cost

| Component              | Quantity | Approx. Cost (INR) |
| ---------------------- | -------- | ------------------ |
| ESP32 Dev Module       | 1        | ₹270               |
| PCA9685 Servo Driver   | 1        | ₹250               |
| MG996R Servo Motors    | 4        | ₹1,200             |
| MG90S Servo Motors     | 2        | ₹300               |
| Potentiometers         | 6        | ₹70                |
| Battery Pack           | 1        | ₹1300              |
| Wiring and Connectors  | -        | ₹300               |
| Mechanical Structure   | -        | ₹200               |
| Miscellaneous Hardware | -        | ₹800               |

### Total Estimated Cost

**₹4,000 – ₹5,000 INR**

The final cost depends on the servo brand, structural material, fabrication method, battery choice, and mechanical design.

## Important Power Notes

* MG90S servos should be powered from 5V–6V.
* MG996R servos require a separate high-current power source.
* ESP32, PCA9685, and servo power grounds must share a common ground.
* Avoid powering servos directly from the ESP32.

## Required Arduino Libraries

Install the following library from the Arduino IDE Library Manager:

```txt
Adafruit PWM Servo Driver Library
```

Required headers:

```cpp
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
```

## Future Improvements

* Wireless master-slave communication
* Robotic arm mounted on a mobile robotic platform
* Object detection and tracking
* Computer vision integration
* Inverse kinematics implementation
* Autonomous pick-and-place operations

## Author

Aman Sharma

Robotics | Embedded Systems | Mechatronics

This project was designed, assembled, wired, programmed, tested, and documented independently.
