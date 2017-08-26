# The Main Controller #

# Functions #
* energy management (shuts down stuff via relays) - some of the sensors (thermal for example should remain here)
because the system makes decisions based on them
* system status - collects data from the rest of the controller boards (i.e. who is online)
* system recovery (i.e. reboots PC or Raspberry Pi units)
* keeps an eye on the batteries (a current/voltage sensor for each battery should be used here)
* communicates with the ground station for monitoring/diagnostics
* keeps logs on micro SD card

# Controlled devices (via relays) #
The power hogs are always relay controlled for obvious reasons. The Arduino boards as well, to ensure the possibility 
of recovery via restart (if they crash).
# Implemented Strategies #
Several operation modes are possible, these are defined/described further. Each mode specifies the relay status
## Ascending mode ##
While ascending, only a minimal set of components will be kept online (the main controller keeping an eye on temperatures
of camera, telescope and so on and starting those devices if their value drops too much)
## In flight mode, camera is not facing the Sun but outside deadzone ##
The camera needs to obviously be shut down
## In flight mode, camera is not facing the Sun but inside deadzone ##
The camera needs to obviously be shut down
## In flight mode, facing the Sun
This is the most critical moment, probably the telescope heating may need to be cut,
this is the only power that can be cut off. 

#Sequence of operation
During ascent phase, only the main controller is online, keeping an eye on the temperature
values of critical components. We don't expect to use any battery power until we actually reach the 
desired altitude level. 
During flight, the camera, telescope and possibly PC (to be determined after testing) might need to be 
powered off for a while to preserve battery. This is implemented via relays, this controller being the 
only one controlling relays. 

# Testing
All results from testing (and possible improvements should go here).

# Sensors
* Thermocouples + their amplifiers (MAX31850K) - https://www.adafruit.com/product/270 and https://www.adafruit.com/product/1727
* Current/Voltage sensors (INA219) - https://www.adafruit.com/product/904

