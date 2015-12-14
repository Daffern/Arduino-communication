#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

AltSoftSerial altSerial;

XBee xbee = XBee();

int led = 13;

void setup() {


  pinMode(led,OUTPUT);
  
  Serial.begin(9600);//usb
  while (!Serial) ; // wait for Arduino Serial MoLnitor to open
  Serial.println("AltSoftSerial Test Begin");
  
  altSerial.begin(9600);//xbee
  altSerial.println("Hello World");

  xbee.setSerial(altSerial);
  
}

void loop() {
  char c;
  

  if (Serial.available()) {//receive usb
    c = Serial.read();
    altSerial.print(c);//send xbee
   
     
  }
  if (altSerial.available()) {//receive xbee
    c = altSerial.read();
    Serial.print(c);//send usb
    digitalWrite(led, LOW);
  }
  
  if (c == 'H'){
     digitalWrite(led, HIGH);
  }
  else if ( c == 'L'){
    digitalWrite(led, LOW);
  }

  
}

