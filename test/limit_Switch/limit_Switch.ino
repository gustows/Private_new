#define lSwitch 8
//c to gnd NO to lsSwitch

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 8 as an input and enable the internal pull-up resistor
  pinMode(LED_BUILTIN, OUTPUT);

  /* */
  pinMode(lSwitch, INPUT_PULLUP);
}

bool chk_switch(char pin)
{
    return (digitalRead(pin) == HIGH)? true : false ;
}

void loop() {
  digitalWrite(LED_BUILTIN,chk_switch);
}
