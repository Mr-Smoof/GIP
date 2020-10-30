#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013)


#include "Adafruit_SI1145.h"// Inladen van de adafruit bibliotheek


Adafruit_BME280 bme;

Adafruit_SI1145 uv = Adafruit_SI1145();


static char sendTemp[253];//temperatuur
static char sendHum[254];//luchtvochtigheid
static char sendPres[255];//druk
static char sendAlt[256];//hoogte



/*
  const int min_payload_size = 4;
  const int max_payload_size = 32;
  const int payload_size_increments_by = 1;
  int next_payload_size = min_payload_size;
*/

RF24 radio(9, 10);//CE, CSN
const byte address[6] = "AB7DC";
//const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};
//char receive_payload[max_payload_size + 1];
uint8_t var[32];

void setup()
{
  Serial.begin(9600);
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("Adafruit SI1145 test");

  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }

  Serial.println("OK!");


  radio.begin();
  // enable dynamic payloads
  radio.enableDynamicPayloads();
  radio.setRetries(5, 15);
  radio.openWritingPipe(address);
  //radio.openReadingPipe(1, pipes[1]);
  radio.setPALevel(RF24_PA_MIN);
  

}

void loop(void)
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  Serial.print("Vis: ");
  Serial.println(uv.readVisible());
  Serial.print("IR: ");
  Serial.println(uv.readIR());
  float UVindex = uv.readUV();
  UVindex /= 100.0;
  Serial.print("UV: ");
  Serial.println(UVindex);

  Serial.println("Sending Data: ");

  int temp = (bme.readTemperature()) * 100;
  Serial.print("temp: ");
  Serial.println(temp);
  var[0] = (temp >> 8) & 0xFF;
  Serial.print(var[0], HEX);
  Serial.println("-------------");
  var[1] = temp & 0xFF;
  Serial.print(var[1], HEX);
  Serial.println("-------------");

  int pres = (bme.readPressure() / 100.0F) * 10;
  Serial.print("pres: ");
  Serial.println(pres);
  var[2] = (pres >> 8) & 0xFF;
  var[3] = pres & 0xFF;

  int hum = (bme.readHumidity());
  Serial.print("hum: ");
  Serial.println(hum);
  var[4] = hum;

  // First, stop listening so we can talk.
  radio.stopListening();

  // Take the time, and send it.  This will block until complete
  Serial.println(F("Now sending the DATA. "));
  radio.write(&var, sizeof(var));

  // Now, continue listening
  radio.startListening();
  delay(7000);

}
