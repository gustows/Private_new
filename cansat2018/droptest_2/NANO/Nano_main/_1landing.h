
bool _landingmode(int status)
{
    Serial.print("In Landing Mode : ");
    
    
    switch (status)
    {
        case on_air:
            Serial.println("on_air");
            break;
        case deploy:
            Serial.println("deploy");
            break;
        case landing:
            Serial.println("landing");
            break;
        case wait_for_cut:
            Serial.println("wait_for_cut");
            break;
        case wire_cutting:
            Serial.println("wire_cutting");
            break;
        default: 
            Serial.println("Invalid status");    
            return 0;
            break;
    }
    return 1;
    
}

