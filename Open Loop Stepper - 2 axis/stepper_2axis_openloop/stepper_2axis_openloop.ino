/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 */

#include "settings.h"                  
#include "motors.h"

int stepCounter_ELEV = 0;    
int stepCounter_AZIM = 0;
int stepsPerRev = 4096;  
int index = 0;
int elevation = 0;
int azimuth = 0;
const int MaxChars = 5;
char strValue_ELEV[MaxChars+1];
char strValue_AZIM[MaxChars+1];
boolean first = true; 

 
//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };
 
void setup()
{
  initMotors();
  Serial.begin(9600);
}
 
void loop()
{
  serialEvent();
}

void serialEvent()
{
 
   while(Serial.available()) 
   {
      char ch = Serial.read();
      //Serial.write(ch);
      // comma separator
      // first split the code in two strings

      
      if (isDigit(ch)||(ch=='-')||(ch==',')) {
          if((index < MaxChars) && (first == true) && (ch!=',')) { 
                strValue_ELEV[index++] = ch; 
          }  else if(ch==',') {
                first = false;
                strValue_ELEV[index] = 0;
                index = 0;
          }
          else {
                strValue_AZIM[index++] = ch;
          }
      }
      
      if(ch == '\n'){
            strValue_AZIM[index] = 0; 
            elevation = atoi(strValue_ELEV);
            azimuth = atoi(strValue_AZIM);
            
            controlMotor(elevation, azimuth);	
            		
            strValue_ELEV[0] = 0;
            strValue_AZIM[0] = 0;

            index = 0;
            first = true;
          }
      }  
      cutMotorsPower();
      
   }
 
 
void directionELEV(int eDirection) {
    if(eDirection > 0) {
        stepCounter_ELEV++;
        if (stepCounter_ELEV >= numSteps) stepCounter_ELEV = 0;
    } else if(eDirection == 0) {
        // do nothing
      }
    else { // anticlockwise
        stepCounter_ELEV--;
        if (stepCounter_ELEV < 0) stepCounter_ELEV = numSteps - 1;
    }  
   
    setOutput(stepCounter_ELEV, true);
}

 
void directionAZIM( int aDirection) {
    if(aDirection > 0) {
        stepCounter_AZIM++;
        if (stepCounter_AZIM >= numSteps) stepCounter_AZIM = 0; 
        }  else if(aDirection == 0) {
        // do nothing as well
        }
        else { // anticlockwise
           stepCounter_AZIM--;
           if (stepCounter_AZIM < 0) stepCounter_AZIM = numSteps - 1;
    }    
   
    setOutput(stepCounter_AZIM, false);
} 
 
void controlMotor(int elevation, int azimuth) {
  int i = 0;
  int j = 0;
  
  int eFinish = abs(elevation)*numSteps;
  int aFinish = abs(azimuth)*numSteps;
  
  while((i < eFinish) || (j < aFinish)) {
      if (i < eFinish) {
          directionELEV(elevation);
      }
      if (j < aFinish) {
          directionAZIM(azimuth);
      }
      delayMicroseconds(motorSpeed);
      i++;
      j++;
  } 
      
 /*     for(int i = 0; i < abs(elevation)*numSteps; i++) {
	    directionELEV(elevation);
            delayMicroseconds(motorSpeed);
    }
      for(int j = 0; j < abs(azimuth)*numSteps; j++) {
	    directionAZIM(azimuth);
            delayMicroseconds(motorSpeed);
      }*/
 }
