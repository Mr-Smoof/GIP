int windhaan = A3;
int graden;
int spanning;
int waarde;

void setup() {
 // pinMode(A3, INPUT);
 Serial.begin(9600);
 }

char windrichting(){
  waarde = analogRead(A3);
  
  Serial.println(waarde);
  delay(1000);
}

void loop() {
  windrichting();
}
