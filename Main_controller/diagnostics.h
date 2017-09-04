/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Various functions for testing
 * 
 * 
 */
 
/**
 * Function to generate (fake) sensor data for testing. It needs a mean value and 
 * a margin of variation 
 * 
 * @param readings - the sensors array which needs data to be filled in
 * @param sizeReadings - the size of aforementioned readings array
 * @param meanValues - the mean value for fake sensor data
 * @param margins - the allowed variation around mean values
 */
void simulateSensorDataWithRandomNoise(double readings[], int sizeReadings, double meanValues[], double margins[]) {
    randomSeed(0L);
    long randMin, randMax; 
    for(int i = 0; i < sizeReadings; i++) {
        long randMin = (long) ((meanValues[i] - margins[i]*meanValues[i])*1000.0);
        long randMax = (long) ((meanValues[i] + margins[i]*meanValues[i])*1000.0); 
        
        readings[i] = ((double) random(randMin, randMax))/1000.0; 
    }
}

/**
 * Function to generate slope variation sensor data for testing. It considers initial values,
 * the amount of increase/decrease (sign dependent dx) and time difference (dt)
 * A different approach would need to keep track of the history of readings[] array to update
 * at the correct time. As it is, the control/decision is moved outside the function - i.e. the
 * caller needs to ensure the readings[] progress in a nice sloped variation by repeatedly 
 * calling the function with appropriate input values. Useful for testing functionality which
 * triggers off after a certain threshold (say dropping under a certain temperature threshold)
 * 
 * @param readings - the sensors array which needs data to be filled in
 * @param sizeReadings - the size of aforementioned readings array
 * @param dx - the amount dx to be added
 * @param dt - the time increment
 */
void simulateSensorDataWithSlopedVariation(double readings[], int sizeReadings, double dx[], double dt) {
    for(int i = 0; i < sizeReadings; i++) {
      readings[i] += (dx[i]/dt);
    }
}

/**
 * very basic diagnostic function (blinking the 13th pin LED) 
 * 
 * @param seconds the time in seconds it will blink
 */

 void blinkMe(int seconds) {
     int increment = 1000;
     int ledPin = 13;
     for(int i = 0; i <= (seconds*1000); i+=increment) {
         digitalWrite(ledPin, HIGH);
         delay(increment/2);
         digitalWrite(ledPin, LOW);
         delay(increment/2);
     }
 }

/**
 * Check system status and returns a fully human readable string with status concerning 
 * the diagnostic mode (always on if this function is called), autonoumous mode (read
 * autonoumous type in management.h), the status of each device (i.e. powered on or off)
 * It is the human readable version of systemStatusEncoded() from management.h
 * 
 * \return a human readable string describing the system wide status of the powered on
 * devices as well as the diagnostics and autonoumous flags
 * 
 * \TODO: add Ethernet connections statuses; correlate with its encoded version and
 * make sure there is functionality somewhere to detect when an addition to the system
 * happens (i.e. a device come online). Add another function to check for local sensors
 * status
 */
String systemStatusDecoded() {
   String result = "\nReporting powered on devices\n";
   result += "----------------------------------\n";
   result += "Diagnostic mode: ON\n";
   result += ((autonoumous == ON)?"Autonomous mode: ON\n":"Autonomous mode: OFF\n");
   for(int i = 0; i < noOfDevices; i++) {
       result += deviceLabels[i];    
       if(devices[i] == ONLINE) result += ": ONLINE\n";
       else result += ": OFFLINE\n"; 
   }
   result += "----------------------------------\n\n";
   return result; 
} 
