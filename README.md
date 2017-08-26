# Sunbyte-IoT-Network-Arduino
This project consists of a small IoT network composed of 3 EtherMega (Arduino Mega 2560) controllers to read sensors and control 3 stepper motors.
The controllers are connected on an Ethernet network via a switch. The overall goal is to be able to position a telescope (tracking algorithm is
implemented elsewhere) and to read sensors. This is done autonomously but it is possible to take over from the ground station at some point. 
This is part of a larger project (Project Sunbyte at University of Sheffield).

# Structure #
The IoT network is composed of three Ethermega controllers:
* the main controller: does energy management, diagnostics/monitoring, communication with the ground station
* the sensors controller: keeps track of all sensors
* the motors controller: deals with the motors. Focusing motor should also go here (having a separate controller for it is a bit late now in the project)

All controllers have Ethernet ports and allows communication for manual control or diagnostics purposes. 
The network is part of a larger setup, powered by batteries, hence the need for energy management. 

# Technologies used #
* C (for Arduino controllers)
* Doxygen (documentation)

# Dependencies #
All extra libraries not shipped usually with Arduino IDE are detailed here (along with their place of provenience).
Please see the README.md for each controller to pinpoint where each library goes:
* Adafruit_INA: https://github.com/adafruit/Adafruit_INA219/archive/master.zip
* OneWire: https://github.com/PaulStoffregen/OneWire/archive/master.zip
* DallasTemp: https://github.com/adafruit/MAX31850_DallasTemp/archive/master.zip

# Recommended practices #
When working with the code in this directory and you are using another Arduino type (instead of EtherMegas)
you should make a new branch (say Leonardo if you are using a Leonardo). By no means modify the pin settings and such in the
settings.h header in the master branch so you can accomodate your particular Arduino, that would be retarded. Speaking of Leonardo, 
it uses a different (newer) Ethernet library, so when merging back into master only relevant bits will be kept. 

# About Project Sunbyte #
Project Sunbyte is a student project at the University of Sheffield composed of undergraduates, PhD Students
and academics from all over UK. Its purpose is to sent a solar telescope into atmosphere using a balloon.
It has been accepted for the REXUS/BEXUS campaign 2016 - 2017 (cycle 10). For a full list of partners and sponsors
please visit http://sunbyte.group.shef.ac.uk/. 

