#include "config.h"
void setup()
{
    goal.la = 00.0;
    goal.lo = 00.0;
    Serial.begin(9600);
    Serial.println("init nano!!");
    set_pin_motor(&motor[gearDrill],Dr_Din1,Dr_Din2,false,NULL); //drill
    set_pin_motor(&motor[gearCrane],Cr_Din1,Cr_Din2,true,Cr_Anin);    //Crane
    set_pin_motor(&motor[IL_wheel],LW_Din1,LW_Din2,true,LW_Anin);
    set_pin_motor(&motor[IR_wheel],RW_Din1,RW_Din2,true,RW_Anin);
    
    drive_something(motor[gearDrill],0);
    drive_something(motor[gearCrane],0);
    drive_something(motor[IL_wheel],0);
    drive_something(motor[IR_wheel],0);
    Serial.println("Set motor!!");
    
    myPos.begin(9600);
    Serial.println("Set GPS!!");

    pinMode(LLC_RX, INPUT);
    pinMode(LLC_TX, OUTPUT);    
    mySerial.begin(9600);
    Serial.println("Connect esp32!!");
    
    Serial.print("wait command : ");
    while(wait_cmd(0) == 0){ //รับสัญญานจาก esp32 =0 ยังไม่ได้
        
    } 
    
    //already
    
    Serial.println("received " + val);
    val="";


}



void loop()
{
    
    bool recieved = recieved_esp32();
    
    if( 1)
    {
        
        //dcode //have to change state
        if(rover_status == requests_gps)
        {
            while(recieve_GPS()==0) {}//wait until recieved
            //send GPS to esp32
        }
    }
    Serial.println( do_mode(rover_mode,rover_status));

}

bool do_mode(int m,int s)
{
    
    switch (m)
    {
        case FINISHED:
            if(_finish_mode(s) != 1)
                return ERR_STS;
            break;
        case Landing:
            if(_landingmode(s) != 1)
                return ERR_STS;
            break;
        case GoingSite:
            if(_go_2Site_mode(s,motor[IL_wheel],motor[IR_wheel],goal) != 1)
                return ERR_STS;
            break;
        case Drill_Process:
            if(_drill_process(s,motor[gearDrill],motor[gearCrane],motor[IL_wheel],motor[IR_wheel]) != 1)
                return ERR_STS;
            break;
        default:
            return ERR_MOD;
            break;
    }
    return 1;
}
bool chkStart=false;

bool recieved_esp32()
{
   //recieve from esp32
   while(mySerial.isListening()!= 1)
   mySerial.listen();
   while(mySerial.available())
   {
    
    char t = mySerial.read();
    if(t!='#' && chkStart ==false)
    {
      continue;
    }
    else if(t== '#')
    {
      sss += t;
      chkStart=true;  
    }
    
   }
  if(sss.length() !=0 && sss[sss.length()-1]== ';' )
  {
    Serial.print(sss);
    val=sss; //copy value
    sss="";
  }
  if(val.length()!=0) 
  {
    //  Serial.println("val = "+ val);
      
      segment(val);
      chkStart = false;
      return 1;
  }
  return 0;
}

bool wait_cmd(bool enable_gps)
{   
  val="";
   Serial.println("wait cmd");
    if(enable_gps == true) 
    {
      Serial.println("read GPS");
      myPos.listen();
      recieve_GPS();
    }
    //from esp32
    mySerial.listen();
    while(mySerial.available())
    {
      return recieved_esp32();
    }
}

bool recieve_GPS()
{
    while (myPos.available())
      gps_tn.encode(myPos.read());
    if(gps_tn.location.isValid()==true)
    return 1;
    else return 0;
}


void steeringStart()
{
  //digitalWrite(STB, HIGH);
  
}
void steeringStop()
{
  //digitalWrite(STB, LOW);
  drive_something(M[IR_wheel],0;
  drive_something(M[IL_wheel],0);
}

void steeringStraight()
{
  drive_something(M[IR_wheel],Full_pipe);
  drive_something(M[IL_wheel],Full_pipe);
}
void steeringRight()
{
  drive_something(M[IR_wheel],Full_pipe);
  drive_something(M[IL_wheel],Full_pipe/2);
}

void steeringLeft()
{
  drive_something(M[IR_wheel],Full_pipe/2);
  drive_something(M[IL_wheel],Full_pipe);
}


