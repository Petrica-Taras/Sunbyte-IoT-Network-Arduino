/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 */

void initMotors() {
    for(int i = 0; i < noOfPhases; i++) {
      pinMode(axis1ControlPins[i], OUTPUT);
      pinMode(axis2ControlPins[i], OUTPUT);
    }  
}

 void cutMotorsPower() {
    for(int i = 0; i < noOfPhases; i++) {
      digitalWrite(axis1ControlPins[i], LOW);
      digitalWrite(axis2ControlPins[i], LOW);
    }
}

void setOutput(int input, boolean choose)
{
  for(int i = 0; i < noOfPhases; i++) {
      if(choose==true) {
          digitalWrite(axis2ControlPins[i], bitRead(stepsLookup[input], i));
      } else {
          digitalWrite(axis1ControlPins[i], bitRead(stepsLookup[input], i));
      }
  }
}
