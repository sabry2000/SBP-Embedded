#include <Arduino.h>
#include "ControlledCurrentSensor.h"

ControlledCurrentSensor::ControlledCurrentSensor(int sensorID, int measurementPinNumber, double voltage, int controlPinNumber) :  CurrentSensor(sensorID, measurementPinNumber, voltage) {
  this->controlPinNumber = controlPinNumber;

  pinMode(controlPinNumber, OUTPUT);

  this->powerOff();
}

ControlledCurrentSensor::~ControlledCurrentSensor(){
  
}

Sensor::SensorType ControlledCurrentSensor::isType(){
  return SensorType::CONTROLLED_CURRENT_SENSOR;
}

void ControlledCurrentSensor::powerOff() {
  digitalWrite(this->controlPinNumber, LOW);
}

void ControlledCurrentSensor::powerOn() {
  digitalWrite(this->controlPinNumber, HIGH);
}

// TODO: need to fix this method
bool ControlledCurrentSensor::isPoweredOn(){
  return (this->getMeasurement() > 0.5);
}
