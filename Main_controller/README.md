# The Main Controller #

# Functions #
* energy management (shuts down stuff via relays) - some of the sensors (thermal for example should remain here)
* system status - collects data from the rest of the controller boards
* system recovery (i.e. reboots PC or Raspberry Pi units)
* communicates with the ground station for monitoring/diagnostics

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