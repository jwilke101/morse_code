// morse_code.cpp 
// Written by: Jeffrey A. Wilke
// Copyright (C) 2022 Jeffrey A. Wilke
// GNU GPL V3


#ifndef morse_code_h
#define morse_code.h

#include <Arduino.h>

// #include "SoftwareSerial.h"         // Uncomment for Uno
#include "TinyGPS.h"

/****************************************************************************
// Spacing and length of the signals
// A dash is equal to three dots.
// The space between the signals forming the same letter is equal to one dot.
// The space between two letters is equal to three dots.
// The space between two words is equal to seven dots.
****************************************************************************/
#define DEFAULT_UNIT 250    // In milliseconds 250 = 1/4 of a second.

#define DEFAULT_DEV 10      // Digital pin for device change here or constructor.
#define CODES_CNT 38        // The codes array contains morse codes for chars: period, minus, A-Z and 0-9
#define FIELDS_CNT 2
#define LETTER 0
#define CODE 1
#define GPS_BAUD 9600

// For GPS Mega 2560 uses 19, 18 as Serial1
#define RX 19               
#define TX 18
#define _ss Serial1


class morseCode {

  public:

    // Constructor
    morseCode();
    morseCode(String msg);
    morseCode(String msg, int devpin);
    morseCode(String msg, int devpin, int defunits);

    
    void pwmPin(int pin);
    void defineUnit(int milli);
    void writeGpsSOS();
    void messageToEncode(String msg);
    String encodedMessage();
    void playMessage();
    void playGpsSos(String msg="");

  private:

    // Private Methods
    void _playDevice(String chr);

    String _buildMCMessage();
    String _getCode(String letter);
    

    int _pwmPin;
    int _oneUnit = 250;
    String _message = "";

};
#endif
