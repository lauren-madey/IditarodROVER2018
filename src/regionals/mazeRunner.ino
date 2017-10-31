/* 
 */


volatile long count=0;       //counter for the Wheel encoder
int goSpeed=255;             //Speed for the Rover to cover distance
int approachSpeed= 120;      //Slower speed when within a cetain distance of goal
int targetDistance;          //Distance ot be covered in inches. Not set here since it is sent from Computer.
int approachDistance = 5;   //Distance from target to slow down.
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
  /* This section allows for a input coming from the serial port to determine the distance
   * This can be used later for sending a distance wirlessly throught the Xbee
-------------------------------------------------------------------------------------------
  //If anything is on the serial port, read the full string in and store it in 'incoming'
  while (Serial.available()) {
      incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
      targetDistance = incoming.toInt();            // convert string to an integer (We need a number distance)
      count =0;
    } */
 
 for (int x=0; x<2; x++) // for( intialize variable, condition, incremnet)
 {
   travelBlock();
 }
 
 delay(1000);           // wait 1 second
 
 for (int y=0; y<1; y++) 
 {
   roveDrive(HIGH, LOW, goSpeed, goSpeed);
   delay(4000);
   roveStop();
 }

   delay(1000);   

 for (int z=0; z<1; z++) 
 {
   roveDrive(LOW, HIGH, goSpeed, goSpeed);
   delay(4000);
   roveStop();
 }
 

}






//------------------------FUNCTIONS ----------------------------------------

//-----------------------Driving a certian distance-------------------------
void travelBlock()
{  
// Calculate distance travelled in inches
// Wheel Circumference * Pi /8 * count
float distanceTravelled = 2.975 * PI/8.00 * float (count);

Serial.println (distanceTravelled);                   //send result to Serial port

targetDistance=3;

// STOP the Rover if target distance is reached or no target Distance is set.
if ((distanceTravelled >= targetDistance)) //&& (targetDistance == NULL))
{
  roveStop();
  Serial.println ("STOPPPING");
}

//Go full speed if Rover is not within target distance yet
else if (distanceTravelled < approachDistance)
{
  roveDrive (HIGH, HIGH, goSpeed, goSpeed);
  Serial.println ("Full Speed");
}

//Slow Rover down while within target distance
else if (distanceTravelled >= approachDistance)
{
  roveDrive (HIGH, HIGH, approachSpeed, approachSpeed);
  Serial.println ("approaching");
}
}

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
      digitalWrite(12,!MotorA);
      digitalWrite(13,!MotorB);
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
