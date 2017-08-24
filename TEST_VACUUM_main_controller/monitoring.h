/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Provides functionality for recording data for later analysis
 * 
 * Provides variables, data structures and functions to deal with 
 * SD card storage or alternatively saving to external sources via
 * Ethernet or Serial ports (if available)
 * 
 */

/*! \fn bool Log2microSD(byte event) 
 *  \brief writes to microSD card, updating the Log file.
 *  \param event a byte showing .
 *  \return a boolean value showing if the write operation succeded or not.
 */

#include <SPI.h>
#include <SD.h>

boolean Log2Serial(byte event) {
  String content = ""; 
  
  switch(event) {
    case 0: //!< at the beginning
       content += "Session started!\n--------------------------------------------------------------------\n\n";       
       break;
    default: //!< read temperature sensors:
       content += "Event: Temperature sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfTemperatureSensors; i++) {
           content += String(temperatureSensorsLabels[i]);
           content += ": ";
           content += String(temperaturesReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------";    
  }

  Serial.println(content);
  return true; 
}

boolean Log2microSD(byte event) {
  String content = ""; 
  
  switch(event) {
    case 0: //!< at the beginning
       content += "Session started!\n--------------------------------------------------------------------\n\n";       
       break;
    default: //!< read temperature sensors:
       content += "Event: Temperature sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfTemperatureSensors; i++) {
           content += String(temperatureSensorsLabels[i]);
           content += ": ";
           content += String(temperaturesReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n";    
  }

  Serial.println(content);
  return true; 
}


