//----------Rover Drive Functions-----------------------------------------
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
