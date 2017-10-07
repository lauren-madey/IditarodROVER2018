/* 
Demos a to sweep a servo and measure the distance.

Servo sweeps with Sonar sensor attached to detect the path without obstacles.
After full sweep Servo returns to first position of least obstacles.

Author: Valentin Vollmer for Ten80 Education inc.
Copyright: Ten80 Education inc. Saratoga Springs, NY
Free to use in the context of Ten80 Challenges.

Version 1.0/  Jan 2016

*/ 

#include <Servo.h>          //Include Servo Library
Servo myservo;              // create servo object to control a servo 
 
int posHigh = 140;          //The highest position the servo should go to
int posLow = 50;            // the lowest position the servo should go to
int increment = 30;         //the increment the servo should move.
int minRead = 1050;         //
const int sweepSpeed = 200; //time in milliseconds the servo gets to move to a position.
const int sonarPin = 7;     // Pin the Servo is attached to
int distance, inches, pos, sense; //Vairables needed in the code       //


 
void setup() 
{ 
  myservo.attach(10);                              // attaches the servo on pin 9 to the servo object 
  Serial.begin (9600);                             // Start Serial Inteface
  int startPos = (posHigh-posLow)/2+posLow;      // Start servo out half way between  posLow and posHigh
//  Serial.println (startPos);
  myservo.write (startPos);    
} 




 
void loop() 
{ 
 // Serial.print (minRead);
  sweep ();

} 



//------------------------FUNCTIONS------------------------------------------------------------------------------

// sweep sends the servo back and forth and measures distances for every position.
void sweep ()
{ 
   myservo.write(15);
   delay(1000);
   myservo.write(30);
      delay(1000);
   myservo.write(45);
      delay(1000)
   myservo.write(60);
      delay(1000);
   myservo.write(75);
      delay(1000);
   myservo.write(90);
      delay(1000);
   myservo.write(105);
   myservo.write(120);
   myservo.write(135);
   myservo.write(150);
   myservo.write(165);
   myservo.write(180);
   myservo.write(165);
   myservo.write(150);
   myservo.write(135);
   myservo.write(120);
   myservo.write(105);
   myservo.write(90);
   myservo.write(75);
   myservo.write(60);
   myservo.write(45);
   myservo.write(30);
   myservo.write(15);   
  /*
    for(pos = posLow; pos <= posHigh; pos += increment) // goes from posLow degrees to posHigh
  {                                  // in steps of degree defined in "increment"
 // Serial.print ("pos: ");
 // Serial.println (pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(sweepSpeed);               // waits  for the servo to reach the position
    getDistance ();                 // Call the getDistance Function
  } 
  
  for(pos = posHigh; pos>=posLow; pos-=increment)     // goes from posHigh degrees to posLow degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(sweepSpeed);               // waits  for the servo to reach the position 
    getDistance ();
  } */
}


//---------------------------------Read Sonar Sensor several times and get average ------------------
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
  Serial.print (pos+180);
  Serial.print (",");
  Serial.println (tempInches);
  return tempInches; 
}
