/*
 * targetDistance Tests
 * ---------------------
 * targetDistance=10
 * (tighten screws on wheel)
 * 66.5 cm
 * 72.0 cm
 * 69.5 cm
 * (tightened screws on wheel)
 * 67.0 cm
 * 72.5 cm
 * (added weight on the back right side to account for weight of the encoder)
 * 64.5 cm
 * 68.0 cm
 * 68.0 cm
 * 65.0 cm
 */


volatile long count=0;             //counter for the Wheel encoder
const int goSpeed=255;             //Speed for the Rover to cover distance
const int approachSpeed=120;       //Slower speed when within a cetain distance of goal
const int approachDistance = 5;    //Distance from target to slow down.
int targetDistance;                //Distance to be covered in inches. Initized here and set later.
String incoming;


void setup()
{ 
  attachInterrupt(digitalPinToInterrupt(2),wheel,CHANGE);    //attach interrupt to Pin 2
  digitalWrite(2,1);                                         // enable pullup resistor on D2
  pinMode(3,  OUTPUT);                                       //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);                                       //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);                                       //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);                                       //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction
  Serial.begin(9600);
}



void loop()
{
  /*
      This section allows for a input coming from the serial port to determine the distance
      This can be used later for sending a distance wirlessly throught the Xbee
      -------------------------------------------------------------------------------------------
      //If anything is on the serial port, read the full string in and store it in 'incoming'
      while (Serial.available()) {
          incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
          targetDistance = incoming.toInt();            // convert string to an integer (We need a number distance)
          count =0;
      }
  */
  targetDistance=10;

  // Calculate distance travelled in inches
  // Wheel Circumference * Pi /8 * count
  float distanceTravelled = 2.975 * PI/8.00 * float (count);

  Serial.println(distanceTravelled); //send result to Serial port

  // STOP the Rover if target distance is reached or no target Distance is set.
  if (distanceTravelled >= targetDistance) {
    roveStop();
    Serial.println("STOPPING");
  }

  //Go full speed if Rover is not within target distance yet
  else if (distanceTravelled < approachDistance) {
    roveDrive(HIGH, HIGH, goSpeed, goSpeed);
    Serial.println("Full speed");
  }

  //Slow Rover down while within target distance
  else if (distanceTravelled >= approachDistance) {
    roveDrive(HIGH, HIGH, approachSpeed, approachSpeed);
    Serial.println("Approaching");
  }
}


//------------------------FUNCTIONS ----------------------------------------

//---------Interrup Sevice Routine for Wheel encoder------------------------
void wheel()
{
  count++; //increment count by one whenever function is called.
  Serial.print("w,");          
  Serial.println(count);
}

/*----------Rover Drive Functions-----------------------------------------
Motor Control Function
Motor A & B are boolean, High or Low sets the direction of one side.
speedA & speedB determine the wheel speed for the sides.
A = Left
B = Right
*/
void roveDrive(bool MotorA, bool MotorB, int speedA, int speedB)
{
  digitalWrite(12,!MotorA);
  digitalWrite(13,!MotorB);
  analogWrite(3,speedA);
  analogWrite(11,speedB); 
}


// Stops motors
void roveStop()
{
  analogWrite(3,0);
  analogWrite(11,0); 
  delay(1);
}
