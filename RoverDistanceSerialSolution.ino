//Lauren Madey
//Iditarod Motorsports ROVER

/*
 * Version 3/10/17
 * 
 * 9m= about 300.33
 * ---------------------------------------------------------------------------------
 * Tests
 * -----
 * WARNING - the results from the tests do not always yeild the same results
 * (when the rightSpeed=245, leftSpeed=225)
 *   |
 *   |
 *   |
 *   V
 * 9m: targetDistance=324, approachingDistance=325
 * 9m: targetDistance=326, approachingDistance=325
 *  9.5m: targetDistance=360, approachingDistance=358
 * DONT USE 10m: targetDistance=384, approachingDistance=380
 * 10m: targetDistance=370, approachingDistance=369
 * 10m: targetDistance=364, approachingDistance=362(dont like as much as one above)
 *  10.5m: targetDistance=385, approachingDistance=383
 * 11m: targetDistance=400,  approachingDistance=395
 *  11.5: targetDistance=430,  approachingDistance=428
 * 12m: targetDistance=428, approachingDistance=420
 * ---------------------------------------------------------------------------------
 */


volatile long count=0;       //counter for the Wheel encoder
int goSpeed=255;          //Speed for the Rover to cover distance
int rightSpeed = 255;
int leftSpeed = 255;
int approachSpeed= 255;      //Slower speed when within a cetain distance of goal
int targetDistance = 92;          //Distance ot be covered in inches. Not set here since it is sent from Computer.
int approachDistance = 60;   //Distance from target to slow down.
String incoming;


void setup()
{ 
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
