//Lauren Madey
//Iditarod Motorsports ROVER 

import processing.serial.*;
Serial myPort;

String inString;

PFont f;

void setup()
{
  size(1000,700);
  background(10,200,25);
  f = createFont("Arial",16,true);
  printArray(Serial.list());// prints a list of ports in the status window
  String portName = Serial.list()[0];// This is where you must match port numbers.
  myPort = new Serial(this, portName, 9600);
  

}

void draw()
{
  textFont(f,18);                  // font
  fill(0);                         // font color 
  text("Autonomous",120,40);
  text("Travel Distance",780,40);
  text("1ft",760,120); 
  text(".5ft",830,120);
  text(".1ft",900,120);
  text("Active SONAR",120,620);
  
  fill(30,25,255);
  rect(750,50,50,50); //1ft
  rect(820,50,50,50); //.5ft
  rect(890,50,50,50); // .1ft
  rect(100,50,150,50); //autonomus
  rect(100,550,150,50); // SONAR
  
  //Draw the arrows and the commands button
  fill(30,25,255);            
  rect(400,100,200,150);// Forward button
  triangle(400,100,600,100,500,50);
  
  rect(400,450,200,150);//reverse button
  triangle(400,600,600,600,500,650);
  
  rect(250,250,150,200);//left button
  triangle(250,250,250,450,200,350);
  
  rect(600,250,150,200);// right button
  triangle(750,250,750,450,800,350);
  
 //rect(x,y,width,height);
 //check Top square coordinates.
  if(mousePressed && mouseX>400&&mouseX<600&&mouseY>100&& mouseY<250)  
  {
    myPort.write("FA");
  } 
  
  //Check bottom square coordinates
  else if(mousePressed && mouseX>400&&mouseX<600&&mouseY>450&& mouseY<600)  
  {
    myPort.write("BA");
  } 
  
  //Check left square coordinates
  else if(mousePressed && mouseX>250&&mouseX<400&&mouseY>250&& mouseY<400)  
  {
    myPort.write("LA");
  } 
  
  //Check right square coordinates
  else if(mousePressed && mouseX>600&&mouseX<750&&mouseY>250&& mouseY<450)  
  {
    myPort.write("RA");
  } 
  
  //Check 1ft coordinates
  else if(mousePressed && mouseX>750&&mouseX<800&&mouseY>50&& mouseY<100)  
  {
    myPort.write("1ft");
  } 
  
  // Check .5ft coordinates
  else if(mousePressed && mouseX>820&&mouseX<870&&mouseY>50&& mouseY<100)  
  {
    myPort.write(".5ft");
  } 
  
  //Check .1ft coordinates
  else if(mousePressed && mouseX>890&&mouseX<940&&mouseY>50&& mouseY<100)  
  {
    myPort.write(".1ft");
  } 
  
  //Check autonomous coordinates
  else if(mousePressed && mouseX>100&&mouseX<250&&mouseY>50&& mouseY<100)  
  {
    myPort.write("autonomous");
  } 
  
  //Check SONAR coordinates
    else if(mousePressed && mouseX>100&&mouseX<250&&mouseY>550&& mouseY<600)  
  {
    myPort.write("SONAR");
  }
  
  else
  {
    myPort.write("5");
  }
  delay(20);
}


void mydelayfcn(int delay)
{
  int time = millis();
  while(millis() - time <= delay);
}