
bool drive_drill(pin_motor geardrill,pin_motor gearcrane)
{
        
        Serial.println("drill crane down");
        unsigned long t = millis();
        drive_something(geardrill,250);
        drive_something(gearcrane,-50);
        
        while(chk_switch(L_switch)==HIGH) { delay(50); } //HIGH is not yet pressed
        drive_something(geardrill,0);
        drive_something(gearcrane,0);
        Serial.println("down_drill complete!!");

        Serial.println("drill crane up");
        drive_something(geardrill,250);
        drive_something(gearcrane,200);
        
        delay(1000);
        drive_something(geardrill,0);
        drive_something(gearcrane,0);
        
        Serial.println("Up_drill complete!!");
        //send to esp32 is complete drilling
        
}
bool _drill_process(int status,pin_motor geardrill,pin_motor gearcrane,pin_motor L_wheel,pin_motor R_wheel)
{
    switch (status)
    {
        case wait_for_drill:
            Serial.println("wait_for_drill");
            drive_something(geardrill,0);
            drive_something(gearcrane,0);
            drive_something(L_wheel,0);
            drive_something(R_wheel,0);
            break;
        case drilling:
            Serial.println("drilling");
            drive_something(L_wheel,0);
            drive_something(R_wheel,0);
            drive_drill(geardrill,gearcrane);
            break;     
        case read_probe:
            Serial.println("read_probe");
            drive_something(L_wheel,0);
            drive_something(R_wheel,0);
            drive_something(geardrill,0);
            drive_something(gearcrane,0);
            break;
        case sending_probe:
            Serial.println("Sending probe");
            drive_something(L_wheel,0);
            drive_something(R_wheel,0);
            drive_something(geardrill,0);
            drive_something(gearcrane,0);
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}

