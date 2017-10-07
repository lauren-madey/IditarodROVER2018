//Lauren Madey
//Iditarod Motorsports ROVER

//Required for Servo to work
#include <Servo.h>          //Include Servo Library
Servo myservo;              // create servo object to control a servo 
const int servoPin = 10;
//End Servo Stuff


volatile long count=0;        //counter for the Wheel encoder
int idealDistance=20;         //Change value for the distance you would like to maintain to the wall.
int maxSpeed = 150;
int correctionFactor = 8;
int lSpeed, rSpeed, distance,diff;
float distanceTravelled;
float distanceTarget = 120;
bool motorLeft = HIGH;
bool motorRight = HIGH;

void setup()
{
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt (2),wheel,CHANGE);   //attach interrupt to Pin 2
digitalWrite(2,1);  

myservo.attach(servoPin);    // Initialize Servo
myservo.write (180);          //Look left...
  pinMode(3,  OUTPUT);    //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);    //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);    //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);    //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction

}

void loop() {

  distance = getDistance();
  diff = distance - idealDistance;

  Serial.print (distance);
  Serial.print ("\t diff: ");
  Serial.print (diff);
  Serial.print ("\t L Motor: ");
  Serial.print (motorLeft);
  Serial.print ("\t lSpeed: ");
  Serial.print (lSpeed);
    Serial.print ("\t R Motor: ");
  Serial.print (motorRight);
  Serial.print ("\t rSPeed: ");
  Serial.print (rSpeed);
  Serial.print ("\t distanceTravelled: ");
  Serial.println (distanceTravelled);
//set both motors to go forward by default
  motorLeft = HIGH;
  motorRight = HIGH;

  //negative values: too close. Slow down right wheels
if (diff <0)
{
  lSpeed = constrain (maxSpeed - (diff * correctionFactor), maxSpeed, 255);             // deduct a negative value will make this go higher. it will always be between maxSpeed and 255
  rSpeed = maxSpeed + (diff * correctionFactor);                              //add diff since it is a negative value.
  //if rSpeed is a negative Value, reverse the Right Motor and send the absolute speed to it
  
  if (rSpeed < 50)
   {
    motorRight = LOW;
    Serial.print (rSpeed);
    Serial.println ("RIGHT LOW!!!'");
    rSpeed = abs (rSpeed);
   }
}

  //positive value: too far, slow down left wheels. 
else if (diff > 0)
{
  lSpeed = maxSpeed - (diff * correctionFactor);  
  rSpeed = constrain (maxSpeed + (diff * correctionFactor),maxSpeed, 255);                                                           // it will always be between maxSpeed and 255

    if (lSpeed < 50)
   {
    motorLeft = LOW;
    Serial.print (lSpeed);
    Serial.println ("LEFT LOW!!!'");
    lSpeed = abs (lSpeed);
   }
}

distanceTravelled = 2.975 * PI/8.00 * float(count);

//Drive the Rover if Distance is not yet reached. 
if (distanceTravelled < distanceTarget)
{
// Drive the Rover with the defined Speeds. 
roveDrive (motorLeft, motorRight, lSpeed, rSpeed);  
}
else
{
  roveStop();  
}
}




//----------------------FUNCTIONS: ALL IN TABS! -----------------------------------

