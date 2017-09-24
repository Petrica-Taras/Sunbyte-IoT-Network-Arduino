/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

/**
 * Controls two motor/axes in an open loop manner. For positioning only, the focusing motor
 * will require a different function (it will be different model most likely). The axis order
 * in decisional structures is AZIMUTH, ELEVATION
 * 
 * \param steps an array with two members specifying the steps to rotate for the two axis
 * \param rDirection an two members array giving the direction to rotate for the two axis (true - clocwise, false - anticlockwise)
 * \param mMode an array with two members setting the type of step ((true - default step, false - microstep)
 * 
 */
void twoAxisOpenLoopMotors(int steps[], boolean rDirection[], boolean mMode[], int mDelay) {
      /**
       * Decide which axis has a bigger number of steps!
       * 
       * for now assume the delay is the same for each axis
       */
      int decide = (steps[AZIMUTH] > steps[ELEVATION])?0:1;  
  
      if(rDirection[AZIMUTH]==true) {
        digitalWrite(motorPins[AZIMUTH][DIRECTIONPIN], HIGH);
      } else {
        digitalWrite(motorPins[AZIMUTH][DIRECTIONPIN], LOW);
      }

      if(rDirection[ELEVATION]==true) {
        digitalWrite(motorPins[ELEVATION][DIRECTIONPIN], HIGH);
      } else {
        digitalWrite(motorPins[ELEVATION][DIRECTIONPIN], LOW);
      } 
      
      if(mMode[AZIMUTH]==true) {
        digitalWrite(motorPins[AZIMUTH][STEPSELECTPIN], HIGH);
      } else {
        digitalWrite(motorPins[AZIMUTH][STEPSELECTPIN], LOW);
      }  

      if(mMode[ELEVATION]==true) {
        digitalWrite(motorPins[ELEVATION][STEPSELECTPIN], HIGH);
      } else {
        digitalWrite(motorPins[ELEVATION][STEPSELECTPIN], LOW);
      }        

  /**      
   * loop first for the smaller number of steps      
   */
  for(int i = 0; i < steps[!decide]; i++) {
      digitalWrite(motorPins[decide][ONPIN], HIGH);
      digitalWrite(motorPins[!decide][ONPIN], HIGH);      
      delayMicroseconds(mDelay);
      digitalWrite(motorPins[decide][ONPIN], LOW);
      digitalWrite(motorPins[!decide][ONPIN], LOW);      
      delayMicroseconds(mDelay);       
  }
  /**
   * loop for the rest of steps
   */
  for(int i = steps[!decide]; i < steps[decide]; i++) {
      digitalWrite(motorPins[decide][ONPIN], HIGH);
      delayMicroseconds(mDelay);
      digitalWrite(motorPins[decide][ONPIN], LOW);
      delayMicroseconds(mDelay);      
  }  
}  

/**
 * quick fix for github - needs to be merged properly
 * into the rest of the code
 */
void sendToSerial() {
  char* results = (char*) malloc(8*sizeof(char));
  int localCounter = 0; // char level
  int fullCounter = 0;  // char level
  int countWords = 0;   // full word level

 
  while(countWords < 6) {
    char ch =  Serial.read(); 

    if(ch == -1) continue; 
    
    //Serial.print(ch); 
    
        if((ch == ' ') || (countWords == 5)) {
            results[localCounter] = '\0';       
            localCounter=0; 

            if(countWords == 0) {
              steps[0] = atol(results);
            } 
            if(countWords == 1) {
              steps[1] = atol(results); 
            } 
            if(countWords == 2) {
              rDirection[0] = atoi(results); 
            }
            if(countWords == 3) {
              rDirection[1] =  atoi(results); 
            } 
            if(countWords == 4) {
              mMode[0] = atoi(results); 
            }
            if(countWords== 5) {
                results[localCounter] = ch;
                results[localCounter+1] = '\0';
                mMode[1] = atoi(results); 
                free(results);
                fun(steps, rDirection, mMode);
                break; 
            } 
            countWords++;
            // Serial.println(countWords); 

        }       
        else {
            results[localCounter]=ch; 
            localCounter++; 
            
        }
        
        // Serial.print('a'); 
  }
  
       shutDown(); 
       countWords = 0;
       localCounter = 0; 
       steps[0] = 0; steps[1] = 0; 
       rDirection[0] = 0; rDirection[1] = 0;
       mMode[0] = 0; mMode[1] = 0;

       // Serial.flush(); 

}