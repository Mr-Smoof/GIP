#include <SPI.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013)

#include "Adafruit_SI1145.h"// Inladen van de adafruit bibliotheek

Adafruit_BME280 bme;
Adafruit_SI1145 uv = Adafruit_SI1145();

//Declaraties windhaan
int windhaan = A3;
int windrichting;
int coordinaat;

//Declaraties anemometer
const int RecordTime = 3; //Define Measuring Time (Seconds)
const int SensorPin = 3;  //Define Interrupt Pin (2 or 3 @ Arduino Uno)
int InterruptCounter;
float windspeed;

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
  /*

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
  */

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
  windhaancode();
  anemometer();

  int temp = (bme.readTemperature()) * 100;
  var[0] = (temp >> 8) & 0xFF;
  var[1] = temp & 0xFF;

  int pres = (bme.readPressure() / 100.0F) * 10;
  var[2] = (pres >> 8) & 0xFF;
  var[3] = pres & 0xFF;

  int hum = (bme.readHumidity());
  var[4] = hum;

  int VIS = (uv.readVisible()) * 100;
  var[5] = (VIS >> 8) & 0xFF;
  var[6] = VIS & 0xFF;

  int IR = (uv.readIR()) * 100;
  var[5] = (IR >> 8) & 0xFF;
  var[6] = IR & 0xFF;

  float UVindex = uv.readUV();
  int UV = (UVindex) * 100;
  var[7] = (UV >> 8) & 0xFF;
  var[8] = UV & 0xFF;


  // First, stop listening so we can talk.
  radio.stopListening();

  // Take the time, and send it.  This will block until complete
  //Serial.println(F("Now sending the DATA. "));
  radio.write(&var, sizeof(var));

  // Now, continue listening
  radio.startListening();

  Serial.print("$,");
  Serial.print("WindDir=");
  Serial.print(coordinaat);
  Serial.print(",");
  Serial.print("WindSpeed=");
  Serial.print(windspeed);
  Serial.print(",");
  Serial.print("Humidity=");
  Serial.print(hum);
  Serial.print(",");
  Serial.print("Temp=");
  Serial.print(temp);
  Serial.print(",");
  Serial.print("Rain=");
  Serial.print("0");
  Serial.print(",");
  Serial.print("Pressure=");
  Serial.print(pres);
  Serial.print(",");
  Serial.print("DewPoint=");
  Serial.print("0");
  Serial.print(",");
  Serial.print("Light=");
  Serial.print(VIS);
  Serial.print(",");
  Serial.print("Latitude=");
  Serial.print("0.000000");
  Serial.print(",");
  Serial.print("Longitude=");
  Serial.print("0.000000");
  Serial.print(",");
  Serial.print("Altitude=");
  Serial.print("0.00");
  Serial.print(",");
  Serial.print("Satellites=");
  Serial.print("0");
  Serial.print(",");
  Serial.print("FixDate=");
  Serial.print("00/00/2000");
  Serial.print(",");
  Serial.print("FixTime=");
  Serial.print("00:00:00");
  Serial.print(",");
  Serial.print("Battery=");
  Serial.print("0.00");
  Serial.print(",");
  Serial.print("#");
  
  delay(5000);

}
