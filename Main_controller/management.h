/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Provides functionality to control the power usage
 * 
 * Provides variables, data structures and functions to deal with
 * relays, autonomous mode and so on;
 * 
 */

/**
 * Check system status and returns a string with 10 letters (one for 
 * each device) in the format 000100000. If we discover there are perfomance
 * issues, we can replace the return type with an int and perform binary 
 * arithmetic to get the output.
 * \return a string with 10 digits having only 0 and 1 values only
 */
String systemStatus() {
   String result = "";

   for(int i = 0; i < noOfDevices; i++) {
       if(devices[i] == ONLINE) 
           result += 1;
       else
           result += 0; 
   }

   return result; 
}



