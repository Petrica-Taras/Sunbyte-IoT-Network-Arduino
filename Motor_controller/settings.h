/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Every setting can be found here
 * 
 * Keeps the following:
 * - motor pins
 */

#define ONPIN 3
#define DIRECTIONPIN 5
#define STEPSELECTPIN 8
int noOfMotorPins = 3;

/**
 * the order is ON pin, direction pin (1- clockwise) and step select (0 - preselected microstepping, 1 - full step)
 */
int motorAzimuthPins[3];
int motorElevationPins[] = {ONPIN, DIRECTIONPIN, STEPSELECTPIN};
int motorFocusingPins[3];

int microSDPins[] = {50, 51, 52}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!
