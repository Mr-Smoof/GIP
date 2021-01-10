#include <SPI.h> 
#include <Adafruit_BME280.h>

#define BME_SCK 13 //Serial clockpin
#define BME_MISO 12 //Serial data out
#define BME_MOSI 11 //Serial data in
#define BME_CS 10 //Chip select

//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK); //software SPI


void setup()
{
  Serial.begin(9600); //serieele monitor instellen op 9600 baud

  if (!bme.begin()) //bme.begin is 'true' als de sensor is gevonden anders niet
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!"); //als de sensor niet is gevonden zal men deze error kunnen zien op de serieele monitor
    while (1); //de while zal continue en oneindig doorlopen tot de uitdrukking tussen haakjes 'false' word
  }
}

void loop()
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature()); //zet de gemeten temperatuur in de serieele monitor
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F); //zet de gemeten luchtdruk die naar hPa wordt omgezet in de serieele monitor
  //de luchtdurk wordt in Pa gemeten maar we hebben die nodig in hPa daarom de formule /100.0F
  Serial.println("hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity()); //zet de gemeten luchtvochtigheid in de serieele monitor in %
  Serial.println("%");

  delay(5000); //pauzeer het programma 5 seconden
}
