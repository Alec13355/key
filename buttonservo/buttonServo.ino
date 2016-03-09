#include <SoftwareSerial.h>       // import the serial library
#include <Servo.h>                // import the servo library

SoftwareSerial blueTooth(10, 11); // RX, TX
Servo myservo;                    // creates a servo object? not sure part of the sorce code for using servos
const int ledpin=13;              // led on D13 will show blink on / off
const int buttonPin=2;            // button attatched to pin 2
const int servoPin=7;             // servo attatched to pin 7
const int locked = 100;           // position of servo when door is locked
const int unlocked = 80;          // position of servo when door is unlocked
boolean unlock = false;           // is it time to unlock the door?
boolean blueYes = false;          // did the bluetooth device say to acctuate the lock
int pos = locked;                 // initalizes the position of the servo to the locked position


void setup() {
   blueTooth.begin(9600);         // set the data rate for the SoftwareSerial port
   pinMode(ledpin,OUTPUT);        // sets the light on the aruino to be an output, isnt used right now
   pinMode(buttonPin, INPUT);     // sets the button's pin number to take input
   myservo.attach(servoPin);      // attatches a servo to the servo pin so it can be controlled
}

void loop() {
   if (blueTooth.available()) {                      // if info arrived from blueTooth device
      if (blueTooth.read()=='1') {                   // if that info was '1'
         blueYes = true;                             // it's time to lock or unlock the door
      }
   }
   if (digitalRead(buttonPin)==HIGH || blueYes) {      // if the button is being pressed or the bluetooth device told us to open
      if (unlock) {                                  // and if unlock is already true
         unlock = false;                             // set unlock to false
      }
      else {                                         // if its not true
         unlock = true;                              // it is now
      }
      blueYes = false;                                 // this is back to false
   }
   while(pos <= locked && unlock){                   // while position is less than the locked position and unlock is true
      myservo.write(pos);                            // tell servo to go to position in variable 'pos'
      delay(15);                                     // waits 15ms for the servo to reach the position
      pos++;                                         // increment the position
   }
   while(pos>=unlocked && !unlock){                  // while the position is greater than the unlocked position and unlock is false
      myservo.write(pos);                            // tell servo to go to position in variable 'pos'
      delay(15);                                     // waits 15ms for the servo to reach the position
      pos--;                                         // increment the position
   }
}

