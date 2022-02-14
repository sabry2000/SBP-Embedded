#include <Arduino.h>
#include "CurrentSensor.h"

CurrentSensor::CurrentSensor(char *sensorName, int measurementPinNumber, double voltage) {
  this->sensorName = sensorName;
  this->measurementPinNumber = measurementPinNumber;
  this->voltage = voltage;

  pinMode(measurementPinNumber, INPUT);
}

double CurrentSensor::getVoltage() {
  return this->voltage;
}

String CurrentSensor::getMeasurementMessage() {
  char message[50];
  sprintf(message, "Current Sensor Name: %s, Current: %f, Voltage: %f", this->sensorName, this->getMeasurement(), this->getVoltage());
  return message;
}
