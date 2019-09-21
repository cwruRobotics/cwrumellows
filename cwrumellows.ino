//#include "btelib/btelib.h"
#include <Servo.h>

//btelib *bluetoothConnection;

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
    
//    btelib bluetoothConnection(2, 3); //Rx pin, Tx pin
}

void loop() {
//    char input = bluetoothConnection->readChar();
    char input = 'h';

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
    if (turningLeft) {
        turntableServo.write(180); //180 for full one way, 
    }else if (turningRight) {
        turntableServo.write(0); //0 for full speed the other way
    }
}
