#include <Arduino.h>
#include <SimplexNoise.h>
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

SimplexNoise sn;
Adafruit_PWMServoDriver PCA1 = Adafruit_PWMServoDriver(0x40, Wire);
Adafruit_PWMServoDriver PCA2 = Adafruit_PWMServoDriver(0x41, Wire);
Adafruit_PWMServoDriver PCA3 = Adafruit_PWMServoDriver(0x42, Wire);

unsigned long previousMillis = 0;
const long interval = 30;

double n;
double n2;
double n3;
float increase = 0.01;
float x = 0.0;
float y = 0.0;
float y2 = 0.3;
float y3 = 0.3;

void setup()
{
  Serial.begin(9600);
  Serial.println("PCA9685LEDv1");

  Wire.begin();
  PCA1.begin();
  PCA1.setPWMFreq(1600); // This is the maximum PWM frequency and suited to LED's

  PCA2.begin();
  PCA2.setPWMFreq(1600);

  PCA2.begin();
  PCA2.setPWMFreq(1600);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    n = sn.noise(x, y);
    n2 = sn.noise(x, y2);
    n3 = sn.noise(x, y3);
    x += increase;
    n = ((n + 1) * 0.5) * 4095;   // 2047
    n2 = ((n2 + 1) * 0.5) * 4095; // 2047
    n3 = ((n3 + 1) * 0.5) * 4095; // 2047

    for (int i = 0; i <= 15; i++)
    {
      PCA1.setPWM(i, 0, n);
      PCA2.setPWM(i, 0, n2);
      PCA3.setPWM(i, 0, n3);
    }

    Serial.println(n);
  }
}