
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RXPin, TXPin);
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
 while(ss.available()){
  Serial.write(ss.read());
 }
}
