//#define DEBUG
//#include <SPI.h>
#include "RF24.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013)

#include "Adafruit_SI1145.h"// Inladen van de adafruit bibliotheek

Adafruit_BME280 bme;
Adafruit_SI1145 uv = Adafruit_SI1145();
RF24 radio(9, 10);//CE, CSN
char data[32];

void setup() {
  Serial.begin(9600);

  //Serial.println("Adafruit BME280 test");
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  //Serial.println("Adafruit SI1145 test");

  if (!uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
  radio.begin();
  radio.setPALevel(RF24_PA_MAX) ;
  radio.setChannel(0x76) ;
  radio.openWritingPipe(0xF0F0F0F0E1LL) ;
  radio.enableDynamicPayloads() ;
  radio.powerUp();
}
void loop() {
  //Serial.print("Begin: ");
  //long start = millis();
  //Serial.println(start);
  uint8_t winddirection = windhaancode();
  uint16_t windspeed = anemometer();
  int16_t outTemp = bme.readTemperature() * 10; // Maak temperatuur integer om draadloos door te sturen.
  uint32_t outPres = bme.readPressure(); //Pressure is a 32 bit integer with the pressure in Pascals.
  uint8_t outHum = bme.readHumidity();

  //float VIS = (uv.readVisible());// * 100;
  //float IR = (uv.readIR());// * 100;
  uint8_t UVindex = uv.readUV();// * 10;

  data[0] = 0x24;           //Begin tag
  data[1] = winddirection;    //Winddir 1-8 N....NW
  data[2] = windspeed >> 8;   //windsnelheid eerste byte van de integer, m/s
  data[3] = windspeed;        //windsnelheid tweede byte van de integer
  data[4] = outHum;           //Luchtvochtigheid wordt weergegeven in %
  data[5] = outTemp >> 8;   //outTemp eerste byte van de integer
  data[6] = outTemp;        //outTemp tweede byte van de integer
  uint8_t regen = pluviometer();//random(25, 27);
  data[7] = regen; //regen
  data[8] = outPres >> 24;
  data[9] = outPres >> 16;
  data[10] = outPres >> 8;
  data[11] = outPres;
  data[12] = UVindex;            //uvalicht
  uint8_t batterijSpanning = 50;
  data[13] = batterijSpanning;             //batterijSpanning
  //int grondTemp = 180;  //grondTemp x 10 om geen float te moeten gebruiken
  //data[14] = grondTemp >> 8;   //grondTemp eerste byte van de integer
  //data[15] = grondTemp;        //grondTemp tweede byte van de integer
  radio.write(&data, sizeof(data));
  //Serial.print("Eind: ");
  //Serial.println(millis()-start);
  delay(1000);
  #ifdef DEBUG
  Serial.print("$,WindDir=");
  Serial.print(winddirection, DEC);
  Serial.print(",WindSpeed=");
  Serial.print(windspeed/10, 1); //0.0
  Serial.print(",Humidity=");
  Serial.print(outHum, 1); //46.5
  Serial.print(",Temp=");
  Serial.print(outTemp, 1); //29.7
  Serial.print(",Rain=0.00,Pressure=");
  Serial.print(outPres, 2); //1003.94
  Serial.print(",DewPoint=17.04,Light=");
  Serial.print(UVindex/100.0,1);//1.43
  Serial.println(",Latitude=0.000000,Longitude=0.000000,Altitude=0.00,Satellites=0,FixDate=00/00/2000,FixTime=00:00:00,Battery=3.94,#");
  #endif
}
