
#include "Adafruit_Thermal.h"
#include "words.h"
#include "SoftwareSerial.h"
#define TX_PIN 11
#define RX_PIN 10

SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);

int ManifestoLenght = 0;

void setup() {
  mySerial.begin(19200);
  printer.begin();  

  Serial.begin(115200);
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    char inChar = Serial.read();
    Serial.print("Received ");
    Serial.println(inChar);

    if( inChar == 'P' || inChar == '{'){
      printManifesto();
    } else if ( inChar == 'S' ) {
      printer.sleep();      // Tell printer to sleep
    } else if ( inChar == 'R' ) {
      printer.wake();       // MUST wake() before printing again, even if reset
      printer.setDefault(); // Restore printer to defaults
    }
  }
}

void printManifesto(){
  int orderLenght = random(0,9);

  printer.boldOn();
  printer.println("j'aimerais " + data[orderLenght] + "\n");
  printer.boldOff();
}

