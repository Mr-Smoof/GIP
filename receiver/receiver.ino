#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "AB7DC";

uint8_t var[32];

void setup() {
  Serial.begin(9600);
  radio.begin();
  
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {

  if (radio.available()) {

    radio.read(&var, sizeof(var));
    
    int temp = (var[0] << 8) & 0xFF00;
    temp = temp | var[1];
    int pres = (var[2] << 8) & 0xFF00;
    pres = pres | var[3];
    int hum = var[4];
    int IR = (var[5] << 8) & 0xFF00;
    IR = IR | var[6];
    int UVindex = (var[7] << 8) & 0xFF00;
    UVindex = UVindex | var[8];
    
    float tempPrint = temp / 100.00;
    float presPrint = pres /10.00;
    float IRPrint = IR / 100.00;
    float UVPrint = UVindex / 100.00;

    Serial.print("Temperatuur: ");
    Serial.println(tempPrint);
    Serial.print("Luchtdruk: ");
    Serial.println(presPrint);
    Serial.print("Luchtvochtigheid: ");
    Serial.println(hum);
    Serial.print("IR: ");
    Serial.println(IRPrint);
    Serial.print("UVindex: ");
    Serial.println(UVPrint);
    
  }

}
