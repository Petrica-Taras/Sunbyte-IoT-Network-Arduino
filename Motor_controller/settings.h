/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Every setting can be found here
 * 
 * Keeps the following:
 * - motor pins
 */

#define ONPIN 0
#define DIRECTIONPIN 1
#define STEPSELECTPIN 2

#define AZIMUTH 0
#define ELEVATION 1
#define FOCUS 2

int noOfMotorPins = 3; //!< for now

/**
 * the order is ON pin, direction pin (1- clockwise) and step select (0 - preselected microstepping, 1 - full step)
 */
int motorPins[][3] = {{3, 5, 8}, {4, 6, 7}};

int motorFocusingPins[3];

int microSDPins[] = {50, 51, 52}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!

const byte noOfPowerSensors = 3; //!< each motor has its own (order is defined above)
const byte noOf9DOFSensors = 2;

String powerSensorsLabels[] = {"Azimuth", "Elevation", "Focus"}; //!< current/voltage sensors
String motorsLabels[] = {"Azimuth", "Elevation", "Focus"};

String s9DOFSensorsLabels[] = {"Telescope", "Outside"};


