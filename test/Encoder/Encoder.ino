#define EncoderA 5
#define deg_rnd 18.0  //360/20 //18 deg per slot 
#define to_rpm 1/6.0//60.0/360.0

bool last_val=0;
unsigned long last_m=0;
int chk,y=0;
double sum;
void setup()
{
    Serial.begin(9600);   
    pinMode(EncoderA,INPUT_PULLUP);
    chk=0;
    last_val =digitalRead(EncoderA);
    
}
void loop()
{
  /*
    bool temp = (analogRead(EncoderA) > 500)? HIGH:LOW;
    if(temp != last_val )
    {
      double delt =( millis()-last_m)/1000.0;
      
      double v = 18.0 /delt * to_rpm;
      Serial.println(v);
      last_m = millis();
      last_val = temp;
    }
   */
  if(y == 5)
  {
    y=0;
    double rpm = sum*to_rpm/5;
    Serial.println("average_ = " + String(rpm));
    sum=0;
  }
   char t=0;
   chk=0;
    last_m = millis();
    do{
      bool temp = digitalRead(EncoderA);
      if(temp!=last_val)
      {
         chk ++;
         last_val = temp;
      }
    t= millis() - last_m;
    }while(  t < 100 );
    
    double w = (double)chk*18.0/((double)t/1000.0) ; ;
    sum += w;
    y++;
// Serial.println(rpm);
   last_m =millis();
}

//    bool temp = digitalRead(EncoderA);
//    if(temp != last_val )
//    {
//      double delt =( millis()-last_m)/1000.0;
//      
//      double v = 18.0 /delt * to_rpm;
//      Serial.println(v);
//      last_m = millis();
//      last_val = temp;

/*
 
    bool val = map(analogRead(EncoderA),0, 1022, 0, 1);
   // Serial.println(val);
    if(last_val != val)
    {
      s++;
      last_val=!last_val;
    }
        
    if(s == 2) {
        s=0;
        Serial.println(double(to_rpm*(1000*deg_rnd)/(millis()-last_m)));
        last_m = millis();    
    }
    //delay(50);
 */
