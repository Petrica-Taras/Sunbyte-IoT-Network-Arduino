/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Every setting can be found here and variables defined here are visible to the rest of the program
 * 
 * Keeps the following:
 * - all sorts of pins (relays, sensors)
 * - IP addresses (if applicable)
 * - decision criteria (based on temperature
 * and power with the mention that temperature
 * ones have priority to avoid damaging the 
 * equipment)
 * - number of sensors for each quantity
 * - defines the status variables for each device
 */

const byte noOfTemperatureSensors = 7;
const byte noOfPowerSensors = 4;

const byte noOfRelays = 7; 

/*
 * local 
 */
String name = "Main Controller"; //!< controller label for identification 
byte ip[] = { 169, 254, 131, 159 }; //!< ip in lan (of this device)
byte gateway[] = { 169, 254, 131, 160 }; //!< ground station
byte subnet[] = { 255, 255, 0, 0 }; //subnet mask

static uint8_t MAC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

String temperatureSensorsLabels[] = {"Motor Azimuth", "Motor Elevation", "Raspberry Pi", "PC", "Camera", "Telescope", "Outside"}; //!< everything we measure
String powerSensorsLabels[] = {"Mains", "PC", "Telescope", "Camera"}; //!< current/voltage sensors - if you want more then 4 then buy TCA9548A (I2C multiplexer)

String relayLabels[] = {"Motors", "PC", "Camera", "Raspberry Pi", "Telescope", "Sensor Controller", "Motor Controller"};

String logFile = "log.txt"; 

int relayPins[] = {22, 23, 24, 25, 26, 27, 28};
int microSDPins[] = {50, 51, 52, 53}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!

int temperatureSensorPin = 2; //!< because the thermocouples we use can be put on the same dataline

double temperaturesThresholds[] = {65, 70, 55}; //!< Motor, PC, Raspberry Pi temperature thresholds
double powerThresholds[] = {40, 60, 60, 10, 40, 2, 2}; //!< Motors, PC, Camera, Raspberry Pi, telescope, sensors and motors (combined) power thresholds

long kickIn = 60L*1*1000; //!< time to reach the proper altitude and hence start the rest of experiment (until now only the main controller is online)
long kickOut = 100L*1*1000; //! time to safely shutdown the experiment just before battery cutoff (descent phase)

long temperatureSamplingTime = 10000L; //!< sample the temperature every 10 seconds 
long powerSamplingTime = 10000L; //!< sample the current/voltage every 10 seconds 

/**
 * Management related functionality. Various flags and enumerations to be used in decision flow structures
 */
typedef enum {PC, ANDOR_CAMERA, R_PI, MAIN_CONTROLLER, TELESCOPE_HEATING, SENSORS_CONTROLLER, MOTOR_CONTROLLER, MOTOR_AZIMUTH, MOTOR_ELEVATION, MOTOR_FOCUSING} device;
typedef enum {OFFLINE, ONLINE} status;
typedef enum {ON, OFF} is; 

status thermalSensorsStatus[] = {OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE}; //!< correlate with temperatureSensorsLabels[]
status powerSensorsStatus[] = {OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE}; //!< correlate with powerSensorsLabels[]
status lightSensorStatus = OFFLINE; 

/**
 * The status of available devices and boards. Should be correlated with the device enumeration type above or the deviceLabels string. 
 * The main controller (index 3/position 4) is always ONLINE because running this code assumes it implicitly. 
 */
status devices[] = {OFFLINE, OFFLINE, OFFLINE, ONLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE}; 

String deviceLabels[] = {"PC", "Andor Camera", "Raspberry Pi", "Main Controller", "Telescope Heating", "Sensor Controller", "Motor Controller", "Motor Azimuth", "Motor Elevation", "Motor Focusing"};
int noOfDevices = 10;

/**
 * Ethernet port settings (or placeholders for later use)
 */
#define I2C_ADDRESS 0x50
int serverPort = 23;
String ethernetNetworkLabels[] = {"Main Controller", "Ground Station", "PC", "Raspberry Pi", "Sensor Controller", "Motor Controller"};
status ethernetNetworkDevices[] = {OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE, OFFLINE};
byte ethernetNetworkIPs[][4] = {{ 169, 254, 131, 159 }, { 169, 254, 131, 160 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 169, 254, 131, 162 }}; 
