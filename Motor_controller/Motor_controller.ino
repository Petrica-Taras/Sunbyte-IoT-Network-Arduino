/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include "settings.h"
#include "utils.h"
#include "communication.h"
#include "motor_control.h"
#include "diagnostics.h"
#include "readings.h"
#include "monitoring.h"

void setup() {
  initMotorPins();

  Serial.begin(9600);

  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW);
  Log2Serial(0); //!< Log2microSD
}

void loop() {

}
