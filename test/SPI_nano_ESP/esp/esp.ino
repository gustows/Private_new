#include <HardwareSerial.h>
HardwareSerial Serial1(20);
#define SERIAL1_RXPIN 16 
#define SERIAL1_TXPIN 17
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SERIAL1_RXPIN,INPUT);
  pinMode(SERIAL1_TXPIN,OUTPUT);
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // pins 16 rx2, 17 tx2, 19200 bps, 8 bits no parity 1 stop bit
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial1.println("Hello,world");
  String dat="weiuhfuierpogkorigiueokgraiugaopkgoeagoeaf;";
  Serial.println(dat);
  delay(300);
}
