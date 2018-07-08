#include "Arduino.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//for connect esp32
#define LLC_TX 13
#define LLC_RX 12

//GPS
#define GPS_TX 10
#define GPS_RX 11
#define GPSBaud = 9600

//Limit
#define L_switch 1

//Left_Wheel
#define LW_Din1 8
#define LW_Din2 9
#define LW_Anin A0
//Right_Wheel
#define RW_Din1 4
#define RW_Din2 5
#define RW_Anin A1
//Crane
#define Cr_Din1 A3
#define Cr_Din2 A4
#define Cr_Anin A2
//Drill
#define Dr_Din1 6
#define Dr_Din2 7
//for all motor
#define gearCrane 0
#define gearDrill 1
#define L_wheel 2
#define R_wheel 3
#define NMOT 4

#include "_motor.h"
#include "_dcode_nano.h"
#include "_general_mode.h"
#include "_gps.h"
#include "_1landing.h"
#include "_2go_site.h"
#include "_3drilling.h"
#include "_4finisher.h"

#define ERR_STS 0xF777
#define ERR_MOD 0XF888