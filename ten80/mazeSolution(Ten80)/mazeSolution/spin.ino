
//-----------------------getHEading----------------------
//This function is based on code of the Adafruit example supllied with the LSM303 LIBRARY.

float getHeading ()
{
    float Pi = 3.14159;
    float headingTotal;
    int numberReadings = 2; 
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

//-------------------------------TURN --------------------------------------------

void spin (int angle)
{
  float turnOriginalHeading = getHeading();       //remember original heading
  float turnHeading = turnOriginalHeading;        //copy heading so it does not have to be recalculated: is faster!
  float deviation, previousDeviation;
  int wheelSpeed = 255;
  bool motorLeft, motorRight;

  //determineDirection to go in
  if (angle > 0)                                  //positive angle means turn right
  {
    motorLeft = HIGH;
    motorRight =LOW;
  }
  else                                           //else turn left
  {
    motorLeft = LOW;
    motorRight =HIGH;
  }

  Serial.print ("Left Speed:");
  Serial.print (motorLeft);
  Serial.print ("\t Right Speed:");
  Serial.println (motorRight);
//  delay (500);
  //Calculate how much was turned already
  deviation = turnOriginalHeading - getHeading();      //calculate deviation from original heading. 
  previousDeviation = deviation;                         // save this reading to check for outliers the next time around
  if (deviation > 180)                                 //compensate for transition from 359 degree to 0. This ensures continuous values in "deviation"
  {
    deviation = deviation -360;
  }
  else if (deviation < -180)
  {
    deviation = deviation +360;
  }
 
  
  while (abs (angle) > abs (deviation))                 //using absolute values [ abs() ] allows to use one statement for both positive nd negtive values.
  {
    roveDrive (motorLeft,motorRight,wheelSpeed, wheelSpeed);
    deviation = turnOriginalHeading - getHeading();       //calculate deviation from original heading. 
  
       
    if (deviation >= 180)                                 //compensate for transition from 359 degree to 0. This ensures continuous values in "deviation"
    {
      deviation = deviation -360;
    }
    else if (deviation <= -180)
    {
      deviation = deviation +360;
    }

   
        //Check for outliers! Ignore readings that are more than a few degrees higher than the previous one. This makes sure "freak" readings don't not stop the turn.  
    if (deviation > previousDeviation + 15.00)
    {
      
      Serial.print ("Correcting. Previous: ");
      Serial.print (previousDeviation);
      Serial.println ("\t current:  ");
      Serial.println (deviation);
      //Ignore the last reading if it was over 10% higher than the last one.
      deviation = previousDeviation;
      }
    previousDeviation = deviation;                                                    // save this reading to check for outliers the next time around

    
  Serial.print ("Angle:");
  Serial.print (abs (angle));
  Serial.print ("\t deviation");
  Serial.print (abs (deviation));
  Serial.print ("\t last deviation: ");
  Serial.println (previousDeviation);
  }
  roveStop();                                           //Stop Motors when done turning.
  
  Serial.println ("Stop");
}

