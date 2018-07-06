#define LWHEEL 0
#define RWHEEL 1
#define gearCrane 2
#define gearDrill 3
//nano can pwm 3 5 6 9 10 11
typedef struct
{
  char in1;
  char in2;
  char pwm;
  bool _isPwm = false;
}pin_motor;

pin_motor motor[4];

void set_pin_motor(pin_motor M)
{
  pinMode(M.in1, OUTPUT);
  pinMode(M.in2, OUTPUT);
  if( M._isPwm  ) return; //skip declare
  pinMode( M.pwm ,OUTPUT );
}

void drive_something(pin_motor M,short val)
{
  bool temp = (val < 0)? LOW:HIGH;
  digitalWrite(M.in1, temp);
  digitalWrite(M.in2, !temp);
  if(M._isPwm)
  analogWrite(M.pwm, val);

}

void setup()
{
  motor[LWHEEL]._isPwm = true;
  motor[LWHEEL].pwm = 3 ;
  motor[LWHEEL].in1 = 2 ;
  motor[LWHEEL].in2 = 1 ;

  motor[RWHEEL]._isPwm = true;
  motor[RWHEEL].pwm = 6;
  motor[RWHEEL].in1 = 5;
  motor[RWHEEL].in2 = 4;

  motor[gearCrane]._isPwm = true;
  motor[gearCrane].pwm = 9;
  motor[gearCrane].in1 = 8;
  motor[gearCrane].in2 = 7;

  motor[gearDrill]._isPwm = false;
  motor[gearDrill].in1 = 11;
  motor[gearDrill].in2 = 10;
  
  set_pin_motor(motor[LWHEEL]);
  set_pin_motor(motor[RWHEEL]);
  set_pin_motor(motor[gearCrane]);
  set_pin_motor(motor[gearDrill]);
}

void loop() {
  //walk
  drive_something(motor[LWHEEL],100);
  drive_something(motor[RWHEEL],100);
  delay(1500);
  drive_something(motor[LWHEEL],0);
  drive_something(motor[RWHEEL],0);
  delay(200);
  //gearDrill open
  drive_something(motor[gearDrill],200);
  //gearCrane
  for(char i = 0 ;i < 5 ;i++)
  {
    drive_something(motor[gearCrane],70);
    delay(1500);
    drive_something(motor[gearCrane],-70);
    delay(1500);
  }
  drive_something(motor[gearCrane],-100);
  delay(1000);
  drive_something(motor[gearDrill],0);
  drive_something(motor[gearCrane],0);
  delay(40000000000);
}
