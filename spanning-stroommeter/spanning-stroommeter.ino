#include <Wire.h>

#include "Beastdevices_INA3221.h" // 

#define SERIAL_SPEED      115200    // serial baud rate
#define PRINT_DEC_POINTS  3         // decimale punten om te printen

// zet I2C address naar 0x41 (A0 pin -> VCC)
Beastdevices_INA3221 ina3221(INA3221_ADDR41_VCC);

void setup() {
  Serial.begin(SERIAL_SPEED);

  while (!Serial) {
    delay(1);
  }

  ina3221.begin();
  ina3221.reset();

  // zet de shunt resistors naar 10 mOhm voor alle kanalen.
  ina3221.setShuntRes(10, 10, 10);

  // zet series filter naar 10 mOhm voor alle kanalen.
  // Serie filterweerstanden introduceren fouten in de stroommeting.
  //De fout kan worden geschat en is afhankelijk van de weerstandswaarden en de busspanning.
  ina3221.setFilterRes(10, 10, 10);
}

void loop() {
  float current[3];
  float current_compensated[3];
  float voltage[3];

  current[0] = ina3221.getCurrent(INA3221_CH1);
  current_compensated[0] = ina3221.getCurrentCompensated(INA3221_CH1);
  voltage[0] = ina3221.getVoltage(INA3221_CH1);

  current[1] = ina3221.getCurrent(INA3221_CH2);
  current_compensated[1] = ina3221.getCurrentCompensated(INA3221_CH2);
  voltage[1] = ina3221.getVoltage(INA3221_CH2);

  current[2] = ina3221.getCurrent(INA3221_CH3);
  current_compensated[2] = ina3221.getCurrentCompensated(INA3221_CH3);
  voltage[2] = ina3221.getVoltage(INA3221_CH3);

  Serial.print("Channel 1: \n Current: ");
  Serial.print(current[0], PRINT_DEC_POINTS);
  Serial.print("A\n Compensated current: ");
  Serial.print(current_compensated[0], PRINT_DEC_POINTS);
  Serial.print("\n Voltage: ");
  Serial.print(voltage[0], PRINT_DEC_POINTS);
  Serial.println("V");

  Serial.print("Channel 2: \n Current: ");
  Serial.print(current[1], PRINT_DEC_POINTS);
  Serial.print("A\n Compensated current: ");
  Serial.print(current_compensated[1], PRINT_DEC_POINTS);
  Serial.print("\n Voltage: ");
  Serial.print(voltage[1], PRINT_DEC_POINTS);
  Serial.println("V");

  Serial.print("Channel 3: \n Current: ");
  Serial.print(current[2], PRINT_DEC_POINTS);
  Serial.print("A\n Compensated current: ");
  Serial.print(current_compensated[2], PRINT_DEC_POINTS);
  Serial.print("\n Voltage: ");
  Serial.print(voltage[2], PRINT_DEC_POINTS);
  Serial.println("V\n");

  delay(1000);
}
