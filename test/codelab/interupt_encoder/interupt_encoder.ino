#define ITR_pin 3
#define deg_rnd 360/20 //18 deg per slot 
#define to_rpm 60.0/360.0
#define interval 100 //millis
int chk_wheel = 0;  
short tdel_wheel = 0;
volatile short rpm =0 ;
unsigned long last_m=0;

void set_val_interupt()
{
    last_m = millis();
    chk_wheel =0;

}
void setup()
{
    Serial.begin(9600);   
    attachInterrupt(ITR_pin, pin_ISR, CHANGE );
    set_val_interupt();
}
void loop()
{
    Serial.println(chk_wheel);
    int t= millis() - last_m;
    if(t > interval)
    {
        double w = (double)chk_wheel*deg_rnd/((double)tdel_wheel/1000.0)  ;
        rpm = w*to_rpm;
        set_val_interupt();
    }
}

void pin_ISR() {
    chk_wheel++;
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(100);
 /*   tdel_wheel = millis()-last_m; 
    if( tdel_wheel > interval )
    {
        last_m = millis();
        double w = (double)chk_wheel*deg_rnd/((double)tdel_wheel/1000.0)  ;
        rpm = w*to_rpm;
        chk_wheel=0;
    }
    */
}
