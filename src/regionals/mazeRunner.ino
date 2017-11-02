/* Lauren Madey
 * mazeRunner.ino
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

volatile long count=0;
int goSpeed=255;
int approachSpeed= 120;
int targetDistance;
int approachDistance = 5;
String incoming;

float getHeading () {
  float Pi = 3.14159;
  sensors_event_t event;
  mag.getEvent(&event);

  float headingTemp = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

  if (headingTemp < 0)
  {
    headingTemp = 360 + headingTemp;
  }
  return headingTemp;
}

void setup() { 
  Serial.begin(9600);

  if(!mag.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  attachInterrupt(digitalPinToInterrupt(2),wheel,CHANGE);
  digitalWrite(2,1);
  pinMode(3,  OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void sleep(float sec) {
  int x = millis() + (sec * 1000);
  while (millis() < x) {;}
}

void right() {
  heading = getHeading();
  target = floor(getHeading()) + 90.0;
  if (target < 0)
  {
    target = 360 + target;
  } else if (target > 360) {
    target -= 360;
  }
  roveDrive(false, true, goSpeed, goSpeed);
  while (heading > heading+5.0 || heading < heading-5.0) {
    header = getHeader();
  }
  printf("Reached correct 90 degree right.")
  roveStop();
  sleep(0.5);
}

void left() {
  heading = getHeading();
  target = floor(getHeading()) - 90.0;
  if (target < 0)
  {
    target = 360 + target;
  } else if (target > 360) {
    target -= 360;
  }
  roveDrive(false, true, goSpeed, goSpeed);
  while (heading > heading+5.0 || heading < heading-5.0) {
    header = getHeader();
  }
  printf("Reached correct 90 degree left.")
  roveStop();
  sleep(0.5);
}

void loop()
{
  travelBlock()
  sleep(1.0)
  right()
  left()
}

void travelBlock()
{  
  float distanceTravelled = 2.975 * PI/8.00 * float(count);

  Serial.println(distanceTravelled);

  targetDistance=3;

  if (distanceTravelled >= targetDistance)
  {
    roveStop();
    Serial.println("Stopping");
  }

  else if (distanceTravelled < approachDistance)
  {
    roveDrive(true, true, goSpeed, goSpeed);
    Serial.println("Full Speed");
  }

  else if (distanceTravelled >= approachDistance)
  {
    roveDrive(true, true, approachSpeed, approachSpeed);
    Serial.println("Approaching");
  }
}

void wheel()
{
  count++;
  Serial.print("w,");          
  Serial.println(count);
}

void roveDrive (bool MotorA, bool MotorB, int speedA, int speedB)
{
      digitalWrite(12,!MotorA);
      digitalWrite(13,!MotorB);
      analogWrite(3,speedA);
      analogWrite(11,speedB); 
}

void roveStop ()
{
      analogWrite(3,0);
      analogWrite(11,0); 
      delay(1);
}
