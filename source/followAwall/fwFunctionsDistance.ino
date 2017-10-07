
//-------------------getDistanceFromPosition------------------------
int getDistanceFromPosition(int pos)
{
myservo.write (pos);                      //Got position passed in argument
delay (10);                               //wait for servo to move there
return getDistance();                     //get Distacne and s it.
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

