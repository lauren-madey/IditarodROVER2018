/*
 * Simple Encoder Test Sketch
 * Created by Valentin Vollmer for Ten80 Education.
 * 
 */

int encoderPin = 2;
int encoder;

void setup() {
Serial.begin (9600);                    //start Serial Communication at 9600 baud
digitalWrite (2,HIGH);                  // Set Encoder pin to high to get more reliable readings
}

void loop() {
  
encoder = digitalRead (encoderPin);
//Serial.print (encoder);

}
