/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

 void oneMotor(int motor[], int mDelay, int mSteps, boolean rDirection, boolean mMode) {
    for(counter = 1; counter<mSteps+1; counter++){
      digitalWrite(motor[ONPIN], HIGH);
      if(rDirection==true){
        digitalWrite(motor[DIRECTIONPIN], HIGH);//cw
      } else{
        digitalWrite(motor[DIRECTIONPIN], LOW);//ccw
      }
      if(mMode==true){
        digitalWrite(motor[STEPSELECTPIN], HIGH);//d
      } else{
        digitalWrite(motor[STEPSELECTPIN], LOW);//ms
      }
      delayMicroseconds(mDelay);//200
      digitalWrite(motor[ONPIN], LOW);
      delayMicroseconds(mDelay);//200
    }
  } 
