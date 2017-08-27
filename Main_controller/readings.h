/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <Adafruit_INA219.h>

#include <math.h>

typedef enum {INIT, READ_TEMPERATURE, READ_CURRENT, READ_VOLTAGE, READ_POWER} logFlags;

/**
 * Create placeholders for data and initialize objects for temperature and power
 */
double temperatureReadings[] = {NAN, NAN, NAN, NAN, NAN, NAN, NAN}; //!< sensors order specified in settings.h in temperatureSensorsLabels
/**
 * TODO: the mains sensor can measure up to 26 V, but the battery voltage is 28 :( . Also current wise is limited to 3 Amps (expected drain is 1.8A x 3)
 */
double currentReadings[] = {NAN, NAN, NAN, NAN}; //!< A maximum of 4, for the models we have;
double voltageReadings[] = {NAN, NAN, NAN, NAN}; //!< correlate with powerSensorsLabels
double powerReadings[] = {NAN, NAN, NAN, NAN}; //!< "Mains", "PC", "Telescope", "Camera" 

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(temperatureSensorPin);
DallasTemperature temperatureSensors(&oneWire);

Adafruit_INA219 MainsPower; //!< this goes directly on the I2C bus, no pin necessary!
Adafruit_INA219 PCPower(0x41);
Adafruit_INA219 TelescopePower(0x44);
Adafruit_INA219 AndorCameraPower(0x45);

void initRelayPins() {
  for(byte i = 0; i < noOfRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

/**
 * reads the (available) temperature sensors and populates temperatureReadings[] array
 * the available online temperature sensors are marked ONLINE
 * @param sensors an object of DallasTemperature type
 */
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

void readPowers(Adafruit_INA219 MainsPower, Adafruit_INA219 PCPower, Adafruit_INA219 TelescopePower, Adafruit_INA219 AndorCameraPower) {  
  double shuntvoltage[] = {MainsPower.getShuntVoltage_mV(), PCPower.getShuntVoltage_mV(), TelescopePower.getShuntVoltage_mV(), AndorCameraPower.getShuntVoltage_mV()};
  double busvoltage[] = {MainsPower.getBusVoltage_V(), PCPower.getBusVoltage_V(), TelescopePower.getBusVoltage_V(), AndorCameraPower.getBusVoltage_V()};
  double current_mA[] = {MainsPower.getCurrent_mA(), PCPower.getCurrent_mA(), TelescopePower.getCurrent_mA(), AndorCameraPower.getCurrent_mA()};
  double loadvoltage[] = {shuntvoltage[0]/1000+busvoltage[0], shuntvoltage[1]/1000+busvoltage[1], shuntvoltage[2]/1000+busvoltage[2], shuntvoltage[3]/1000+busvoltage[3]};

  for(int i = 0; i < noOfPowerSensors; i++) { // should be i < noOfPowerSensors;
    currentReadings[i] = current_mA[i];
    voltageReadings[i] = loadvoltage[i];

    powerReadings[i] = currentReadings[i]*1000*loadvoltage[i];
  }  
}



