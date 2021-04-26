#define DEBUG

#define RainPin 2                         // The Rain input is connected to digital pin 2 on the arduino

bool Tip = false;             // one of the two positions of tipping-bucket
const float bucketAmount = 0.2794;   // mm equivalent of ml to trip tipping-bucket
float rain = 0.0;

unsigned int pluviometer()
{
  if ((Tip == false) && (digitalRead(RainPin) == HIGH))
  {
    Tip = true;
    rain += bucketAmount;        // update the rain
#ifdef DEBUG
    Serial.print(rain, 4);
    Serial.println(" mm");
#endif
  }

  if ((Tip == true) && (digitalRead(RainPin) == LOW))
  {
    Tip = false;
  }
  return rain;
}
