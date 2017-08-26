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
    case 1: //!< read temperature sensors:
       content += "Event: Temperature sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfTemperatureSensors; i++) {
           content += String(temperatureSensorsLabels[i]);
           content += ": ";
           content += String(temperatureReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------"; 
       break;   
    case 2: //!< currents
       content += "Event: Current sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfCurrentSensors; i++) {
           content += String(currentSensorsLabels[i]);
           content += ": ";
           content += String(currentReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------"; 
       break;   
    case 3: //!< voltages
       content += "Event: Voltage sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfVoltageSensors; i++) {
           content += String(voltageSensorsLabels[i]);
           content += ": ";
           content += String(voltageReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------"; 
       break;
    default:  //!< powers
       content += "Event: Power sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
           content += ": ";
           content += String(powerReadings[i]);
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
    case 1: //!< read temperature sensors:
       content += "Event: Temperature sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfTemperatureSensors; i++) {
           content += String(temperatureSensorsLabels[i]);
           content += ": ";
           content += String(temperatureReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n"; 
       break;   
    case 2: //!< currents
       content += "Event: Current sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfCurrentSensors; i++) {
           content += String(currentSensorsLabels[i]);
           content += ": ";
           content += String(currentReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n"; 
       break;   
    case 3: //!< voltages
       content += "Event: Voltage sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfVoltageSensors; i++) {
           content += String(voltageSensorsLabels[i]);
           content += ": ";
           content += String(voltageReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n"; 
       break;
    default:  //!< powers
       content += "Event: Power sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
           content += ": ";
           content += String(powerReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n";            
  }

  File dataFile = SD.open(logFile, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(content);
    dataFile.close();
    // print to the serial port too:
    Serial.println(content);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error writting to SD card");
  }
  Serial.println(content);
  return true; 
}


