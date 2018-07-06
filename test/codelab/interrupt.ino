#include <Servo.h>

                    
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int motor = 3;
// variables will change:
volatile bool temp = HIGH;         // variable for reading the pushbutton status
int  lastpos = 0;
int pos=0;
int *pp = &pos ;
Servo myS;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, RISING);
	myS.attach(motor);
}

void loop() {
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myS.write(*pp);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myS.write(*pp);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void pin_ISR() {
  temp=!temp;
  
  digitalWrite(ledPin , temp);
  if(temp) {
    lastpos = pos;
    pp = &lastpos;
  }
  else {
    pp = &pos;
  	*pp = lastpos;
  }
  /*if(myS.attached()==1 ) {
    myS.detach();
  }
  else { myS.attach(motor);  }
 */

}