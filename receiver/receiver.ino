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
    int val = (var[0] << 8) & 0xFF00;
    // Serial.println(val, HEX);
    val = val | var[1];
    //Serial.println(val, DEC);
    //Serial.print("var0 ");
    // Serial.println(var[0], HEX);
    // Serial.print("var1 ");
    // Serial.println(var[1], HEX);

    int pres = (var[2] << 8) & 0xFF00;
    pres = pres | var[3];

    float inf = val / 100.00;
    float presPrint = pres /10.00;
    Serial.println(inf);
    Serial.println(presPrint);
  }

}
