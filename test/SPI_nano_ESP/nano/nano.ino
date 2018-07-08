#include <SoftwareSerial.h>
#define rxPin 3
#define txPin 4
SoftwareSerial mySerial(rxPin, txPin);
String sss="",val="";
void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
   while(mySerial.available())
   {
    char t = mySerial.read();
//    if( t== ';') break;
    sss += t;
   }
  if(sss.length() !=0 && sss[sss.length()-1]== ';' )
  {
    Serial.print(sss);
    val=sss; //copy value
    sss="";
  }
   Serial.println("val = "+ val);
    if(val.length()!=0) 
    {
      mySerial.println("555555555555555555555555;");
      delay(100000000000);
    }
  Serial.println("sssval = "+ val);
}  
/*
char tmp = '\0';
    String msg = "";
    while(mySerial.available()){
      while(tmp != '\n'){
        
      tmp = (char)mySerial.read();
       msg +=tmp;
       }
     
    }
    msg+= "\0";
    Serial.println(msg);
    msg="";

 */
