#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(int sensorID, int measurementPinNumber){
  this->sensorID = sensorID;
  this->measurementPinNumber = measurementPinNumber;

  pinMode(measurementPinNumber, INPUT);
}

Sensor::~Sensor(){
  
}

double Sensor::getMeasurement() {
  return analogRead(this->measurementPinNumber);
}
