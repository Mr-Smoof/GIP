int freqPin = 8;
int pulseHigh;
int pulseLow;
int pulseTotal;
float frequency;

void setup()
{
  Serial.begin(9600);
  pinMode(freqPin, INPUT);
}

void loop()
{
  pulseHigh = pulseIn(freqPin, HIGH); //meet de tijd in microseconden dat het signaal hoog is
  Serial.print("hoog: ");
  Serial.println(pulseHigh);
  
  pulseLow = pulseIn(freqPin, LOW); //meet de tijd in microseconden dat het signaal laag is
  Serial.print("laag: ");
  Serial.println(pulseLow);
  
  pulseTotal = pulseHigh + pulseLow; //telt de 2 signalen op
  Serial.print("totaal: ");
  Serial.println(pulseTotal);
  
  frequency = 1000000/pulseTotal; //berekent de frequentie
  Serial.println(frequency);
  delay(1000);
}
