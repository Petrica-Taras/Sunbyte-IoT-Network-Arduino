/**
 * \author Petrica Taras
 * \author Fernando Alvarez
 * 
 * \brief mostly Ethernet functionality
 * 
 * 
 */

#include <SPI.h>
#include <Ethernet.h>

#define HANDSHAKE 'a'

/**
 * Helper to retrieve the MAC address
 * https://www.freetronics.com.au/pages/setting-the-mac-address-using-the-mcp-24aa025e48#.WaMwK9GQxjG
 */
byte readRegister(byte r)
{
  unsigned char v;
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(r);  // Register to read
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, 1); // Read a byte
  while(!Wire.available())
  {
    // Wait
  }
  v = Wire.read();
  return v;
} 

/**
 * populate the MAC array in settins.h
 * https://www.freetronics.com.au/pages/setting-the-mac-address-using-the-mcp-24aa025e48#.WaMwK9GQxjG
 */

void getMACAddress() {
  MAC[0] = readRegister(0xFA);
  MAC[1] = readRegister(0xFB);
  MAC[2] = readRegister(0xFC);
  MAC[3] = readRegister(0xFD);
  MAC[4] = readRegister(0xFE);
  MAC[5] = readRegister(0xFF);
}

/**
 * Needs to be server & client 
 */
EthernetClient client; 
EthernetServer server(serverPort);


/*
 * Check another device on the network (i.e. connection status). Needs ethernetNetworkDevices[] in 
 * settings.h as it will set items in it. Also it requires ethernetNetworkIPs[] and ethernetNetworkLabels[]
 * in the same header file.  
 * 
 * \returns true if that device is online and false otherwise
 */

boolean checkConnection(int deviceNo) {
  if(ethernetNetworkIPs[deviceNo][0] || ethernetNetworkIPs[deviceNo][1] || ethernetNetworkIPs[deviceNo][2] || ethernetNetworkIPs[deviceNo][3]) { 
    client.connect(ethernetNetworkIPs[deviceNo], 23);
    if(client.connected()) {
      ethernetNetworkDevices[deviceNo] = ONLINE;
      devices[deviceNo] = ONLINE; 
      // digitalWrite(13, HIGH);
      // client.println("Yaaaay!");
      client.stop(); 
      return true;
    }
  }
  else { //!< make sure is set OFFLINE
    ethernetNetworkDevices[deviceNo] = OFFLINE;
    return false;
  }
}
 
