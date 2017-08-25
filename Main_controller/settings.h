/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief Every setting can be found here
 * 
 * Keeps the following:
 * - all sorts of pins (relays, sensors)
 * - IP addresses (if applicable)
 * - decision criteria (based on temperature
 * and power with the mention that temperature
 * ones have priority to avoid damaging the 
 * equipment)
 * - number of sensors for each quantity
 */

const byte noOfTemperatureSensors = 3;
const byte noOfCurrentSensors = 3;
const byte noOfVoltageSensors = 3;
const byte noOfRelays = 4; 

String temperatureSensorsLabels[] = {"Motor", "PC", "Raspberry PI"}; //!< size needs to be correlated with no of temperature sensors available
String currentSensorsLabels[] = {"Motor", "PC", "Raspberry PI"}; //!< size needs to be correlated with no of current sensors available
String voltageSensorsLabels[] = {"Motor", "PC", "Raspberry PI"}; //!< size needs to be correlated with no of voltage sensors available

int relayPins[] = {22, 23, 24, 25};
int currentSensorsPins[] = {A3, A4, A5};
int voltageSensorsPins[noOfVoltageSensors]; //!< not available for now
int temperatureSensorsPins[] = {A0, A1, A2};

double temperaturesThresholds[] = {65, 70, 55}; //!< Motor, PC, Raspberry Pi temperature thresholds
double powerThresholds[] = {8, 10, 55}; //!< Motor, PC, Raspberry Pi power thresholds

long kickIn = 60L*1*1000; //!< time to reach vacuum and hence start testing (so far only the main controller is online)
long temperatureSamplingTime = 30000L; //!< 
int microSDPins[] = {50, 51, 52}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!
