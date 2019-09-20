#include "btelib.h"

btelib *bluetoothConnection;

void setup() {
    btelib bluetoothConnection(2, 3); //Rx pin, Tx pin
}

void loop() {
    char input = bluetoothConnection->getChar();

    switch (input){
        case '\x00':
            //All buttons are released
            break;
    }
}
