#include "LEDStrip.h"
#include "LEDStripController.h"

int commandIndex = 0;

LEDStripController* ledStripController;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting setup");

  LEDStrip ledStrip = LEDStrip();

  ledStripController = new LEDStripController(ledStrip);
  Serial.println("Finishing setup");

}

void loop() {ledStripController->displayPattern(commandIndex++);}
