#include "_0header.h"

void _drill_process(int status)
{
    switch (status)
    {
        case wait_for_drill:
            set_zero_motor();
            break;
        case drilling
            drive_drill(0);
            break;     
        case read_probe:
            set_zero_motor();
            break;
        case sending_probe:
            set_zero_motor();
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}

bool drive_drill(char up)
{
        
        Serial.println("drill crane down");
        unsigned long t = millis();
        drive_something(motor[gearDrill],250);
        drive_something(motor[gearCrane],50);
        
        while(chk_switch(L_switch)==HIGH) { delay(50); } //HIGH is not yet pressed
        drive_something(motor[gearDrill],0);
        drive_something(motor[gearCrane],0);
        Serial.println("down_drill complete!!");

        Serial.println("drill crane up");
        drive_something(motor[gearDrill],250);
        drive_something(motor[gearCrane],200);
        
        delay(1000);
        drive_something(motor[gearDrill],0);
        drive_something(motor[gearCrane],0);
        
        Serial.println("Up_drill complete!!");
        //send to esp32 is complete drilling
        
}