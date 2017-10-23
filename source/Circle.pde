//NOT WORKING
//Lauren Madey
//Iditarod Motorsports ROVER

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
  
/* Assign a unique ID to this sensor at the same time */
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
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303*/
    exit(-1);
  }
}
  
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  
  roveDrive(false, true, 0, 255);
  while !((heading > 358) && (heading < 5)) {;}
  roveDrive(true, true, 100, 100);
  
  sleep(2);
}
