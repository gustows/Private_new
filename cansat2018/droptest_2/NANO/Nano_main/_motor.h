
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
//  Serial.println("in1 : " +String(in1,DEC) + "in2 : " +String(in2,DEC)+ " pwm : " +String(pwm,DEC) );
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

void set_zero_motor()
{
  for(int iii =0 ;iii<NMOT ;iii++)
  {
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
  }
}

bool chk_switch(char pin)
{
    return (digitalRead(pin) == HIGH)? true : false ;
}