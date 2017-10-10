/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include <Wire.h>
#include <Adafruit_INA219.h>

/**
 * these go on THIS I2C bus, no clash with the main controller ones!
 * obviously all these sensors are not on the motor wires (not suitable
 * for high frequency switching) but on the DC bus coming to drivers)
 */
Adafruit_INA219 elevMotor;       
Adafruit_INA219 azimMotor(0x41); 

void initMotorPins() {
    for(byte i = 0; i < noOfMotorPins; i++) {
        pinMode(motorPins[AZIMUTH][i], OUTPUT);
        pinMode(motorPins[ELEVATION][i], OUTPUT); 
    }
}

double currentReadings[] = {NAN, NAN, NAN}; //!< correlate with powerSensorsLabels
double voltageReadings[] = {NAN, NAN, NAN}; //!< just three motors
double powerReadings[] = {NAN, NAN, NAN}; //!< "Azimuth", "Elevation", "Focus"

void readPowers(Adafruit_INA219 elevMotor, Adafruit_INA219 azimMotor) {  
  double shuntvoltage[] = {elevMotor.getShuntVoltage_mV(), azimMotor.getShuntVoltage_mV()};
  double busvoltage[] = {elevMotor.getBusVoltage_V(), azimMotor.getBusVoltage_V()};
  double current_mA[] = {elevMotor.getCurrent_mA(), azimMotor.getCurrent_mA()};
  double loadvoltage[] = {shuntvoltage[0]/1000+busvoltage[0], shuntvoltage[1]/1000+busvoltage[1]};

  for(int i = 0; i < noOfPowerSensors; i++) { 
    currentReadings[i] = current_mA[i];
    voltageReadings[i] = loadvoltage[i];
    powerReadings[i] = currentReadings[i]*1000*loadvoltage[i];
  }  
}






