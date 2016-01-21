#include <XBee.h>
#include <SoftwareSerial.h>
#include "AddressBook.h"
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial serial1(2, 3); // RX, TX

XBee xbee=XBee();
XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
AddressBook book = AddressBook(3);
uint8_t option = 0;
uint8_t data = 0;
uint8_t rssi = 0;
uint8_t dataLength = 0;
uint16_t addresses;
int pos = 0;

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
        //Serial.println("16");
        xbee.getResponse().getRx16Response(rx16);
        option = rx16.getOption();
        data = rx16.getData(0);
        dataLength = rx16.getDataLength();
        book.insert(rx16.getRemoteAddress16(),rx16.getRssi());
        rssi = rx16.getRssi();
        //addresses = rx16.getRemoteAddress16();
        
        Serial.print("datalenght: ");Serial.println(dataLength);
        Serial.print("data: ");Serial.println(data);
        Serial.print("option: ");Serial.println(option);
        Serial.print("Reads: ");
        Serial.print("Remote aderess: ");Serial.println(addresses);
        for (int i =0 ; i<=dataLength-1;i++) 
          {
            uint8_t temp=rx16.getData(i);
            Serial.print(temp);
            Serial.print(" ");
          }
        Serial.print("\nFrom:"); Serial.print(rx16.getRemoteAddress16());
        Serial.println("");
        Serial.println(rssi);
      } 
      else 
      {
        Serial.println("64");
        xbee.getResponse().getRx64Response(rx64);
        //option = rx64.getOption();
        //data = rx64.getData(0);
        rssi = rx64.getRssi();
        Serial.println(rssi);
      }
    }
  }
  
}
