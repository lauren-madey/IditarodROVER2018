#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
  
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
 
void roveDrive(bool MotorA, bool MotorB, unsigned int speedA, unsigned int speedB)
{
  digitalWrite(12, !MotorA);
  digitalWrite(13, !MotorB);
  analogWrite(3, speedA);
  analogWrite(11, speedB);
}

void roveStop()
{
  analogWrite(3, 0);
  analogWrite(11, 0);
  delay(1);
}
 
void sleep(int sec) {
  int x = millis() + (sec * 1000);
  while (millis() < x) {;}
}

void setup(void) 
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  if(!mag.begin())
  {
    exit(-1);
  }
}
  
void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  
  roveDrive(false, true, 0, 255);
  while (!((heading > 200) || (heading < 230))) {
    float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
    Serial.println(heading);
  }

  roveDrive(true, true, 100, 100);
  sleep(2);
}
