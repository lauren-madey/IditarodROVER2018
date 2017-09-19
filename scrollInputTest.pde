//Lauren Madey
//Iditarod Motorsports ROVER

import controlP5.*;

ControlP5 jControl;


void setup()
{
  size(1000,800);
  jControl = new ControlP5(this);
  
  Slider s = jControl.addSlider("encoderDistance", 0, 10, 0, 10, 10, 700, 50);
}

void draw()
{
  background(0);
}