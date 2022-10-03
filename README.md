# morse_code
Morse Code library for Arduino. Turns on digital pin on and off with morse code timing.

Codes are kept in global array morse_code.cpp
Uppers case letters A-Z Numbers 0-9 Includes (.) period and (-) minus sign for GPS Coordinates.


Spacing and length of the signals are calculated from one unit.
A dot is equal to one unit.
A dash is equal to three units.
The space between the signals forming the same letter is equal to one unit.
The space between two letters is equal to three units.
The space between two words is equal to seven units.

These settings can be found in morse_code.h
#define DEFAULT_UNIT 250    // In milliseconds 250 = 1/4 of a second.

#define DEFAULT_DEV 10      // Digital pin for device change here or constructor.
#define CODES_CNT 38        // The codes array contains morse codes for chars: period, minus, A-Z and 0-9
#define FIELDS_CNT 2        // If you add elements, be sure to add them to the Alphabet string in _getCode().
#define LETTER 0
#define CODE 1
#define GPS_BAUD 9600       // Change your GPS Baud here.

// For GPS Mega 2560 uses 19, 18 RX, TX Uno use 4,3
#define RX 19               
#define TX 18
#define _ss Serial1   // Comment for Uno.


If using Uno, or SoftwareSerial, be sure to uncomment the following line in morse_code.cpp
// for SoftwareSerial
// SoftwareSerial _ss(RX, TX);

and the following line in morse_code.h
// #include "SoftwareSerial.h"         // Uncomment for Uno
