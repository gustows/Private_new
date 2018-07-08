#include "_0header.h"

bool recieved_esp32()
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

bool wait_cmd(bool enable_gps)
{
    set_zero_motor();
    if(enable_gps == true) 
    {
      myPos.listen();
      recieve_GPS();
    }
    //from esp32
    mySerial.listen();
    while(mySerial.available())
    {
      if(recieved_esp32() == true) 
      {
        decode_cmd(0); // 0 is dummy
        return 1;
      }
      else 
        return 0;
    }
}


void smartDelay(unsigned long ms,bool enable_gps)
{
  unsigned long start = millis();
  do 
  { 
    //read received_esp32
    mySerial.listen();
    while(mySerial.available())
    {
      if(recieved_esp32() == true) 
      {
          decode_cmd(0); // 0 is dummy
      }
    }

    //read GPS
    myPos.listen();
    if(enable_gps == true){
      receive_GPS();
    }
  } while (millis() - start < ms);
}
