//#define DEBUG
const float bucketAmount = 0.2794;   // mm equivalent of ml to trip tipping-bucket
float rain = 0.00;
unsigned int InterruptCount = 0;

unsigned int pluviometer()
{
  //detachInterrupt(digitalPinToInterrupt(RainPin));
  rain = (float)InterruptCount * (float)bucketAmount;
  InterruptCount = 0;
#ifdef DEBUG
  Serial.print(rain, 4);
  Serial.println(" mm");
#endif

  return rain;
}
void count()
{
  InterruptCount++;
}
