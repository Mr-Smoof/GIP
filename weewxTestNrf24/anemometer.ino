//Declaraties anemometer
//#define DEBUG
const byte RecordTime = 3; //Define Measuring Time (Seconds)
const byte SensorPin = 3;  //Define Interrupt Pin (2 or 3 @ Arduino Uno)
unsigned int InterruptCounter = 0;

unsigned int anemometer()
{
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  float windspeed = ((float)InterruptCounter / (float)RecordTime) * 2.4;
  unsigned int windspeed_int = windspeed * 10;    //Make windspeed integer to send wireless
  unsigned int windspeedConstrained = constrain(windspeed_int, 0, 1024);
#ifdef DEBUG
  Serial.print("windspeed: ");
  Serial.println(windspeed);
#endif
  return windspeedConstrained;
}

void countup()
{
  InterruptCounter++;
}
