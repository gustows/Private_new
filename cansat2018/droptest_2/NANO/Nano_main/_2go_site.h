#include "_0header.h"

void _go_2Site_mode(int status)
{

    switch (status)
    {
        case requests_gps:
            //already send
            set_zero_motor();
            break;
        case run_to_pos:
            navigation(target);
            break;
        case on_position:
            while(wait_cmd(1) == false ) {} 
            //send to esp32
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}

void navigation(coordinate target)
{
    //requests_gps
    //calculate distance
    //calculate direction
    //check distance
    //>10 walk to direction
    //<10 set_zero_motor change state to on_position
}