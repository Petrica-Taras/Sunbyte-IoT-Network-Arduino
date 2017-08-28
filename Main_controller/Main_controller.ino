/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include "settings.h"
#include "utils.h"
#include "readings.h"
#include "communication.h"
#include "diagnostics.h"
#include "monitoring.h"
#include "management.h"

void setup() {
  initRelayPins();
  
  Wire.begin(); 
  Serial.begin(9600);
  pinMode(13, OUTPUT); 

  /**
   * Initialize sensor objects
   */
  temperatureSensors.begin(); 

  MainsPower.begin(); 
  PCPower.begin();
  TelescopePower.begin();
  AndorCameraPower.begin();

  Ethernet.begin(MAC, ip);
  server.begin();
    
  Log2Serial(INIT); //!< Log2Serial
  /*Log2microSD(INIT);
  if (!SD.begin(microSDPins[3])) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } else {
    Log2microSD(INIT); 
  }*/


}

void loop() {
/**
 * Just the basic framework of a server/client architecture. 
 * Tested with telnet
 */
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
       char c = client.read(); //!< send basic commands via this once the communication protocol has been established

       if(c == 'd') { 
         Serial.println("d was pressed");
       } 
       if(c == 'f') {
         // client.println("Testing");
         Serial.println("f was pressed");
       //} 
      }
    }
  }
  client.stop();  
/*  if(millis() >= kickIn) {
    if(millis()%temperatureSamplingTime == 0) {
      
        readTemperatures(temperatureSensors);
        readPowers(MainsPower, PCPower, TelescopePower, AndorCameraPower);
        Log2microSD(READ_TEMPERATURE);
        /* Log2Serial(1); //!< temperatures
        Log2Serial(2); //!< currents
        Log2Serial(3); //!< voltages
        Log2Serial(4); //!< powers 
    }
  }
  else { // record to Log for every minute passed
    // if(millis()
  }*/

}
