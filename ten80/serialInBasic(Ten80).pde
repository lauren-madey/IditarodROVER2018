/*

This is a barebone sketch to receive serial data.
data is stored in varibale "inString" as a string!! 
It might have to be converted to an integer using int(inString);

Serial data is processed as it is received through an event function.

Created by: Valentin Vollmer for Ten80 Education inc.

Copyright:
Free to use in connection with Ten80 Curriculum
Credit must be given for reused portions of the code. 

History:
V 1.0: Displays one arc inidicating distance sent by Arduino.  


*/

import processing.serial.*;
Serial myPort;                                                // Create object from Serial class
String inString;
int distance;

void setup ()
{
    size (500,500);                                          //draws main window 
    printArray (Serial.list());                              //Show all serial ports available
    String portName = Serial.list()[0];                      //Select serial port. Change number in []
    myPort = new Serial(this, portName, 9600);               //Open selected serial port
}


//------------------------Main Part of sketch, edit here! ------------------------------------
void draw ()
{
  background(255);
  plotArc (distance, 270);


}



//--------------------------FUNCTIONS ----------------------------------------------------

//-----------------------Serial Event Function ----------------------------
/*
This is an event function, i. e. it is triggered by a pre defined event, not called from the draw loop. 
This particualr one gets triggered as soon as serial data becomes available. 
*/
void serialEvent (Serial myPort)
{
   inString = myPort.readStringUntil('\n');                 //Get whatever was sent to serial port until a newline is detected. Store in global varible inString
                                                            //Arduino sends a newline character (\n)at the end of the Serial.Println statement.
   if (inString != null)                                    //if inString is not (!=) empty (null) 
   {
      inString = trim (inString);      //Remove any leading or trailing spaces
       distance = int (inString);
   }

}

//----------------------------End Function -----------------------------------

void plotArc (float distance, float angle)
{
  int wide = 30;
  float start = radians (angle - wide/2);
  float stop = radians (angle + wide/2);
  
  noStroke();
  fill (0,0,225);
  arc (width/2,500,distance,distance,start,stop,PIE);
}