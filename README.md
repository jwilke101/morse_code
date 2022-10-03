# morse_code
<h1>Morse Code library for Arduino.</h1>
<h2>Turns digital pin on and off with morse code timing.</h2>

Tested with Mega 2560, two wire laser module, and Neo7 GPS with 9600 baud.

Morse Codes are kept in global array: morseCodes[ ][ ] found in morse_code.cpp 

Contains upper case letters A-Z, numbers 0-9 and also includes (.) period, and, (-) minus sign, for GPS Coordinates. 

If you add elements to the array, be sure to add their alphanumeric digit to the Alphabet string in _getCode(); morse_code.cpp

<ul>
<li>#define CODES_CNT 38</li>
</ul>

Example code can be use a laser pointer with (+) wire in digital pin 10 (by default) and the (-) wire in ground. The code Will flash laser dots and dashes with the proper morse code durations. The same code can be used with a passive buzzer or any other device if attached to pin 10 and ground. 

Any device attached to the default, or, user defined pin will recieve HIGH (on) and LOW (off) output.

Method playGpsSos(msg) will find your gps coordinates and play a message with the text: "SOS LAT 99.99 LON 99.99 [msg] AR"


<b>Spacing and length of the signals are calculated from one unit.</b>
<ul>
<li>A dot is equal to one unit.</li>

<li>A dash is equal to three units.</li>

<li>The space between the signals forming the same letter is equal to one unit.</li>

<li>The space between two letters is equal to three units.</li>

<li>The space between two words is equal to seven units.</li>
</ul>

These settings can be found in morse_code.h

<ul>
<li>// In milliseconds 250 = 1/4 of a second.</li>
<li>#define DEFAULT_UNIT 250    </li>
</ul>

<ul>
<li>// Digital pin for device change here or constructor.</li?
<li>#define DEFAULT_DEV 10</li>
</ul>

<ul>
<li>// Change your GPS Baud here.</li>
<li>#define GPS_BAUD 9600</li>
</ul>

<ul>
<li>// For GPS Mega 2560 uses 19, 18 RX, TX Uno use 4,3</li>
<li>#define RX 19</li>
</ul>
#define TX 18

#define _ss Serial1   // Comment for Uno.

If using Uno, or SoftwareSerial, be sure to uncomment the following line in morse_code.cpp

// SoftwareSerial _ss(RX, TX);


Uncomment the following line in morse_code.h

// #include "SoftwareSerial.h"         
