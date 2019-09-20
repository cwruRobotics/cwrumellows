// Bluetooth module driver library - v1
// Zach Baldwin 2019


#ifndef BTELIB_H
#define BTELIB_H

// For arduino standard libraries
#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
	#include "WConstants.h"
#endif


class SoftwareSerial;	// forward declaration for the serial library

// Here is the class for the driver functions
class btelib {
	public:
		// Constructor
		btelib(byte RxPin=2, byte TxPin=3);


		// Methods
		void btelib::begin(unsigned long baudRate);	// Setup BAUD rate
		bool areYouThere(); // Get status (true = active)
		
		void setTimeout(unsigned long timeoutDelayWanted);	// Timeout for waiting for response from module
		unsigned long getTimeout();	// Returns the timeout for the module command functions
		
		void resetModule();	// Reset the module
		String getFirmVer();	// Returns the firmware version of the module
		void restoreDefault();	// Reset the module to factory defaults
		String getModuleAddress();	// Returns the address of the module
		bool setModuleName(String moduleName);	// Set the name of the module
		String getModuleName();	// Get the name of the module
		String getBlueDeviceName();	// Get the bluetooth device name
		bool setModuleMode();	// Set the module mode 1=Master, 0=Slave, 2=Slave=Loop
		byte getModuleMode();	// Gets the module mode (see setModuleMode())
		
		
		
		
		int get5();	// Returns int 5

	private:
		byte _RxPin;	// Pins used for the serial port
		byte _TxPin;
		SoftwareSerial *bteSerial;	// Name of serial port object
		
		// Timeout delay for messages over the serial port
		unsigned long timeoutDelay = 500;
		
		bool waitForResponse(String messageToWaitFor, bool caseSensitive, bool useTimeout);
};

#endif
