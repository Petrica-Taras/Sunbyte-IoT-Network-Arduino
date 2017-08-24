/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include <OneWire.h>
#include <DallasTemperature.h>

double temperaturesReadings[] = {20.0, 18.0, 30.0}; //!< sensors order specified in settings.h in temperatureSensorsLabels
double currentReadings[noOfCurrentSensors]; //!< Motor, PC, Raspberry Pi current readings
double voltageReadings[noOfVoltageSensors]; //!< Motor, PC, Raspberry Pi voltage readings

void initRelayPins() {
  for(byte i = 0; i < noOfRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void initTemperatureSensorsPins() {
  for(byte i = 0; i < noOfTemperatureSensors; i++) {
    pinMode(temperatureSensorsPins[i], INPUT); // internal pullup resistor?
  }
}

void initCurrentSensorsPins() {
  for(byte i = 0; i < noOfCurrentSensors; i++) {
    pinMode(currentSensorsPins[i], INPUT);
  }
}

OneWire oneWire(temperatureSensorsPins[0])

void readTemperature() {
  OneWire oneWire(temperatureSensorsPins[0]);
}


