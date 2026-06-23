#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

// Blue LED on ESP32
const int blueLED = 2;

// Potentiometer pins
const int potA = 32;  // Gripper A
const int potB = 33;  // Wrist Roll B
const int potC = 34;  // Wrist Pitch C
const int potD = 35;  // Elbow D
const int potE = 25;  // Shoulder E
const int potF = 26;  // Base F

// PCA9685 servo channels
const int servoA = 0;
const int servoB = 2;
const int servoC = 4;
const int servoD = 6;
const int servoE = 8;
const int servoF = 10;

// Servo pulse ranges
// MG90S usually works better with slightly narrower pulse range
const int MG90S_MIN = 120;
const int MG90S_MAX = 500;

// MG996R normal range
const int MG996R_MIN = 102;
const int MG996R_MAX = 512;

// Current angles
int angleA = 90;
int angleB = 90;
int angleC = 90;
int angleD = 0;
int angleE = 0;
int angleF = 0;

// Previous angles for LED movement detection
int lastA = 90;
int lastB = 90;
int lastC = 90;
int lastD = 0;
int lastE = 0;
int lastF = 0;

unsigned long lastPrintTime = 0;
unsigned long lastServoTime = 0;

// 5 lines per second = every 200 ms
const unsigned long printInterval = 200;

// Fast servo update
const unsigned long servoInterval = 10;

// Small ADC noise ignore
const int adcDeadband = 20;

int oldPotA = -1;
int oldPotB = -1;
int oldPotC = -1;
int oldPotD = -1;
int oldPotE = -1;
int oldPotF = -1;

int angleToPulse(int angle, int pulseMin, int pulseMax) {
  angle = constrain(angle, 0, 180);
  return map(angle, 0, 180, pulseMin, pulseMax);
}

int readPotStable(int pin, int &oldValue) {
  int value = analogRead(pin);

  if (oldValue < 0) {
    oldValue = value;
    return value;
  }

  if (abs(value - oldValue) > adcDeadband) {
    oldValue = value;
  }

  return oldValue;
}

void writeMG90S(int channel, int angle) {
  pca.setPWM(channel, 0, angleToPulse(angle, MG90S_MIN, MG90S_MAX));
}

void writeMG996R(int channel, int angle) {
  pca.setPWM(channel, 0, angleToPulse(angle, MG996R_MIN, MG996R_MAX));
}

void setup() {
  Serial.begin(115200);

  pinMode(blueLED, OUTPUT);
  digitalWrite(blueLED, LOW);

  Wire.begin(18, 19);

  pca.begin();
  pca.setPWMFreq(50);

  delay(500);

  // Safe startup positions
  // A and B MG90S start from 90 degree
  // C starts from 90 degree
  writeMG90S(servoA, 90);
  writeMG90S(servoB, 90);
  writeMG996R(servoC, 90);
  writeMG996R(servoD, 0);
  writeMG996R(servoE, 0);
  writeMG996R(servoF, 0);

  Serial.println("Final Safe 6 Servo Code Started");
  Serial.println("A/B = MG90S | C starts from 90 degree | Serial = 5 lines/sec");
}

void loop() {
  if (millis() - lastServoTime >= servoInterval) {
    lastServoTime = millis();

    int valueA = readPotStable(potA, oldPotA);
    int valueB = readPotStable(potB, oldPotB);
    int valueC = readPotStable(potC, oldPotC);
    int valueD = readPotStable(potD, oldPotD);
    int valueE = readPotStable(potE, oldPotE);
    int valueF = readPotStable(potF, oldPotF);

    // A and B are MG90S, so limited safely
    angleA = map(valueA, 0, 4095, 20, 160);
    angleB = map(valueB, 0, 4095, 20, 160);

    // MG996R full range
    angleC = map(valueC, 0, 4095, 0, 180);
    angleD = map(valueD, 0, 4095, 0, 180);
    angleE = map(valueE, 0, 4095, 0, 180);
    angleF = map(valueF, 0, 4095, 0, 180);

    angleA = constrain(angleA, 20, 160);
    angleB = constrain(angleB, 20, 160);
    angleC = constrain(angleC, 0, 180);
    angleD = constrain(angleD, 0, 180);
    angleE = constrain(angleE, 0, 180);
    angleF = constrain(angleF, 0, 180);

    writeMG90S(servoA, angleA);
    writeMG90S(servoB, angleB);
    writeMG996R(servoC, angleC);
    writeMG996R(servoD, angleD);
    writeMG996R(servoE, angleE);
    writeMG996R(servoF, angleF);

    bool moving = false;

    if (abs(angleA - lastA) > 3) moving = true;
    if (abs(angleB - lastB) > 3) moving = true;
    if (abs(angleC - lastC) > 3) moving = true;
    if (abs(angleD - lastD) > 3) moving = true;
    if (abs(angleE - lastE) > 3) moving = true;
    if (abs(angleF - lastF) > 3) moving = true;

    digitalWrite(blueLED, moving ? HIGH : LOW);

    lastA = angleA;
    lastB = angleB;
    lastC = angleC;
    lastD = angleD;
    lastE = angleE;
    lastF = angleF;
  }

  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    Serial.print("A:");
    Serial.print(angleA);

    Serial.print(" | B:");
    Serial.print(angleB);

    Serial.print(" | C:");
    Serial.print(angleC);

    Serial.print(" | D:");
    Serial.print(angleD);

    Serial.print(" | E:");
    Serial.print(angleE);

    Serial.print(" | F:");
    Serial.println(angleF);
  }
}