/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include "settings.h"
#include "utils.h"
#include "communication.h"
#include "readings.h"
#include "diagnostics.h"
#include "monitoring.h"
#include "management.h"

void setup() {
  initRelayPins();

  Serial.begin(9600);

  /**
   * Initialize sensor objects
   */
  temperatureSensors.begin(); 

  MainsPower.begin(); 
  PCPower.begin();
  TelescopePower.begin();
  AndorCameraPower.begin();
    
  // Log2Serial(0); //!< Log2Serial
  Log2microSD(INIT);
  if (!SD.begin(microSDPins[3])) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } else {
    Log2microSD(INIT); 
  }
}

void loop() {
  if(millis() >= kickIn) {
    digitalWrite(13, HIGH);
    if(millis()%temperatureSamplingTime == 0) {
      
        readTemperatures(temperatureSensors);
        readPowers(MainsPower, PCPower, TelescopePower, AndorCameraPower);
        Log2microSD(READ_TEMPERATURE);
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
