// Bluetooth module driver library - v1
// Zach Baldwin 2019


#ifndef BTELIB
#define BTELIB

// For arduino standard libraries
#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
	#include "WConstants.h"
#endif

//class SoftwareSerial;	// forward declaration for the serial library

// Here is the class for the driver functions
class btelib : public SoftwareSerial {
	public:
		// Constructor
		btelib(byte RxPin=2, byte TxPin=3);

		// Methods
		void btelib::begin(unsigned long baudRate);
		bool areYouThere();
		
		void setTimeout(unsigned long timeoutDelayWanted);
		unsigned long getTimeout();
		
		int get5();

	private:
		byte _RxPin;	// Pins used for the serial port
		byte _TxPin;
//		SoftwareSerial bteSerial;	// Name of serial port object
		
		// Timeout delay for messages over the serial port
		unsigned long timeoutDelay = 500;
		
		bool waitForResponse(String messageToWaitFor, bool caseSensitive, bool useTimeout);
};

#endif
