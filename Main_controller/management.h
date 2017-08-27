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

typedef enum {PC, ANDOR_CAMERA, R_PI, MAIN_CONTROLLER, TELESCOPE_HEATING, SENSORS_CONTROLLER, MOTOR_CONTROLLER, MOTOR_AZIMUTH, MOTOR_ELEVATION, MOTOR_FOCUSING} device;
typedef enum {OFFLINE, ONLINE} status;

status thermalSensorsStatus[] = {OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE}; //!< correlate with temperatureSensorsLabels[]
status powerSensorsStatus[] = {OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE}; //!< correlate with powerSensorsLabels[]
status lightSensorStatus = OFFLINE; 

typedef enum {ON, OFF} autonoumous; 



