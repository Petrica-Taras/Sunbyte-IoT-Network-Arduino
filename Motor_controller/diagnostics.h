/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

/**
 * Controls a single motor/axis at a time
 * 
 * \param motor an array with the Arduino pins to control the motors (located in settings.h)
 * \param mDelay in microseconds, the delay between steps, indirectly sets speeds
 * \param mSteps the number of (micro)steps to rotate
 * \param rDirection sets the direction of rotation (true - clocwise, false - anticlockwise)
 * \param mMode sets microsteps or full step (true - default step, false - microstep)
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
