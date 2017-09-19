//Lauren Madey
//Iditarod Motorsports ROVER

//Required for Servo to work
#include <Servo.h>          //Include Servo Library
Servo myservo;              // create servo object to control a servo 
const int servoPin = 10;
//End Servo Stuff



int distance;

void setup() {
Serial.begin(9600);
myservo.attach(servoPin);    // Initialize Servo

}

void loop() {

  distance = getDistanceFromPosition(10);
  Serial.println (distance);
}




//----------------------FUNCTIONS -----------------------------------

//-------------------getDistanceFromPosition------------------------
int getDistanceFromPosition(int pos)
{
int tmpAngle = map (pos,0,180, 180,0);    //inverse the position provided to match the compass.
  
myservo.write (tmpAngle);                      //Got position passed in argument
delay (10);                               //wait for servo to move there
return getDistance();                     //get Distance 
}



//-----------------------Get Distance--------------------
int getDistance ()
{
  const int sonarPin = 7; 
  int  loops = 3;                         // USe to define the number of loops
  long pulse;                             // declare long variable to read pulses from sensor
  int tempInches;
  int tempTotal=0;

  for (int i=1; i <= loops; i++)
  {
  pulse = pulseIn(sonarPin, HIGH);        //Read sensor
  tempInches = pulse/147;
  tempTotal = tempTotal + tempInches;     //Calculate inches and add to total
  }
  tempInches = tempTotal/loops;           // divide total by number of loops run
  return tempInches;                      // return inches.
}

