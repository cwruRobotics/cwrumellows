// #include "btelib/btelib.h"
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bteSerial(2, 3); //Rx, Tx???

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

const int TABLE_ZERO = 1891;

const int FLYWHEEL_MIN = 60;  //A relatively slow speed to jump to from 0 when the button is pressed
const int FLYWHEEL_MAX = 70;

bool turningRight = false;
bool turningLeft = false;

int flywheelPower = 0;

Servo turntableServo;

Servo leftMotor;
Servo rightMotor;

Servo actuator;

int actuatedTime = 0;
//0 means not extended
//Every tick, this timer is incrimented, until we pull it back.

void setup() {
    turntableServo.attach(8); //Pin 8-turntable
    
    leftMotor.attach(10); //Pin 10
    // rightMotor.attach(11); //Pin 11

    leftMotor.write(0);
    
    turntableServo.write(TABLE_ZERO);

    actuator.attach(7);
    
    // TODO: Do we need this?
//    int now = millis();
    bteSerial.begin(9600);

    while (!bteSerial);

    Serial.begin(115200);
    while (!Serial);

    Serial.println("Started");
    
    
//    Serial.println(!!bteSerial);
}

void loop() {
    char input = bteSerial.read();
    if (input >= 0) {
        Serial.print((int)input);
    }
    
    Serial.println("running\n");

    if (actuatedTime > 0) {
        actuatedTime++;
    }

    if (input == '\x00'){
        //One button are released
        //Set all buttons to false
        //    If buttons are still pressed, we'll get a lower case letter soon and turn it back on
        turningRight = false;
        turningLeft = false;
        flywheelPower = 0;
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
            case TRIANGLE:
                Serial.println("Triangle pressed.");
                flywheelPower = FLYWHEEL_MIN;
                break;
//            case CROSS:
//                flywheelPower = 180; //"boost" AKA "SELF DESTRUCT"
//                break;
            case CIRCLE:
                if (actuatedTime == 0) {
                    actuator.write(150);
                    actuatedTime = 1;
                }
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

    /* --Turntable --*/
    //if left, turn turntable left, etc.
    //TABLE_ZERO is the middle
    if (turningLeft) {
        turntableServo.writeMicroseconds(TABLE_ZERO - 100);
       
//        Serial.println("left");
    }else if (turningRight) {
        turntableServo.writeMicroseconds(TABLE_ZERO + 100);
        
//        Serial.println("right");
    }else {
        turntableServo.write(TABLE_ZERO);
    }
    
    /* --Flywheel-- */
    if (flywheelPower > 0 && flywheelPower < FLYWHEEL_MAX) {
        flywheelPower += 0.5;
    }

    leftMotor.write(flywheelPower);
    
    /* --Actuator-- */
    //Wait 2 tenths of a second after we extend
    /*
        -Extend (t=1)
        -Wait 100ms
        -t=2
        -Wait 100ms
        -t=3
    */
    if (actuatedTime == 4) {
        actuator.write(80);
        actuatedTime = 0;
    }else if (actuatedTime == 0) {
//        Serial.println("Hi");
        actuator.write(93);
    }
 
    delay(100);
}
