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

boolean Log2Serial(logFlags flags) {
String content = ""; 
  
  switch(flags) {
    case INIT: //!< at the beginning
       content += "Session started!\n--------------------------------------------------------------------\n\n";       
       break;
    case READ_TEMPERATURE: //!< read temperature sensors:
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
    case READ_CURRENT: //!< currents
       content += "Event: Current sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
           content += ": ";
           content += String(currentReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------"; 
       break;   
    case READ_VOLTAGE: //!< voltages
       content += "Event: Voltage sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
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

boolean Log2microSD(logFlags flags) {
  String content = ""; 
  
  switch(flags) {
    case INIT: //!< at the beginning
       content += "Session started!\n--------------------------------------------------------------------\n\n";       
       break;
    case READ_TEMPERATURE: //!< read temperature sensors:
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
    case READ_CURRENT: //!< currents
       content += "Event: Current sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
           content += ": ";
           content += String(currentReadings[i]);
           content += "\n";
           }
       content += "--------------------------------------------------------------------\n"; 
       break;   
    case READ_VOLTAGE: //!< voltages
       content += "Event: Voltage sensor readings at ";
       content += String(millis()/1000);
       content += " seconds\n";
       for(int i = 0; i < noOfPowerSensors; i++) {
           content += String(powerSensorsLabels[i]);
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

/**
 * Check system status and returns a string with 12 digits (diagnostics, mode, one for 
 * each device - see settings.h) in the format 00000100000. If we discover there are perfomance
 * issues, we can replace the return type with an int and perform binary 
 * arithmetic to get the output.
 * \return a string with 10 digits having only 0 and 1 values only
 */
String systemStatusEncoded() {
   String result = "";
   result += ((autonoumous == ON)?"Autonomous mode is ON":"");
   for(int i = 0; i < noOfDevices; i++) {
       if(devices[i] == ONLINE) 
           result += 1;
       else
           result += 0; 
   }

   return result; 
}

