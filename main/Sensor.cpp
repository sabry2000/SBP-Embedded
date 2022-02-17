#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(char *sensorName, int measurementPinNumber){
  this->sensorName = sensorName;
  this->measurementPinNumber = measurementPinNumber;

  pinMode(measurementPinNumber, INPUT);
}

Sensor::~Sensor(){
  
}

double Sensor::getMeasurement() {
  return analogRead(this->measurementPinNumber);
}
