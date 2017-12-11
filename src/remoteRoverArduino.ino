
/*
This code was created by
Ashwin Wagadarikar and Valentin Vollmer
for Ten80 Eduction inc.
www.ten80education.com

Copyright is with Ten80 Education.

Use of this code is allowed by schools and teams 
competing in the Ten80 Rover Challenge.

Version History

12/2015 Version 2.0
- motor control is moved into a functio for more reliability and ease of use
- varibale maxSpeed is added for easier control.

2014 Original Version 1.0

MOTOER CONFIGURATION
A = Left
B = Right

*/


String readString;
int maxSpeed = 255; //Set Maximum Speed. Should never be higher than 255

void setup()
{
  // WARNING!
  //TEAMS: DO NOT CHANGE THE CODE BETWEEN THESE LINES (BEGIN)---------------------------------------
  
  pinMode(3,  OUTPUT);    //PWM control for motor outputs 1 and 2 is on digital pin 3/ A Speed
  pinMode(11, OUTPUT);    //PWM control for motor outputs 3 and 4 is on digital pin 11/ B Speed
  pinMode(12, OUTPUT);    //direction control for motor outputs 1 and 2 is on digital pin 12 RIGHT WHEELS/ A Direction
  pinMode(13, OUTPUT);    //direction control for motor outputs 3 and 4 is on digital pin 13 LEFT WHEELS/ B Direction
  Serial.begin(9600);
}


void loop() {
  
  //If anything is on the serial port, read the full string in and store it in 'readString'
  while (Serial.available()) {
    delay(10);  
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    } 
  }
  
  //If the readString has length > 0 then figure out what command was received in the string.
  if (readString.length() >0) {
    Serial.println(readString); //see what command string was received on the serial port
    
    //Determine positions of commas in the command string received on the serial port
    int commaIndex1 = readString.indexOf(',');
    int commaIndex2 = readString.indexOf(',', commaIndex1+1);
    int commaIndex3 = readString.indexOf(',', commaIndex2+1);
    
    //Break up the command string into the initcommand, left and right motor speeds and run time
    String initcommand = readString.substring(0, commaIndex1);
    String speedls = readString.substring(commaIndex1+1, commaIndex2);
    String speedrs = readString.substring(commaIndex2+1, commaIndex3);
    String runtimes = readString.substring(commaIndex3+1);
    
    int speedl = speedls.toInt();
    int speedr = speedrs.toInt();
    int runtime = runtimes.toInt();
    
    //Make sure the speeds on the left and right motors are constrained to 0-255 (or maxSpeed
    speedl = constrain(speedl, 0, maxSpeed);
    speedr = constrain(speedr, 0, maxSpeed);
   
// WARNING!
//TEAMS: DO NOT CHANGE THE CODE BETWEEN  THESE LINES (END) -----------------------------------------

if(initcommand == "L") {  //turn left with speeds 'speedl' and 'speedr' on left & right motors
      roveDrive (HIGH, LOW, speedl, speedr);  
      delay(runtime);
      delay(1);
}
else if(initcommand == "LA") {  //Left arrow
  roveDrive (HIGH, LOW, maxSpeed,maxSpeed);
  delay(10);
}    
else if(initcommand == "R") {  //turn right with speeds 'speedl' and 'speedr' on left & right motors
  roveDrive (LOW, HIGH, speedl, speedr);
  delay(runtime);
  delay(1);
}
else if(initcommand == "RA") {  //Right arrow
  roveDrive (LOW, HIGH, maxSpeed, maxSpeed);
  delay(10);
}    
else if(initcommand == "F") {  //move forward with speeds 'speedl' and 'speedr' on left & right motors
  roveDrive (HIGH, HIGH, speedl, speedr);
  delay(runtime);
  delay(1);
}
else if(initcommand == "FA") {  //Forward arrow
  roveDrive (HIGH, HIGH, maxSpeed, maxSpeed);
  delay(10);
}    
    else if(initcommand == "B") {  //move back with speeds 'speedl' and 'speedr' on left & right motors
      roveDrive (LOW, LOW, speedl, speedr);
      delay(runtime);
      delay(1);
    }
    else if(initcommand == "BA") {  //Back arrow
      roveDrive (LOW, LOW, maxSpeed, maxSpeed);
      delay(10);
    }    
    else //Stop the motors
    {  
      roveStop ();
    }
    
    //Clear out readString to prepare for the next command
    readString="";
  }  
}


//-------------Functions ------------------------------

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
