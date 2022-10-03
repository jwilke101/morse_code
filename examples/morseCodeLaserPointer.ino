// Morse Code Laser Pointer
// morseCodeLaserPointer.cpp 
// Written by: Jeffrey A. Wilke
// Copyright (C) 2022 Jeffrey A. Wilke
// GNU GPL V3

#include "morse_code.h"

// Also: morseCode mc("SOME MESSAGE", 10, 150);
morseCode mc;

void setup() {
  
  mc.pwmPin(10);
  mc.defineUnit(150);  // 150 millis
  
}

void loop() {

  mc.messageToEncode("SOME MESSAGE A TO Z 0 TO 9 -9.0 OK AR");
  mc.playMessage();
  
  delay(5000);
  
  // Plays: SOS LAT 99.99 LON 99.99 [USER MESSAGE] AR
  mc.playGpsSos("MESSAGE TO INFIX");
  
  delay(5000);

}
