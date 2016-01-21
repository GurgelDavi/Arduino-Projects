#include <XBee.h>
#include <SoftwareSerial.h>
 
 
// XBee's DOUT (TX) is connected to pin 8 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 9 (Arduino's Software TX)
SoftwareSerial serial1(8, 9); // RX, TX
 
XBee xbee=XBee();
XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
 
uint8_t option = 0;
uint8_t data = 0;
uint8_t rssi = 0;
 
void setup() 
{
  Serial.begin(9600);
  serial1.begin(9600);
  xbee.setSerial(serial1);
}
 
void loop() 
{
  xbee.readPacket(100);
  if (xbee.getResponse().isAvailable())
  {
    Serial.println("available");
    if(xbee.getResponse().getApiId() == RX_64_RESPONSE || xbee.getResponse().getApiId() == RX_16_RESPONSE)
    { 
      Serial.println("16");
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) 
      {
        Serial.println("16");
        xbee.getResponse().getRx16Response(rx16);
        rssi = rx16.getRssi();
        Serial.println(rssi);
      } 
      else 
      {
        Serial.println("64");
        xbee.getResponse().getRx64Response(rx64);
        rssi = rx64.getRssi();
        Serial.println(rssi);
      }
    }
  }
}
