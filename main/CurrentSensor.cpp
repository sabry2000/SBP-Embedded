#include <Arduino.h>
#include "Sensor.h"
#include "CurrentSensor.h"

CurrentSensor::CurrentSensor(char *sensorName, int measurementPinNumber, double voltage) : Sensor(sensorName, measurementPinNumber){
  this->voltage = voltage;
}

//TODO
CurrentSensor::~CurrentSensor(){
  
}

double CurrentSensor::getVoltage() {
  return this->voltage;
}

Sensor::SensorType CurrentSensor::isType(){
  return SensorType::CURRENT_SENSOR;
}

//TODO
double CurrentSensor::getMeasurement(){
  double current = 0;
  return current;
}

String CurrentSensor::getMeasurementMessage() {
  char message[50];
  sprintf(message, "Current Sensor Name: %s, Current: %f, Voltage: %f", this->sensorName, this->getMeasurement(), this->getVoltage());
  return message;
}
