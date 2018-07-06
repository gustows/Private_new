#define SWITCH_PIN 2
#define outpin 13 
bool b=LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH_PIN,INPUT);
  pinMode(outpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  b = digitalRead(SWITCH_PIN);
  digitalWrite(outpin, b ) ;
}
