/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <Adafruit_INA219.h>

double temperatureReadings[noOfTemperatureSensors]; //!< sensors order specified in settings.h in temperatureSensorsLabels
double currentReadings[noOfCurrentSensors]; //!< Motor, PC, Raspberry Pi current readings
double voltageReadings[noOfVoltageSensors]; //!< Motor, PC, Raspberry Pi voltage readings
double powerReadings[] = {0, 0, 0};

void initRelayPins() {
  for(byte i = 0; i < noOfRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void initCurrentSensorsPins() {
  for(byte i = 0; i < noOfCurrentSensors; i++) {
    pinMode(currentSensorsPins[i], INPUT);
  }
}

void readTemperatures(DallasTemperature sensors) {
  DeviceAddress addr;
  
  for (uint8_t s=0; s < sensors.getDeviceCount(); s++) {
        // get the unique address 
        sensors.getAddress(addr, s);
        // just look at bottom two bytes, which is pretty likely to be unique
        int smalladdr = (addr[6] << 8) | addr[7];
        
        temperatureReadings[s]=sensors.getTempCByIndex(s);
  }
}

void readPowers(Adafruit_INA219 motor, Adafruit_INA219 PC, Adafruit_INA219 rpi) {  
  double shuntvoltage[] = {motor.getShuntVoltage_mV(), PC.getShuntVoltage_mV(), rpi.getShuntVoltage_mV()};
  double busvoltage[] = {motor.getBusVoltage_V(), PC.getBusVoltage_V(), rpi.getBusVoltage_V()};
  double current_mA[] = {motor.getCurrent_mA(), PC.getCurrent_mA(), rpi.getCurrent_mA()};
  double loadvoltage[] = {shuntvoltage[0]/1000+busvoltage[0], shuntvoltage[0]/1000+busvoltage[1], shuntvoltage[0]/1000+busvoltage[2]};

  for(int i = 0; i < noOfCurrentSensors; i++) {
    currentReadings[i] = current_mA[i];
    voltageReadings[i] = loadvoltage[i];

    powerReadings[i] = currentReadings[i]*1000*loadvoltage[i];
  }  
}


