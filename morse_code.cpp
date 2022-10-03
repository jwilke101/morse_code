// morse_code.cpp 
// Written by: Jeffrey A. Wilke
// Copyright (C) 2022 Jeffrey A. Wilke
// GNU GPL V3

#include "morse_code.h"

// for SoftwareSerial
// SoftwareSerial _ss(RX, DX);


String _morseCodes[CODES_CNT][FIELDS_CNT] =
{
  { ".", "*-*-*-" },
  { "-", "-****-" },
  { "A", "*-" },               /* Letters */
  { "B", "-***" },
  { "C", "-*-*" },
  { "D", "-**" },
  { "E", "*" },
  { "F", "**-*" },
  { "G", "--*" },
  { "H", "****" },
  { "I", "**" },
  { "J", "*---" },
  { "K", "-*-" },
  { "L", "*-**" },
  { "M", "--" },
  { "N", "-*" },
  { "O", "---" },
  { "P", "*--*" },
  { "Q", "--*-" },
  { "R", "*-*" },
  { "S", "***" },
  { "T", "-" },
  { "U", "**-" },
  { "V", "***-" },
  { "W", "*--" },
  { "X", "-**-" },
  { "Y", "-*--" },
  { "Z", "--**" },
  { "0", "-----" },             /* Arabic Numerals */
  { "1", "*----" },
  { "2", "**---" },
  { "3", "***--" },
  { "4", "****-" },
  { "5", "*****" },
  { "6", "-****" },
  { "7", "--***" },
  { "8", "---**" },
  { "9", "----*" }
};


// Constructor
morseCode::morseCode() {

  _pwmPin = DEFAULT_DEV;
  pinMode(_pwmPin, OUTPUT);

  _oneUnit = DEFAULT_UNIT;
}

morseCode::morseCode(String msg) {

  _pwmPin = DEFAULT_DEV;
  pinMode(_pwmPin, OUTPUT);

  _message  = msg;
  _message.toUpperCase();

  _oneUnit = DEFAULT_UNIT;

}

morseCode::morseCode(String msg, int devpin) {

  _pwmPin = devpin;
  pinMode(_pwmPin, OUTPUT);

  _message  = msg;
  _message.toUpperCase();

  _oneUnit = DEFAULT_UNIT;

}

morseCode::morseCode(String msg, int devpin, int defineUnits) {

  _pwmPin = devpin;
  pinMode(_pwmPin, OUTPUT);

  _message  = msg;
  _message.toUpperCase();

  _oneUnit = defineUnits;

}

String morseCode::_getCode(String letter) {

  //---------------------------------          1         2         3
  //---------------------------------01234567890123456789012345678901234567
  String const static strAlphabet = "-.ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  int pos = strAlphabet.indexOf(letter);
  return (_morseCodes[pos][1]);

}

String morseCode::_buildMCMessage() {

  String mcd = "";
  String chr = "";



  for (int a = 0; a < _message.length(); a++) {

    chr = _message.substring(a, a + 1);

    if (chr == " ") {
      mcd = mcd + " ";
    }
    else {
      String cd = (_getCode(chr));
      mcd = mcd + cd;

      if (a + 1 < _message.length()) {
        if (!(_message.substring(a + 1, a + 2).equals(" ")) ) {
          mcd = mcd + "|";
        }
      }
    }
  }

  Serial.print("%%%"); Serial.print(_message); Serial.println("@@@");
  Serial.print("$$$"); Serial.print(mcd); Serial.println("###");
  delay(5000);
  return (mcd);

}


void morseCode::playGpsSos(String msg = "") {

  // Thanks to Mikal Hart for the following library and example code
  // https://github.com/mikalhart/TinyGPS
  TinyGPS _gps;

  _ss.begin(GPS_BAUD);

  boolean newData = false;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)  {
    while (_ss.available())    {
      char c = _ss.read();
      if (_gps.encode(c)) { // Did a new valid sentence come in?
        newData = true;
      }
    }
  }

  if (newData)  {
    float flat, flon;
    unsigned long age;

    _gps.f_get_position(&flat, &flon, &age);
    if (flat != TinyGPS::GPS_INVALID_F_ANGLE  &&
        flon != TinyGPS::GPS_INVALID_F_ANGLE) {
      messageToEncode(("SOS LAT " + String(flat) + " LON " + String(flon) + " " + msg + " AR"));
      playMessage();
    }
  }

}




void  morseCode::_playDevice(String chr) {

  if (chr.equals(" ")) {          // = " " (space) 7 units.
    digitalWrite(_pwmPin, LOW);   // 
    delay((_oneUnit*6));          // Note: Six more units needed to accountfor delay after each dot, and dash.
  } else if (chr.equals("*")) {   // = "*" (asterik)
    digitalWrite(_pwmPin, HIGH);  // Send dot on pin on for one unit.
    delay(_oneUnit);
    digitalWrite(_pwmPin, LOW);   // One unit delay between beeps.
    delay(_oneUnit);              
  } else if (chr.equals("-")) {   // = "-" (minus sign)
    digitalWrite(_pwmPin, HIGH);  // Send dash on pin on for three units.
    delay((_oneUnit*3));
    digitalWrite(_pwmPin, LOW);   // One unit delay between beeps.
    delay(_oneUnit);
  } else if (chr.equals("|")) {   // = "|" (Space between letters. 3 Units)
    digitalWrite(_pwmPin, LOW);
    delay((_oneUnit * 2));        // Note: Two more units needed to accountfor delay after each dot, and dash.
  }
}

void morseCode::playMessage() {


  if (!(_message.equals(""))) {

    String mcd = _buildMCMessage();
    for (int a = 0; a < mcd.length(); a++) {
      String chr = mcd.substring(a, a + 1);
      _playDevice(chr);
    }
  }
}

void morseCode::pwmPin(int devpin) {

  if (devpin > 1 && devpin < 14) {
    _pwmPin = devpin;

  }
}


void morseCode::defineUnit(int milli) {

  // division of a second
  _oneUnit = milli;
}


void morseCode::messageToEncode(String msg) {

  _message  = msg;
  _message.toUpperCase();

}

String morseCode::encodedMessage() {

  if (!(_message.equals(""))) {
    String enc = _buildMCMessage();

    return (enc);
  }
  return "";
}
