/*
 * Written By Valentin Vollmer for Ten80 Education inc.
 * 2016
 * 
 * This example reads the compass
 * and prints it to serial monitor.
 * 
 */


//Necessary Libraries and settings for compass
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

int rightSpeed1 = 70;
int leftSpeed1 = 225;
int rightSpeed2 = 70;
int leftSpeed2 = 255;

float heading;

void setup(void) 
{
  Serial.begin(9600);
  /* Initialise the sensor COPY THIS SECTION TO YOUR CODE!! */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void) 
{
  heading = getHeading ();

  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);

  if(heading > 279)
    {
        roveDrive (HIGH, HIGH, -225, -170);
    }
    if(heading < 275)
    {
      roveDrive (HIGH, HIGH, -170, -225);
    }
    if(heading >= -279 && heading <= -275)
    {
      roveDrive;
    }
}


//------------------------FUNCTIONS---------------------------

//-----------------------getHEading----------------------
//This function is based on code of the Adafruit example supllied with the LSM303 LIBRARY.

float getHeading ()
{
    float Pi = 3.14159; 
  sensors_event_t event; 
  mag.getEvent(&event); 
  
  // Calculate the angle of the vector y,x
  float headingTemp = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi; 
  // Normalize to 0-360
  if (headingTemp < 0)
  {
    headingTemp = 360 + headingTemp;
  }
  return headingTemp;
}
void roveDrive (bool MotorA, bool MotorB, int speedA, int speedB)
{
      digitalWrite(12,MotorA);
      digitalWrite(13,MotorB);
      analogWrite(3,speedA);
      analogWrite(11,speedB); 
}

void roveStop ()
{
      analogWrite(3,0);
      analogWrite(11,0); 
      delay(1);
}
