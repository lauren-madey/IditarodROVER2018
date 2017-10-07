/*
 * Written By Valentin Vollmer for Ten80 Education inc.
 * 2016
 * 
 * This example reads the compass
 * and prints it to serial monitor.
 * Added is a function to let the Rover turn a level of degree sent by Serial Monitor
 * 
 * Known issues: 
 * - Fix the for loop when reading the values
 * - heading sometimes jumps.
 * 
 */


//Necessary Libraries and settings for compass
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

float heading;
int turnAngle;
String incoming;

volatile long count=0;        //counter for the Wheel encoder
int goSpeed=200;            //Speed for the Rover to cover distance
int approachSpeed= 100;       //Slower speed when within a cetain distance of goal
int approachDistance = 10;    //Distance from target to slow down.

void setup() 
{
  pinMode(3,  OUTPUT);    //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);    //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);    //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);    //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt (2),wheel,CHANGE);   //attach interrupt to Pin 2
  digitalWrite(2,1);   
  
  /* Initialise the sensor COPY THIS SECTION TO YOUR CODE!! */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }


}



//--------------------------


void loop() 
{
driveDistance(55);
//spin (-40);
spin (30);
delay(50);


driveDistance (40);
spin (30);
delay(50);

driveDistance(35);
spin(-25);
delay(50);

spin(25);
delay(50);
spin(15);
delay(50);
driveDistance(5);
delay(50);

//spin (-30);
//delay(50);
//spin (-20);
//delay(50);



while (1)
{}
}


//------------------------FUNCTIONS IN TABS!---------------------------

