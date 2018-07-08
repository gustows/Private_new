#define senB 11
#define sin1 A1
#define sin2 A2
#define sin3 A3
#define sin4 A4
void setup() {
  // put your setup code here, to run once:
 pinMode(A1, OUTPUT);
 pinMode(A2, OUTPUT);
 pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(senB,0);
}
