#define mot 34


void setup() {
  // put your setup code here, to run once:
  ledcAttachPin(mot, 1);
  ledcSetup(1, 8000, 8);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(1, 255);
}
