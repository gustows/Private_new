#include "_0header.h"


SoftwareSerial mySerial(LLC_RX, LLC_TX);
String sss="",val=""; //allocate for message esp32

state rover_status = on_air;
MODE rover_mode = Landing; 

pin_motor motor[NMOT]; //here NMOT = 4 

TinyGPSPlus gps;
SoftwareSerial myPos(GPS_RX, GPS_TX);

coordinate goal;
goal.la = 00.0;
goal.lo = 00.0;
void setup()
{
    Serial.begin(9600);
    Serial.println("init nano!!");
    set_pin_motor(&motor[gearDrill],Dr_Din1,Dr_Din2,false,NULL); //drill
    set_pin_motor(&motor[gearCrane],Cr_Din1,Cr_Din2,true,Cr_Anin);    //Crane
    set_pin_motor(&motor[L_wheel],LW_Din1,LW_Din2,true,LW_Anin);
    set_pin_motor(&motor[R_wheel],RW_Din1,RW_Din2,true,RW_Anin);
    set_zero_motor();
    Serial.println("Set motor!!");
    
    myPos.begin(GPSBaud);
    Serial.println("Set GPS!!");

    pinMode(LLC_RX, INPUT);
    pinMode(LLC_TX, OUTPUT);    
    mySerial.begin(9600);
    Serial.println("Connect esp32!!");
    
    while(wait_cmd(0) == 0){ //รับสัญญานจาก esp32 =0 ยังไม่ได้
        
    } 

    //already
    
    Serial.println("received command");



}



void loop()
{
    bool recieved = recieved_esp32();
    
    if( recieved )
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
            if(_go_2Site_mode(s) != 1)
                return ERR_STS;
            break;
        case Drill_Process:
            if(_drill_process(s) != 1)
                return ERR_STS;
            break;
        default:
            return ERR_MOD;
            break;
    }
    return 1;
}
