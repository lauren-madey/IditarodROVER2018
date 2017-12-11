//Direction, Speed of the right wheels, Speed of the left wheels, Time to run at this speed.
import processing.serial.*;
Serial myPort;

String inString;

void setup()
{
  size(1000,800);
  background(10,200,25);
  printArray(Serial.list());// prints a list of ports in the status window
  String portName = Serial.list()[0];// This is where you must match port numbers.
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  fill(30,25,255);            

  if (keyPressed) {
    if(key == UP) {
      myPort.write("FA");
    } 
    
    else if (key == DOWN) {
      myPort.write("BA");
    } 
    
    else if (key == LEFT) {
      myPort.write("LA");
    } 
    
    else if (key == RIGHT) {
      myPort.write("RA");
    } 
    else {
      myPort.write("5");
    }
  }
  delay(20);
}


void mydelayfcn(int delay)
{
  int time = millis();
  while(millis() - time <= delay);
}