#define mot 2
void setup() {
  // put your setup code here, to run once:
 pinMode(mot, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(mot,-255); 
  
}
