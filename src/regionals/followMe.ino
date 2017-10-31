/* Lauren Madey
 * followMe.ino
 */


/*L         R    
 --         --   [] --> rover veers to RIGHT with this program
|  |__[ ]__|  |  [] --> ultra sonic sensor points this way 
 --| front |--   []
   |       |     []
   |       |     []
 --|       |--   [] 
|  | back  |  |  []
 --|_______|--   []
   |_|           []
   (_)           [] 
 */
int distance;

void setup() {
  Serial.begin(9600);
}

void loop() {
  distance = getDistance();       // Call getDistance function to get value in inches.. 
  Serial.println(distance);  
  if (distance > 10) {            // If object is over 10 inches away.
    roveDrive(true,true,50,100);  // Keep driving!
  } else {
    roveStop();                   // Otherwise stop.
  }
}

//----------------------FUNCTIONS -----------------------------------

//-----------------------Get Distance--------------------
int getDistance()
{
  const int sonarPin = 7; 
  long pulse;                             // Declare long variable to read pulses from sensor.
  int loops = 3;                          // Use to define the number of loops.
  int tempInches;
  int tempTotal=0;

  for (int i=1; i <= loops; i++) {
    pulse = pulseIn(sonarPin, true);      //Read sensor
    tempInches = pulse/147;
    tempTotal = tempTotal + tempInches;   //Calculate inches and add to total
  }

  tempInches = tempTotal/loops;           // divide total by number of loops run
  return tempInches;                      // return inches.
}

void roveDrive(bool MotorA, bool MotorB, int speedA, int speedB)
{
  digitalWrite(12,!MotorA);
  digitalWrite(13,!MotorB);
  analogWrite(3,speedA);
  analogWrite(11,speedB); 
}

void roveStop()
{
  analogWrite(3,0);
  analogWrite(11,0); 
  delay(1);
}
