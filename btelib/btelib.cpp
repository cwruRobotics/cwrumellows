// Bluetooth bodule driver library - v1
// Zach Baldwin 2019

#include "btelib.h"
#include <SoftwareSerial.h>	// Needed for the serial port used to interface with the bluetooth module

// Constructor, get the pins to be used for the serial port
btelib::btelib(byte RxPin, byte TxPin) {
    // Stuff used when initalizing the object goes here
    _RxPin = RxPin;
    _TxPin = TxPin;
    SoftwareSerial bteSerial(_RxPin, _TxPin); // Tell which pins we will be using
	OK_TEXT = "OK";	// The OK string
}

// Initialize our object
void btelib::begin(unsigned long baudRate) {
    bteSerial->begin(baudRate);	// Start the serial port
}

// Check to make sure the bluetooth module is ready
bool btelib::areYouThere() {
    bteSerial->println("AT");

    // Check to see if we got back "OK"
    return waitForResponse(OK_TEXT, false, true);
}

// Set the timeout delay to X mS
void btelib::setTimeout(unsigned long timeoutDelayWanted) {
    timeoutDelay = timeoutDelayWanted;
}

unsigned long btelib::getTimeout() {
    return timeoutDelay;
}


// Software Reset of the module
void btelib::resetModule() {
    writeln("AT+RESET", true);
    waitForResponse(OK_TEXT, false, true);
}

// Get the firmware Version
String btelib::getFirmVer() {
    writeln("AT+VERSION", false);
	String myString = readln(true);
	myString.remove(0.9);
    return myString;
}

// Set the name of the module
bool btelib::setModuleName(String moduleName) {
    writeln("AT+NAME" + moduleName, false);
    return waitForResponse(OK_TEXT, false, true);
}

// Get the name of the module
String btelib::getModuleName() {
    writeln("AT+NAME", false);
	String myString = readln(true);
	myString.remove(0,6);
    return myString;
}

// Get the state of the module
byte btelib::getState() {
    writeln("AT+STATE", true);
    return (byte)(readln(true).charAt(8) - '\x30');
}

// Wait for a response from the module
bool btelib::waitForResponse(String messageToWaitFor, bool caseSensitive, bool useTimeout) {
	
    unsigned long startTime = millis();	// Used for determining the timeout if needed.

    char currentChar;

    // Get the length of our string
    int stringLength = messageToWaitFor.length();
	
    if (!caseSensitive)
        messageToWaitFor.toUpperCase();
	
    int j = 0;	// The current number of correct characters in a row recieved
    while (j != stringLength) {
		
        do { 
            currentChar = readChar();
			
            // Now make sure that we do not run over the timeout delay if we are using it
            if (useTimeout && ((millis() - startTime) >= timeoutDelay) )
                return false;	//Hit the timeout, return false
        } while (currentChar == '\x00');
		
        // If we don't case about the case, ignore it.
        if (!caseSensitive)
            currentChar & 0x5F;
		
        // If the current character that we are looking at is the next one in the string that 
        //   we are waiting for, incriment the value, otherwise reset it.
        if (currentChar == messageToWaitFor[j])
            j++;
        else 
            j = 0;
    }
	
    // No timeout, "YAY" - return true
    return true;
}

// Get a character from the module
char btelib::readChar() {
    char data = bteSerial->read(); 
   
    return (data == -1) ? '\x00' : data;
}

// Read a line from the module
String btelib::readln(bool useTimeout) {
    unsigned long startTime = millis();

    char charIn;
    String stringOut;

    do {
        charIn = readChar();

        if ((charIn == '\r') || (charIn == '\n'))
            break;

        if (useTimeout && ((millis() - startTime) >= timeoutDelay))
            return "";

        if (charIn = 0)
            continue;   // If no character is in buffer, check again
        
        // Append character to string
        
        stringOut += charIn;

    } while ((charIn != '\r') && (charIn != '\n'));
    
    return stringOut;
}

// Send a character to the module
void btelib::writeChar(char characterToSend) {
    bteSerial->print(characterToSend);
}

// Send a string to the module
void btelib::writeln(String characterString, bool waitForOK) {
    bteSerial->println(characterString);
    if (waitForOK)
        waitForResponse(OK_TEXT, false, true);
}

// Check serial port
void btelib::checkPort() {
	while(true) {
		bteSerial->println("AT");
	}
}