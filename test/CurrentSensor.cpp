#include <Arduino.h>
#include "Sensor.h"
#include "CurrentSensor.h"

CurrentSensor::CurrentSensor(int sensorID, int measurementPinNumber, double voltage) : Sensor(sensorID, measurementPinNumber){
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
  sprintf(message, "Sensor ID: %d, Current: %f, Voltage: %f", this->sensorID, this->getMeasurement(), this->getVoltage());
  return message;
}
