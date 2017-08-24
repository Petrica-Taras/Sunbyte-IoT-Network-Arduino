/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 */

// first motor/axis
const int axis1ControlPins = [9, 10, 11, 12];

const int motorPin1 = 9;    // 28BYJ48 In1
const int motorPin2 = 10;    // 28BYJ48 In2
const int motorPin3 = 11;   // 28BYJ48 In3
const int motorPin4 = 12;   // 28BYJ48 In4

// second motor/axis
const int axis1ControlPins = [8, 7, 6, 5];
const int motorPin5 = 8;    // 28BYJ48 In5
const int motorPin6 = 7;    // 28BYJ48 In6
const int motorPin7 = 6;    // 28BYJ48 In7
const int motorPin8 = 5;    // 28BYJ48 In8
                   
//definicion variables
int motorSpeed = 1000;   
int stepCounter_ELEV = 0;    
int stepCounter_AZIM = 0;
int stepsPerRev = 4096;  // 4076 pasos para una vuelta completa
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
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  pinMode(motorPin5, OUTPUT);
  pinMode(motorPin6, OUTPUT);
  pinMode(motorPin7, OUTPUT);
  pinMode(motorPin8, OUTPUT);
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
                //Serial.println("was here, if");
          }  else if(ch==',') {
               // Serial.println("was here, else if");
                first = false;
                strValue_ELEV[index] = 0;
                index = 0;
          }
          else {
                // Serial.println("was here, else");
                strValue_AZIM[index++] = ch;
          }
      }
      
      if(ch == '\n'){
            strValue_AZIM[index] = 0; 
            elevation = atoi(strValue_ELEV);
            azimuth = atoi(strValue_AZIM);
            
            Serial.println(elevation);
            Serial.println(azimuth);
            
            controlMotor(elevation, azimuth);	
            		
            strValue_ELEV[0] = 0;
            strValue_AZIM[0] = 0;
            
            //Serial.println(strValue_AZIM);
            //Serial.println(strValue_ELEV);
            

            index = 0;
            first = true;
          }
      }  
      stopArduino();
      
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
 
void setOutput(int input, boolean choose)
{
        //Serial.println("WAS here A");
  if(choose==true) {
      //Serial.println("WAS here B");
      digitalWrite(motorPin5, bitRead(stepsLookup[input], 0));
      digitalWrite(motorPin6, bitRead(stepsLookup[input], 1));
      digitalWrite(motorPin7, bitRead(stepsLookup[input], 2));
      digitalWrite(motorPin8, bitRead(stepsLookup[input], 3));
  } else {
       //Serial.println("WAS here C");
      digitalWrite(motorPin1, bitRead(stepsLookup[input], 0));
      digitalWrite(motorPin2, bitRead(stepsLookup[input], 1));
      digitalWrite(motorPin3, bitRead(stepsLookup[input], 2));
      digitalWrite(motorPin4, bitRead(stepsLookup[input], 3));
  }
}

void stopArduino() {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
}
