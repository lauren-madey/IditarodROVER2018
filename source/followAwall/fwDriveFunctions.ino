void roveDrive (bool MotorA, bool MotorB, int speedA, int speedB)
{
      digitalWrite(12,MotorA);
      digitalWrite(13,MotorB);
      analogWrite(3,speedA);
      analogWrite(11,speedB); 
}

void roveStop ()
{
      analogWrite(3,0);
      analogWrite(11,0); 
      delay(1);
}
