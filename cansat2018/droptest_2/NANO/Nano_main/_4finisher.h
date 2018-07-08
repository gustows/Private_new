
bool _finish_mode(int status)
{
    
    switch (status)
    {
        case idl:
            Serial.println("MISSION COMPLETE!!");
            break;
        default:
            Serial.println("Invalid status");
            return 0;
            break;
    }
    return 1;
}
