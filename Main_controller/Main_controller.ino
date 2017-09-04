/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

#include "settings.h"
#include "utils.h"
#include "readings.h"
#include "communication.h"
#include "management.h"
#include "monitoring.h"
#include "diagnostics.h" //!< natural choice in positioning as it takes data from all other headers

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

  /**
   * Initialize Ethernet communication
   */
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

/**
 * Just the basic framework of a server/client architecture. 
 * Tested with telnet
 * 
 */
void loop() {
  client = server.available();    
  
  if (client && client.connected()) {
      char c = client.read(); //!< send basic commands via this once the communication protocol has been established

       if(c == 'd') { 
         Serial.println(systemStatusDecoded());
       } 
       if(c == 'f') {
         // client.println("Testing");
         Serial.println("f was pressed");
         checkConnection(5); 
         Serial.println(ethernetNetworkDevices[5]);
       } 
       if(c == 'x') {
         // client.println("Testing");
         Serial.println("x was pressed");
         client.stop(); //!< was outside the if clause
       }
  } else {
       //Serial.println("no client connected");
  }
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
