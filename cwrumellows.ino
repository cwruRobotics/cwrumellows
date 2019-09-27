// #include "btelib/btelib.h"
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bteSerial(2, 3);

enum BUTTONS {
    TOP = 'A',
    RIGHT,
    DOWN,
    LEFT,
    TRIANGLE,
    CIRCLE,
    CROSS,
    SQUARE
};

bool turningRight = false;
bool turningLeft = false;

Servo turntableServo;

void setup() {
    turntableServo.attach(9); //Pin 9????

    turntableServo.write(90);

    bteSerial.begin(9600);

    int now = millis();
    while (millis() - now < 3000) {

    }

    Serial.begin(115200);
    while (!Serial);

    Serial.println("Started");
}

void loop() {
    char input = bteSerial.read();
    if (input >= 0) {
        Serial.print((int)input);
    }
    
    Serial.println("running\n");

    if (input == '\x00'){
        //One button are released
        //Set all buttons to false
        //    If buttons are still pressed, we'll get a lower case letter soon and turn it back on
        turningRight = false;
        turningLeft = false;
    }else {
        if (isLowerCase(input)) {
            input = input - 0x20;
        }

        switch(input) {
            case LEFT:
                turningLeft = true;
                break;
            case RIGHT: 
                turningRight = true;
                break;
            default:
                //Ignore button presses right now
                break;
        }

        //If left and right are both pressed, pretend like neither is pressed
        if (turningLeft && turningRight) {
            turningRight = false;
            turningLeft = false;
        }
    }

    //Untested!
    //if left, turn turntable left, etc.
    //100 is the middle
    if (turningLeft) {
       turntableServo.write(100);
        Serial.println("left");
    }else if (turningRight) {
       turntableServo.write(80);
        Serial.println("right");
    }else {
        turntableServo.write(90);
    }

    delay(200);
}
