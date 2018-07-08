
bool navigation(coordinate target,pin_motor L_wheel,pin_motor R_wheel)
{
    //P'George
    setup1();
    while(1)
    {
      loop1();  
    }
    
    //requests_gps
    //calculate distance
    //calculate direction
    //check distance
    //>10 walk to direction
    //<10 set_zero_motor change state to on_position
}

bool _go_2Site_mode(int status,pin_motor L_wheel,pin_motor R_wheel,coordinate goal)
{

    switch (status)
    {
        case requests_gps:
            //already send
            Serial.println("requests_gps");
            drive_something(L_wheel,0);
            drive_something(R_wheel,0);
 
            break;
        case run_to_pos:
            Serial.println("run_to_pos");
            navigation(goal,L_wheel,R_wheel);
            break;
        case on_position:
            Serial.println("on_position");
            //while(wait_cmd(1) == false ) {} 
            //send to esp32
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}
