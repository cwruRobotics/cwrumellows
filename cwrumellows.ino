#include "btelib/btelib.h"
#include <Servo.h>

// Bluetooth driver library
btelib *bluetoothConnection; //Rx pin, Tx pin

// Pins used for software serial port
#define RxPIN 2
#define TxPIN 3

// Default timeout for the BTE module's response
#define D_TIMEOUT 500 // mS

// Baudrates
#define BTE_BAUD 9600  // Baudrate to communnicate with the BTE module
#define SFT_BAUD 19200 // Baudrate for the serial debug port

// Buttons and their corresponding meanings from the bluetooth module
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

// Misc Variable initialization
bool turningRight = false;
bool turningLeft = false;

// Our servo objects
#define SERVO_CENTER 100 // Center (STOP) value for the servos

Servo turntableServo;     // Create object for the servo controling the turntable
#define TTSERVO_PIN 9  // Pin for controling the turn table servo


// Now, setup everything...
void setup() {

    // Setup the bluetooth module
    btelib bluetoothConnection(RxPIN, TxPIN);
    //bluetoothConnection.begin(BTE_BAUD);

    // Wait for the bluetooth module
    //while (!bluetoothConnection.areYouThere()) {
        // The first set of noop stuff...
    //}
    // Setup the servo connections
    turntableServo.attach(TTSERVO_PIN); 

    // Center (or stop - for continuous rotation) the servos
    turntableServo.write(SERVO_CENTER);

    // Setup our debug serial port
    Serial.begin(SFT_BAUD);
    while (!Serial) { // Wait for the serial port to be open
        // Some sort of noop stuff...
    }

    // Done initializing!
    Serial.println("Started");
    delay(200);
    Serial.println("HELLO");
    delay(200);

}

void loop() {
    delay(200);
    // See if there are any characters from the BTE module
    char inputChar = bluetoothConnection->readChar();

    Serial.println(inputChar, HEX);

    /*
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
        turntableServo.write(110);
        Serial.println("left");
    }else if (turningRight) {
        turntableServo.write(90);
        Serial.println("right");
    }
*/
    delay(200);
}
