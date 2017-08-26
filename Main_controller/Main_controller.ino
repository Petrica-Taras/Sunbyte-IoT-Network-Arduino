/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include "settings.h"
#include "utils.h"
#include "communication.h"
#include "readings.h"
#include "monitoring.h"
#include "management.h"

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(temperatureSensorPin);
     
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature temperatureSensors(&oneWire);

Adafruit_INA219 MotorPower; //!< this goes directly on the I2C bus, no pin necessary!
Adafruit_INA219 PCPower(0x41);
Adafruit_INA219 RaspberryPiPower(0x44);

void setup() {
  initRelayPins();
  initCurrentSensorsPins(); //!< good for voltage and power too!

  Serial.begin(9600);
  
  temperatureSensors.begin(); 
  
  MotorPower.begin(); 
  PCPower.begin();
  RaspberryPiPower.begin();
  
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW);
  // Log2Serial(0); //!< Log2Serial
  Log2microSD(0);
  if (!SD.begin(microSDPins[3])) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } else {
    Log2microSD(0); 
  }
}

void loop() {
  if(millis() >= kickIn) {
    digitalWrite(13, HIGH);
    if(millis()%temperatureSamplingTime == 0) {
      
        readTemperatures(temperatureSensors);
        readPowers(MotorPower, PCPower, RaspberryPiPower);
        Log2microSD(1);
        /* Log2Serial(1); //!< temperatures
        Log2Serial(2); //!< currents
        Log2Serial(3); //!< voltages
        Log2Serial(4); //!< powers */
    }
  }
  else { // record to Log for every minute passed
    // if(millis()
  }

}
