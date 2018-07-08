#include "_0header.h"

void _finish_mode(int status)
{
    }
    switch (status)
    {
        case idle:
            set_zero_motor();
            Serial.println("MISSION COMPLETE!!");
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}