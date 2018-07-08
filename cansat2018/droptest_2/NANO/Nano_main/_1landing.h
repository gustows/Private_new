#include "_0header.h"

bool _landingmode(int status)
{
    Serial.print("In Landing Mode : ");
    
    Serial.println(decode_cmd(status));
    
    switch (status)
    {
        case on_air:
            break;
        case deploy:
            break;
        case landing:
            break;
        case wait_for_cut:
            break;
        case wire_cutting:
            break;
        default: 
            Serial.println("Invalid status");    
            return 0;
            break;
    }
    return 1;
    
}

