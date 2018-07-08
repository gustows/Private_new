#define MShip 0xBC
#define Rover 0xBA
#define GStation 0xC0

#include <SPI.h>              // include libraries
#include <LoRa.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)

const int csPin = SS;          // LoRa radio chip select
const int resetPin = RST;       // LoRa radio reset
const int irqPin = DI0;         // change for your board; must be a hardware interrupt pin

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = GStation;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 500;          // interval between sends
String lastmsg ="";
byte lastsend = 0xFF;
enum state{ide , separated, landing , cut_rope , rdy }; 
enum state rover;
byte recipient;
byte sender;
byte l_relay;
byte incomingMsgId;
String dcode_status(int rover)
{
// read state from lora to rover
  
  if( rover == ide)
  return "idle" ;
  if( rover == separated)
  return  "separated"; 
  if( rover == landing)
   return  "landing"; 
  if( rover == cut_rope)
   return  "cut rope"; 
  if( rover == rdy)
   return "ready";
  
}

void setup() {
  Serial.begin(115200);                   // initialize serial
//  while (!Serial);

  Serial.println("Ground Station");

  // override the default CS, reset, and IRQ pins (optional)
  //SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin
  LoRa.setTxPower(15);
  
   while (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("Connecting . . .");
    delay(100);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
//   Serial.println("*");
   onReceive(LoRa.parsePacket());
}
/*
void sendMessage(byte sender,String outgoing,byte target,byte last_relay) 
{
  LoRa.beginPacket();                   // start packet
  LoRa.write(target);              // add destination address
  LoRa.write(sender);             // add sender address
  LoRa.write(last_relay);                 // add last relay address
  LoRa.write(msgCount);                 // add message ID
  LoRa.print(outgoing);                 // add code
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID}
}
*/
void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}
void relay(String outgoing){
  LoRa.beginPacket();                   // start packet
  LoRa.write(recipient);                // add destination address
  LoRa.write(sender);                   // add real sender address
  LoRa.write(localAddress);             // add relay add
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;  
}
void onReceive(int packetSize) {
 if (packetSize == 0) return;          
 // if there's no packet, return
  recipient = LoRa.read();          // recipient address
  sender = LoRa.read();            // sender address
  l_relay = LoRa.read();            // sender address
  incomingMsgId = LoRa.read();     // incoming msg ID
  String payload ="";
  //for (int i = 4; i < packetSize; i++) { payload += (char) LoRa.read(); }
  while(LoRa.available()){
    payload += (char)LoRa.read();
  }
  Serial.println(payload);
  if (sender == localAddress ) return;
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("Relay message :  " + payload);
    msgCount = incomingMsgId;
    relay(payload);
    return;                             // skip rest of function
  }
  
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("last relay: 0x" + String(l_relay, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message: " + payload);
  Serial.println(payload.length());
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  
}
