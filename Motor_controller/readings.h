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

void initMotorPins() {
    for(byte i = 0; i < noOfMotorPins; i++) {
        pinMode(motorElevationPins[i], OUTPUT); //!< just one motor now
    }
}



