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

int motorAzimuthPins[4];
int motorElevationPins[4];
int motorFocusingPins[4];

int microSDPins[] = {50, 51, 52}; //!< for EtherMega/Arduino Mega only - change controller, change these pins!
