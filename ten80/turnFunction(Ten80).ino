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

int rightSpeed1 = 245;
int leftSpeed1 = 225;
int rightSpeed2 = 245;
int leftSpeed2 = 225;

float heading;
int turnAngle;
String incoming;

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

    //If anything is on the serial port, read the full string in and store it in 'incoming'
  while (Serial.available()) {
      incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
      turnAngle = incoming.toInt();              // convert string to an integer (We need a number Angle)

      //Call turn function
      turn(turnAngle);
    } 

}


//------------------------FUNCTIONS---------------------------

//-----------------------getHEading----------------------
//This function is based on code of the Adafruit example supllied with the LSM303 LIBRARY.

float getHeading ()
{
    float Pi = 3.14159;
    float headingTotal;
    int numberReadings = 10; 
  sensors_event_t event; 
  mag.getEvent(&event); 

  for (int i=1; i<numberReadings; i++)
  {
    // Calculate the angle of the vector y,x
    float headingTemp = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi; 
    // Normalize to 0-360
    if (headingTemp < 0)
    {
      headingTemp = 360 + headingTemp;
    }
    headingTotal += headingTemp;
  }
  return headingTotal/ numberReadings;
}

//-------------------------------TURN --------------------------------------------

void turn (int angle)
{
  float turnOriginalHeading = getHeading();       //remember original heading
  float turnHeading = turnOriginalHeading;        //copy heading so it does not have to be recalculated: is faster!
  float deviation;
  int turnSpeedLeft, turnSpeedRight;

  //determineDirection to go in
  if (angle > 0)                                  //positive angle means turn right
  {
    turnSpeedLeft = 255;
    turnSpeedRight = 225;
    //turnSpeedRight = 70;
  }
  else                                           //else turn left
  {
    //turnSpeedLeft = 70;
    turnSpeedLeft=225;
    turnSpeedRight = 255;  
  }

  Serial.print ("Left Speed:");
  Serial.print (turnSpeedLeft);
  Serial.print ("\t Right Speed:");
  Serial.println (turnSpeedRight);
  delay (500);
  //Calculate how much was turned already
  deviation = turnOriginalHeading - getHeading();      //calculate deviation from original heading. 
  if (deviation > 180)                                 //compensate for transition from 359 degree to 0. This ensures continuous values in "deviation"
  {
    deviation = deviation -360;
  }
  else if (deviation < -180)
  {
    deviation = deviation +360;
  }

  while (abs (angle) > abs (deviation))                 //using absolute values [ abs() ] allows to use one statement for both positive nd negtive values.
  {
    roveDrive (HIGH,HIGH,turnSpeedLeft, turnSpeedRight);
    deviation = turnOriginalHeading - getHeading();      //calculate deviation from original heading. 
    if (deviation > 180)                                 //compensate for transition from 359 degree to 0. This ensures continuous values in "deviation"
    {
      deviation = deviation -360;
    }
    else if (deviation < -180)
    {
      deviation = deviation +360;
    }

  Serial.print ("Angle:");
  Serial.print (abs (angle));
  Serial.print ("\t deviation");
  Serial.println (abs (deviation));
  }
  roveStop();                                           //Stop Motors when done turning.
  
  Serial.println ("Stop");
}



/*
//----------------------------------Motor Control Function---------------------------------
Motor A & B are boolean, High or Low sets the direction of one side.
speedA & speedB determine the wheel speed for the sides.
A = Left
B = Right
*/
void roveDrive (bool MotorA, bool MotorB, int speedA, int speedB)
{
      digitalWrite(12,MotorA);
      digitalWrite(13,MotorB);
      analogWrite(3,speedA);
      analogWrite(11,speedB); 
}


/*
Stops motors
*/
void roveStop ()
{
      analogWrite(3,0);
      analogWrite(11,0); 
      delay(1);
}
