void driveDistance (int targetDistance)
{
  count =0;                                                     //reset the wheel counter
float distanceTravelled = 2.975 * PI/8.00 * float(count);

  while (distanceTravelled < targetDistance)
{
// Calculate distance travelled in inches
// Wheel Circumference * Pi /8 * count


Serial.println (distanceTravelled);                   //send result to Serial port

// STOP the Rover if target distance is reached.
if (distanceTravelled >= targetDistance)
{
  roveStop();
  Serial.println ("STOPPPING");
}

//Go full speed if Rover is not within target distance yet
else if (distanceTravelled < approachDistance)
{
  roveDrive (HIGH, HIGH, goSpeed, goSpeed);
  Serial.println ("Full Speed");
}

//Slow Rover down while within target distance
else if (distanceTravelled >= approachDistance)
{
  roveDrive (HIGH, HIGH, approachSpeed, approachSpeed);
  Serial.println ("approaching");
}
distanceTravelled = 2.975 * PI/8.00 * float(count);
}
  roveStop();
  Serial.println ("STOPPPING");
}
