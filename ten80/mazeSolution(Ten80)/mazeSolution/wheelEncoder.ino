//---------Interrup Sevice Routine for Wheel encoder------------------------
void wheel()
{
  count++;                      //increment count by one whenever function is called.
  Serial.print ("w,");          
  Serial.println (count);
}

