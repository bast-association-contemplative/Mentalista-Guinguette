/* ----------------------------------------------------------------------------------------------------
 * MENTALISTA GUINGUETTE – PRINTER
 * Update: 08/05/16
 *
 * print what you want with OpenBCI / Processing
 * Using Adafruit Termal Printer
 * 
 * ----------------------------------------------------------------------------------------------------
 */ 
 
#include "Adafruit_Thermal.h"
#include "words.h"
#include "SoftwareSerial.h"
#define TX_PIN 11
#define RX_PIN 10

SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);

void setup() {
  mySerial.begin(19200);
  printer.begin();  

  Serial.begin(115200);
  
  // print help
  Serial.println("PRINTER Controller: starting..."); 
  Serial.println("Help Commands: ");
  Serial.println("    'P' ou '{' = print!");
  Serial.println("    'S'        = sleep printer");
  Serial.println("    'R'        = wake printer");
  
  Serial.println("Waiting for Alpha Brainwaves...");
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    char inChar = Serial.read();
    Serial.print("Received ");
    Serial.println(inChar);

    if( inChar == 'P' || inChar == '{'){
      printNow();
    } else if ( inChar == 'S' ) {
      printer.sleep();      // Tell printer to sleep
    } else if ( inChar == 'R' ) {
      printer.wake();       // MUST wake() before printing again, even if reset
      printer.setDefault(); // Restore printer to defaults
    }
  }
}

void printNow(){
  int orderLenght = random(0,DATA_SIZE);

  printer.boldOn();
  printer.println("j'aimerais " + data[orderLenght] + "\n");
   Serial.println("j'aimerais " + data[orderLenght] + "\n");
  printer.boldOff();
}

