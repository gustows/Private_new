//#include "newall_motor_editing.ino"

#define gearCrane 0
#define gearDrill 1

#define lSwitch_pin 12

typedef struct
{
  char in1;
  char in2;
  char pwm;
  bool _isPwm = false;
}pin_motor;


void set_pin_motor(pin_motor *M,char in1,char in2,bool isPwm,char pwm)
{
  M->in1 = in1;
  M->in2 = in2;
  M->_isPwm = isPwm;
  M->pwm = pwm;
  Serial.println("in1 : " +String(in1,DEC) + "in2 : " +String(in2,DEC)+ " pwm : " +String(pwm,DEC) );
  pinMode(M->in1, OUTPUT);
  pinMode(M->in2, OUTPUT);
  if( M->_isPwm == false ) return; //skip declare
  pinMode( M->pwm ,OUTPUT );
  
}

void drive_something(pin_motor M,short val)
{
  bool temp = (val < 0)? LOW:HIGH;
  if(val == 0) 
  {
    digitalWrite(M.in1, LOW);
    digitalWrite(M.in2, LOW);
    return;
  }
  digitalWrite(M.in1, temp);
  digitalWrite(M.in2, !temp);
  if(M._isPwm)
  analogWrite(M.pwm, val);
}

pin_motor motor[2];
//nano can pwm 3 5 6 9 10 11

bool chk_switch(char pin)
{
    return (digitalRead(pin) == HIGH)? true : false ;
}

void setup()
{
    Serial.begin(9600);
    set_pin_motor(&motor[gearDrill],A1,A2,false,NULL); //drill
    set_pin_motor(&motor[gearCrane],A3,A4,true,11);    //Crane
    pinMode(lSwitch_pin,INPUT_PULLUP);
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);
}

void loop()
{
    //test 1 Drill
    drive_something(motor[gearDrill],50);
    Serial.println(gearDrill);
    delay(500);
    drive_something(motor[gearDrill],0);
    delay(500);
    //test 2 Crane
    drive_something(motor[gearCrane],-50); //down
    Serial.println(gearCrane);
    delay(500);
    drive_something(motor[gearCrane],100); //up
    delay(500);
    drive_something(motor[gearCrane],0);
    delay(2000);
    //test 3 All with Switch
    short time = millis();
    do{
        drive_something(motor[gearCrane],-70);
        delay(50);
    }while(chk_switch(lSwitch_pin)==HIGH);
    short temp = millis()-time;
    Serial.println("Time : " + String(temp,DEC));
    drive_something(motor[gearCrane],0);
    delay(1000);
    
    drive_something(motor[gearCrane],140);
    delay(temp);

     drive_something(motor[gearCrane],0);
    delay(100000000);
}
