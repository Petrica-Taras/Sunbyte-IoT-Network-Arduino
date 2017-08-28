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


