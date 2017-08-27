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
 */

const byte noOf9DOFSensors = 2;
const byte noOfLightSensors = 1;
const byte noOfVibrationSensions = 1;

String s9DOFSensorsLabels[] = {"Telescope", "Outside"}; //!< size needs to be correlated with no of temperature sensors available

int microSDPins[] = {50, 51, 52}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!
