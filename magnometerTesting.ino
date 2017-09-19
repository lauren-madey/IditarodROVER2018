//Lauren Madey
//Iditarod Motorsports ROVER

volatile long count=0;       //counter for the Wheel encoder
int goSpeed=255;          //Speed for the Rover to cover distance
int rightSpeed = 245;
int leftSpeed = 225;
int approachSpeed= 120;      //Slower speed when within a cetain distance of goal
int targetDistance = 140;          //Distance ot be covered in inches. Not set here since it is sent from Computer.
int approachDistance = 140;   //Distance from target to slow down.
String incoming;

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

float heading;

void setup()
{ 
    Serial.begin(9600);
  /* Initialise the sensor COPY THIS SECTION TO YOUR CODE!! */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
  attachInterrupt(digitalPinToInterrupt (2),wheel,CHANGE);   //attach interrupt to Pin 2
   digitalWrite(2,1);                                         // enable pullup resistor on D2
   pinMode(3,  OUTPUT);    //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);    //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);    //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);    //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction
  Serial.begin(9600);
}


void loop()
{
      while (Serial.available()) 
      {
      incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
      targetDistance = incoming.toInt();              // convert string to an integer (We need a number distance)
      count =0;
      } 
  heading = getHeading ();

  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
  //If anything is on the serial port, read the full string in and store it in 'incoming'
  while (Serial.available()) {
      incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
      targetDistance = incoming.toInt();              // convert string to an integer (We need a number distance)
      count =0;
    } 
  
// Calculate distance travelled in inches
// Wheel Circumference * Pi /8 * count
float distanceTravelled = 2.975 * PI/8.00 * float (count);

Serial.println (distanceTravelled);                   //send result to Serial port



// STOP the Rover if target distance is reached or no target Distance is set.
if ((distanceTravelled >= targetDistance)) //&& (targetDistance == NULL))
{
  roveStop();
  Serial.println ("STOPPPING");
}

//Go full speed if Rover is not within target distance yet
else if (distanceTravelled < approachDistance)
{
  roveDrive (HIGH, HIGH, leftSpeed, rightSpeed);
  Serial.println ("Full Speed");
}

//Slow Rover down while within target distance
else if (distanceTravelled >= approachDistance)
{
  roveDrive (HIGH, HIGH, approachSpeed, approachSpeed);
  Serial.println ("approaching");
}


}



//------------------------FUNCTIONS ----------------------------------------


//---------Interrup Sevice Routine for Wheel encoder------------------------
void wheel()
{
  count++;                      //increment count by one whenever function is called.
  Serial.print ("w,");          
  Serial.println (count);
}

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



//----------Rover Drive Functions-----------------------------------------
/*
Motor Control Function
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
