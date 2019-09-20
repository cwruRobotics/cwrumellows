// Bluetooth bodule driver library - v1
// Zach Baldwin 2019

#include "btelib.h"
#include <SoftwareSerial.h>	// Needed for the serial port used to interface with the bluetooth module

// Constructor, get the pins to be used for the serial port
btelib::btelib(byte RxPin, byte TxPin) {
	// Stuff used when initalizing the object goes here
	_RxPin = RxPin;
	_TxPin = TxPin;
}

// Initialize our object
void begin(unsigned long baudRate) {
	bteSerial(_RxPin, _TxPin);	// Tell which pins we will be using
	bteSerial.begin(9600);	// Start the serial port
}

// Check to make sure the bluetooth module is ready
bool btelib::areYouThere() {
	bteSerial.println("AT");
	
	// Check to see if we got back "OK"
	return waitForResponse("OK", false, true);
}

// Set the timeout delay to X mS
void btelib::setTimeout(unsigned long timeoutDelayWanted) {
	btelib::timeoutDelay = timeoutDelayWanted;
}

unsigned long getTimeout() {
	return ::timeoutDelay;
}

bool btelib::waitForResponse(String messageToWaitFor, bool caseSensitive, bool useTimeout) {
	
	unsigned long startTime = millis();	// Used for determining the timeout if needed.

	currentChar = ' ';

	// Get the length of our string
	stringLength = messageToWaitFor.length();
	
	if (!caseSensitive)
		messageToWaitFor.toUpperCase();
	
	int j = 0;	// The current number of correct characters in a row recieved
	while (j != stringLength) {
		
		do { 
			currentChar = bteSerial.read();
			
			// Now make sure that we do not run over the timeout delay if we are using it
			if (useTimeout && ((millis() - startTime) >= timeoutDelay) )
				return false;	//Hit the timeout, return false
		} while (currentChar == -1);
		
		// If we don't case about the case, ignore it.
		if (!caseSensitive)
			currentChar.toUpperCase();
		
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


// return the value 5
int btelib::get5() {
	return 5;
}
