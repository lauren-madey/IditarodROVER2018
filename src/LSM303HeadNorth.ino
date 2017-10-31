//NOT WORKING
//could be the position of the gyrometer
//Lauren Madey
//Iditarod Motorsports ROVER
------------------------------------------
#include <Adafruit_LSM303.h>
#include <Adafruit_LSM303_U.h>
#include <Wire.h>
#include <Servo.h>
#define SERVO  2
#define CENTER 100
#define GOAL   0

LSM303_U compass;
int      goal = GOAL;
float    declinationAngle = 0.212;    // Radians
Servo    myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO);
  Wire.begin();
  compass = LSM303_U();
  // Set scale to +/- 1.3 Ga
  int error = compass.SetScale(1.3);
  if (error != 0)
    Serial.println(compass.GetErrorText(error));
  // Set measurement mode to continous
  error = compass.SetMeasurementMode(Measurement_Continuous);
  if (error != 0)
    Serial.println(compass.GetErrorText(error));
}
void loop() {
  int angle = getDegrees();
  int error = goal - angle
  if (error >= 180)
    error -= 360;
  if (error <= -180)
    error += 360;
  // Update servo and keep with range of +/- 60
  if (error > 60)
    error = 60;
  if (error < -60)
    error = -60;
  myservo.write(CENTER + error);
  delay(10);
}
int getDegrees () {
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis) + declinationAngle;
  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;
  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;
  // Convert radians to degrees for readability.
  return (int)  (heading * 180 / M_PI);
}
