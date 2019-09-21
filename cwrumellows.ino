//#include "btelib/btelib.h"

//btelib *bluetoothConnection;

void setup() {
//    btelib bluetoothConnection(2, 3); //Rx pin, Tx pin
}

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

    //TODO:
    //if left, turn turntable left, etc.
}
