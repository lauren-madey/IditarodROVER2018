/*
 * Written By Valentin Vollmer for Ten80 Education inc.
 * 2016
 * 
 * This example reads the compass
 * and prints it to serial monitor.
 * Added is a function to let the Rover turn a level of degree sent by Serial Monitor
 * 
 * 3/9/2016 
 * Added control to successfully deal with outliers.
 * 
 */


//Necessary Libraries and settings for compass
#include <Wire.h>                                                         
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

float heading;
int turnAngle;
String incoming;

void setup() 
{
  pinMode(3,  OUTPUT);    //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);    //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);    //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);    //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction
  
  Serial.begin(9600);
  /* Initialise the sensor COPY THIS SECTION TO YOUR CODE!! */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}


void loop() 
{
    //If anything is on the serial port, read the full string in and store it in 'incoming'
  if (Serial.available()) {
      incoming = Serial.readStringUntil ('\n');       //get whatever was sent via the serial port unitl a line break
      turnAngle = incoming.toInt();                   // convert string to an integer (We need a number Angle)
      Serial.print ("got something: ");
      Serial.println (turnAngle);
      //Call turn function
      spin(turnAngle);
    } 

}


//------------------------FUNCTIONS---------------------------
//-------------------------------SPIN --------------------------------------------
/*Version 1.0
 * Takes degrees as input, all calculations performed in Radians
 * heading is taken within this function to avoid Stack Overflow.
 * Includes Error Correction for outlier by letting the Rover stop and take up to 10 more readings. 
 * 
 * 
 * Takes an degree angle as input and spins Rover to desired position.
 * Values are restricted between -180 and 180. 
 * Larger or smaller values are adjusted to those max or min values. 
 * 
 */


