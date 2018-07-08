enum state {
  on_air=0,
  deploy,
  landing,
  wait_for_cut,
  wire_cutting,
  requests_gps,
  run_to_pos,
  on_position,
  wait_for_drill,
  Up_drill,
  Down_drill,
  read_probe,
  sending_probe,
  idle
};

enum MODE {
  Landing = 0xBA,GoingSite,Drilling,FINISHED
};

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//for connect esp32
#define LLC_TX 13
#define LLC_RX 12
SoftwareSerial mySerial(LLC_RX, LLC_TX);
String sss="",val="";

//GPS
#define GPS_TX 10
#define GPS_RX 11
#define GPSBaud = 9600
TinyGPSPlus gps;
SoftwareSerial myPos(RXPin, TXPin);
unsigned double  dist(double cur_lat,double cur_lon,double pos_lat,double pos_lon)
{
    return TinyGPSPlus::distanceBetween(cur_lat,cur_lon,pos_lat,pos_lon); //m unit
}

//Limit
#define L_switch 1

bool chk_switch(char pin)
{
    return (digitalRead(pin) == HIGH)? true : false ;
}

//Left_Wheel
#define LW_Din1 8
#define LW_Din2 9
#define LW_Anin A0
//Right_Wheel
#define RW_Din1 4
#define RW_Din2 5
#define RW_Anin A1
//Crane
#define Cr_Din1 A3
#define Cr_Din2 A4
#define Cr_Anin A2
//Drill
#define Dr_Din1 6
#define Dr_Din2 7
//for all motor
#define gearCrane 0
#define gearDrill 1
#define L_wheel 2
#define R_wheel 3

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

pin_motor motor[4];

//drive_something(motor[L_wheel],200);

void set_zero_motor()
{
  for(int iii =0 ;iii<4 ;iii++)
  {
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
    drive_something(motor[iii],0);
  }
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms,bool enable_gps)
{
  unsigned long start = millis();
  do 
  { 
    //read received_esp32
    mySerial.listen();
    while(mySerial.available())
    {
      char t = mySerial.read();
      sss += t;
    }
    if(sss.length() !=0 && sss[sss.length()-1]== ';' )
    {
      Serial.print(sss);
      val=sss; //copy value
      sss="";
    }

    //read GPS
    myPos.listen();
    if(enable_gps == true){
      while (myPos.available())
      gps.encode(myPos.read());
    }
  } while (millis() - start < ms);
}

state rover_status;
MODE rover_mode;

bool check_nano(bool isEnabled){
  if(isEnabled == false) return false;
   //GPS
  myPos.begin(GPSBaud);
  //motor
  set_pin_motor(&motor[gearDrill],Dr_Din1,Dr_Din2,false,NULL); //drill
  set_pin_motor(&motor[gearCrane],Cr_Din2,Cr_Din1,true,Cr_Anin);    //Crane
  set_pin_motor(&motor[L_wheel],LW_Din1,LW_Din2,true,LW_Anin);
  set_pin_motor(&motor[R_wheel],RW_Din1,RW_Din2,true,RW_Anin);
  set_zero_motor();
  pinMode(L_switch,INPUT_PULLUP); // lower limit switch
}


void setup() {
  rover_status = on_air;
  //for Serial monitor
  Serial.begin(9600);
  //for esp32
  mySerial.begin(9600);
  while(check_nano(false) == false) {} // wait for function set_pin  

}

/*
bool received_esp32()
{
   //recieve from esp32
   while(mySerial.available())
   {
    char t = mySerial.read();
    sss += t;
   }
  if(sss.length() !=0 && sss[sss.length()-1]== ';' )
  {
    Serial.print(sss);
    val=sss; //copy value
    sss="";
  }
  if(val.length()!=0) return 1;
  return 0;
}
*/

bool decode_cmd(int mode)
{
  
  switch (mode)
  { 
    //MODE L
    case Landing:
      /* code */
      break;
    case on_air:
      /* code */
      break;
    case deploy:
      /* code */
      break;
    case landing:
      /* code */
      break;
    case wait_for_cut:
      /* code */
      break;
    case wire_cutting:
      /* code */
      break;
    case wait_for_cut:
      /* code */
      break;

    //MODE G
    case GoingSite:
      /* code */
      break;
    case requests_gps:
      /* code */
      break;
    case run_to_pos:
      /* code */
      break;
    case on_position:
      /* code */
      break;
    
    //mode D
    case Drilling:
      /* code */
      break;
    case wait_for_drill:
      /* code */
      break;
    case Up_drill:
      /* code */
      break;
    case Down_drill:
      /* code */
      break;
    case read_probe:
      /* code */
      break;
    case sending_probe:
      /* code */
      break;

    //SUCCESS
    case FINISHED:
      /* code */
      break;
    case idle:
      /* code */
      break;

    default: return 0;
  }
}

void loop() {
  
  


}  