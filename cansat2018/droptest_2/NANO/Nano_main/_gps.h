#include "_0header.h"

typedef struct{
  double la,lo;
}coordinate;

bool recieve_GPS()
{
    while (myPos.available())
      gps.encode(myPos.read());
    if(gps.isValid()==true)
    return 1;
    else return 0;
}

