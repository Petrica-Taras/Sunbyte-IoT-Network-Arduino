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

void setup() {
  initRelayPins();

  Serial.begin(9600);

  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW);
  Log2Serial(0); //!< Log2microSD
}

void loop() {
  if(millis() >= kickIn) {
    digitalWrite(13, HIGH);
    if(millis()%temperatureSamplingTime == 0) {
        Log2Serial(1);
    }
  }
  else { // record to Log for every minute passed
    // if(millis()
  }

}
