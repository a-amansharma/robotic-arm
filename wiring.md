# ⚠️ Important Power & Safety Precautions

Read this section completely before connecting power to the robotic arm.

## Servo Voltage Limits

### MG90S Servo Motors

* Recommended operating voltage: **4.8V – 6V**
* Do NOT connect MG90S servos directly to a 2S Li-ion battery (7.4V nominal, 8.4V fully charged).
* Exceeding 6V may permanently damage the servo electronics.

### MG996R Servo Motors

* Recommended operating voltage: **4.8V – 7.2V**
* Use an appropriate high-current power supply.

---

## Recommended Power Setup

Use a DC-DC Buck Converter between the battery and the servo power rail.

```txt
Battery
   ↓
Buck Converter (5V–6V Output)
   ↓
PCA9685 Servo Power Terminal (V+)
```

This provides stable voltage and significantly reduces the risk of damaging servos.

---

## Common Ground Requirement

The following grounds MUST be connected together:

* ESP32 GND
* PCA9685 GND
* Servo Power Supply GND

Failure to use a common ground may result in:

* Unstable servo movement
* Random servo behavior
* Communication issues
* Potential hardware damage

---

## Protect Your ESP32

Servos can generate electrical noise and voltage spikes during startup, stopping, or under heavy load.

Recommended:

* Use a dedicated servo power supply.
* Do not power servos from the ESP32.
* Use a buck converter with adequate current capability.
* Verify polarity before applying power.

Possible consequences of incorrect power wiring:

* Servo overheating
* Servo failure
* ESP32 overheating
* ESP32 regulator damage
* Permanent microcontroller failure

---

## Pre-Power Checklist

Before connecting the battery:

* [ ] Servo supply voltage verified with a multimeter
* [ ] Buck converter adjusted correctly
* [ ] Common ground connected
* [ ] PCA9685 VCC connected to ESP32 3.3V
* [ ] SDA connected to GPIO 18
* [ ] SCL connected to GPIO 19
* [ ] No loose wires
* [ ] No short circuits
* [ ] Servo polarity verified

---

# Wiring Guide

This document contains the complete wiring reference for the Master-Slave Robotic Arm project.

---

# ESP32 ↔ PCA9685

| PCA9685 Pin | ESP32 Pin |
| ----------- | --------- |
| VCC         | 3.3V      |
| GND         | GND       |
| SDA         | GPIO 18   |
| SCL         | GPIO 19   |

---

# Potentiometer Connections

Each potentiometer uses:

* One outer pin → 3.3V
* One outer pin → GND
* Center pin → ESP32 Analog Input

| Potentiometer | Joint             | ESP32 Pin |
| ------------- | ----------------- | --------- |
| a             | Gripper (A)       | GPIO 32   |
| b             | Wrist Roll (B)    | GPIO 33   |
| c             | Wrist Pitch (C)   | GPIO 34   |
| d             | Elbow (D)         | GPIO 35   |
| e             | Shoulder (E)      | GPIO 25   |
| f             | Base Rotation (F) | GPIO 26   |

---

# Servo Channel Mapping

| Joint | PCA9685 Channel | Servo Type |
| ----- | --------------- | ---------- |
| A     | 0               | MG90S      |
| B     | 2               | MG90S      |
| C     | 4               | MG996R     |
| D     | 6               | MG996R     |
| E     | 8               | MG996R     |
| F     | 10              | MG996R     |

---

# Blue LED

| Component       | ESP32 Pin |
| --------------- | --------- |
| Blue Status LED | GPIO 2    |

Behavior:

* ON when any servo is moving
* OFF when all servos are stationary

---

# Startup Position

| Joint | Startup Angle |
| ----- | ------------- |
| A     | 90°           |
| B     | 90°           |
| C     | 90°           |
| D     | 0°            |
| E     | 0°            |
| F     | 0°            |

---

# PCA9685 Configuration

```cpp
Wire.begin(18, 19);
pca.begin();
pca.setPWMFreq(50);
```

Servo Frequency:

```txt
50 Hz
```

---

# Notes

* Alternate PCA9685 channels are used: 0, 2, 4, 6, 8, and 10.
* All potentiometers provide real-time joint control.
* Servo C initializes at 90° during startup.
* Designed for future integration with wireless communication and mobile robotic platforms.
