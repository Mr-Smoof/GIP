void anemometer()
{
  int InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  windspeed = (float)InterruptCounter / (float)RecordTime * 2.4;
}

void countup()
{
  InterruptCounter++;
}
