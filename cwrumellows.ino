#include "btelib/btelib.h"

btelib *bluetoothConnection;

void setup() {
    btelib bluetoothConnection(2, 3); //Rx pin, Tx pin
}
/*
const enum BUTTONS {
    TOP = 'A',
    RIGHT,
    DOWN,
    LEFT,
    TRIANGLE,
    CIRCLE,
    CROSS,
    SQUARE
}

void loop() {
    char input = bluetoothConnection->readChar();
    
    if (input == '\x00'){
        //All buttons are released
        //Set all buttons to false
    }else {
        
    }
}
*/
