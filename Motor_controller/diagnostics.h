/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 */

/**
 * Controls a single motor/axis at a time. Useful for debugging on positioning (focusing
 * will require a different motor model most likely)
 * 
 * \param motor an array with the Arduino pins to control the motors (located in settings.h)
 * \param mDelay in microseconds, the delay between steps, indirectly sets speeds
 * \param mSteps the number of (micro)steps to rotate
 * \param rDirection sets the direction of rotation (true - clocwise, false - anticlockwise)
 * \param mMode sets microsteps or full step (true - default step, false - microstep)
 * 
 */
 void oneAxisOpenLoopMotor(int motor[], int mDelay, int mSteps, boolean rDirection, boolean mMode) {
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
      
    for(int i = 0; i < mSteps+1; i++){
      digitalWrite(motor[ONPIN], HIGH);
      delayMicroseconds(mDelay);//200
      digitalWrite(motor[ONPIN], LOW);
      delayMicroseconds(mDelay);//200
    }
  } 
