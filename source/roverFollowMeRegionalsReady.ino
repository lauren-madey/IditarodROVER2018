
//Iditarod Rover
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

  distance = getDistance();           //Call getDistance function to get value in inches.. 
  Serial.println (distance);  
  if (distance > 10)                  //if the closest object is further away than 10 inches
  {
  roveDrive (HIGH,HIGH,50,100);        //keep driving!
  }
  else 
  roveStop();                         //otherwise stop.

}




//----------------------FUNCTIONS -----------------------------------

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

void roveDrive (bool MotorA, bool MotorB, int speedA, int speedB)
{
      digitalWrite(12,!MotorA);
      digitalWrite(13,!MotorB);
      analogWrite(3,speedA);
      analogWrite(11,speedB); 
}

void roveStop ()
{
      analogWrite(3,0);
      analogWrite(11,0); 
      delay(1);
}