void spin (float angleRadians)
{
  //Declare all variables needed in this function
  //Configuration Variables
  const float margin = 0.2;                                //Defines the outlier error margin.
  const float increment = 0.35;                            // The increments in which the Rover takes breaks. in Radians.
  const float tolerance = 0.10;                             //Tolerance setting to exit the do .. while loop earlier.
  int wheelSpeed = 235;
  const int driveTime = 200;
  
  //no change needed variables.
  const float Pi = 3.14159; 
  float nextIncrement = increment;
  bool motorLeft, motorRight;                       //booleans to determine Motor directions.
  float startHeading,turnRadians, lastTurnRadians, turnDifference, lastTurnDifference;
  int errorCount, overCount;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------
 *Receive the angle in degrees
 * Positive Value means turn right, negative means turn left. 
 */
  //determine Direction to go in
  if (angleRadians > 0) {                                //positive angle means turn right. Set Left and Right motor speeds accordingly 
    motorLeft = HIGH;
    motorRight =LOW;
  }
  else  {                                                //else turn left. Set Left and Right motor speeds accordingly
    motorLeft = LOW;
    motorRight =HIGH;
  }

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------
 * Change Degree angle to absolute radians.
 * Get Start Heading
 * 
 * from here on out work only with absolute Values to make it work in both directions regardless.
 */
  angleRadians = constrain (angleRadians, -179,179);     //Incoming Values over 180 degrees confuse the Rover, so constaring here with a slight error margin.
 angleRadians = abs (radians(angleRadians));            //change degree value to absolute radians value.
 //Get Heading and calculate how much was turned.
  //float currentHeading = getHeading ();
  sensors_event_t event; 
  mag.getEvent(&event);
 startHeading = atan2(event.magnetic.y,event.magnetic.x); 
  // Normalize to 0-2 PI
  if (startHeading < 0)  {
    startHeading = 2* Pi + startHeading;
  };
 Serial.print ("Start Heading: ");
 Serial.println (startHeading);


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------
 * Begin Sequnece:
 * Check direction
 * Check if current turn is within error Margin
 * turn wheels
 */

 do
 {
  beginning:                                                                          //This is a label used in the loop to return here if an outlier was detected.

//Get Heading and calculate how much was turned.
  //float currentHeading = getHeading ();
  sensors_event_t event; 
  mag.getEvent(&event); 
  // Calculate the angle of the vector y,x
  float currentHeading = atan2(event.magnetic.y,event.magnetic.x); 
  // Normalize to 0-2 PI
  if (currentHeading < 0)  {
    currentHeading = 2* Pi + currentHeading;
  }

  
  turnRadians = startHeading - currentHeading;                                         //Calculate how many degrees were turned from the start Heading and stor in turn Radians
  
  if( turnRadians > Pi) {                                                             //These 2 statments ensure a consistenlty increasing turnRadians Velue when corssing the 0 reading.
    turnRadians -= 2*Pi;
  }
  else if  (turnRadians < -Pi) {
      turnRadians += 2*Pi;
    }
  turnRadians = abs (turnRadians);                                                    //Make them absolute to be able to use one while statement ofr positive and negative values.

  turnDifference = turnRadians - lastTurnRadians;                                     //Calculate how many radians was turned just now.

/*
 * Error Correction.
 * Compare this turnRadians reading against the last one. 
 * If it is larger than defined in "margin", correction has to be taken.
 * the Rover is stopped and the code sent back to the beginning of the loop
 * to take another reading.
 */
if (turnDifference > lastTurnDifference + margin)
{  
  /*Uncomment for debugging                                                             
  Serial.print ("Correction!");
  Serial.print ("\t erroCount: ");
  Serial.print (errorCount);
  Serial.print ("\t lastturnDiff: ");
  Serial.print (lastTurnDifference);
  Serial.print ("\t turnDiff: ");
  Serial.println (turnDifference);
  */
  roveStop();                                                                         //Stop the Rover to avoid more errors and being stuck in and error correction loop.
  delay (100);
                                                                    
//Send Rover back to beginning 10 times, then resume duty.
  if (errorCount < 10){ 
      errorCount ++;                                                                  //increment ErrorCount by one to make sure the Rover exists out of Error Correction at some point.
    goto beginning;                                                                   //Go to the label "beginning" in the beginning of the do...while loop.
  }
                                                                     
}

/*
 * When the turn is over 180 degrees the value of turnRadians will decrease again.
 * If that happens before the target margin is detected, the Rover will keep spinning forever.
 * 
 * So check if that happens a few times in a row, then bail out!
 */

if(turnRadians > 2.5 && turnRadians < lastTurnRadians){
  overCount++;
  /*
  Serial.print ("\t lastturnRadians: ");
  Serial.print (lastTurnRadians);
  Serial.print ("\t turnRadians: ");
  Serial.print (turnRadians);
  Serial.print ("\t BoverCount: ");
  Serial.println (overCount);
  */
}
else{
  //all good, reset overCount
  overCount = 0;
}

if(overCount >= 3){
 // Serial.println ("bailing OUt!");
break;                                                                            //bailout!
}



/*  If the code gets here, all is good! No Error detected so 
 *  record all the values and spin the wheels!
 *  Reset errorCount and 
 *   Record turnRadians to be able to compare to it next Time around.
 */

 
  Serial.print ("Current Heading ");
  Serial.println (currentHeading);

  /*
  Serial.print ("\t turnRadians: ");
  Serial.print (turnRadians);
  Serial.print ("\t lastTurnRadians: ");
  Serial.print (lastTurnRadians);
  Serial.print ("\t turnDiff: ");
  Serial.println (turnDifference);
  */

  errorCount = 0;
  lastTurnRadians = turnRadians;                                                    //Save turnRadiance to be able to compare the next one to it.
  lastTurnDifference = turnDifference;
  


/*
 * Let the Rover drive
 */
  roveDrive (motorLeft, motorRight, wheelSpeed, wheelSpeed);

  /*
   * Take a break in the Radians intervalls defined in "increment"
   * This will make the Rover move slower and more controlled towards the desired angle.
   */
   if (turnRadians >= nextIncrement){
    roveStop();
 //   Serial.print ("Taking a break at: ");
 //   Serial.println (turnRadians);
    delay (300);
    nextIncrement = turnRadians + increment;
   }

  
  } while (turnRadians < angleRadians - tolerance );

  roveStop ();
  Serial.println ("STOP");
}



