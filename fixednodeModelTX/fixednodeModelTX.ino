#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
SoftwareSerial serial1(2, 3); // RX, TX
unsigned long start = millis();
uint8_t payload[] = { 0, 0 };
Tx16Request tx = Tx16Request(0x0000ffff, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

int pin5 = 0;

int statusLed = 11;
int errorLed = 13;

void setup() {
  Serial.begin(9600);
  serial1.begin(9600);
  xbee.setSerial(serial1);
}

void loop() {
   
    if (millis() - start > 15000) {
      // break down 10-bit reading into two bytes and place in payload
      pin5 = analogRead(5);
      /*
       * Split
       * Char1 = MyShort & 0xFF;
       * Char2 = MyShort >> 8;
       * merge
       * MyShort = (Char2 << 8) | Char1;
       */
      payload[0] = pin5 >> 8 & 0xff;
      payload[1] = pin5 & 0xff;
      
      xbee.send(tx);
    }
  
    // after sending a tx request, we expect a status response
    // wait up to 5 seconds for the status response
    if (xbee.readPacket(5000)) {
        // got a response!

        // should be a znet tx status              
      if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
         xbee.getResponse().getTxStatusResponse(txStatus);
        
         // get the delivery status, the fifth byte
           if (txStatus.getStatus() == SUCCESS) {
           }
        }      
    } 
    delay(1000);
}
