/* Donovan Keohane
 * straight.ino
 */

#include <Wire.h>

void sleep(int sec) {
  int x = millis() + (sec * 1000);
  while (millis() < x)
  {
    ;
  }
}

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void roveDrive(bool MotorA, bool MotorB, int speedA, int speedB)
{
  digitalWrite(12, MotorA);
  digitalWrite(13, MotorB);
  analogWrite(3, speedA);
  analogWrite(11, speedB);
}

void roveStop()
{
  analogWrite(3, 0);
  analogWrite(11, 0);
  delay(1);
}

void loop()
{
  roveDrive(true, true, 100, 100);
  sleep(1);
  exit(1);
}
