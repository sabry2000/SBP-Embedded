#include <Arduino.h>
#include "Sensor.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(char *sensorName, int measurementPinNumber) : Sensor(sensorName, measurementPinNumber){
}

TemperatureSensor::~TemperatureSensor(){
  
}

String TemperatureSensor::getMeasurementMessage(){
  char message[50];
  sprintf(message, "Temperature Sensor, Temperature: %f", this->getMeasurement());
  return message;
}

Sensor::SensorType TemperatureSensor::isType(){
  return SensorType::TEMPERATURE_SENSOR;
}

double TemperatureSensor::getMeasurement() {
  double sensorInput = analogRead(this->measurementPinNumber);   //read the analog sensor and store it
  double temperature = (double)sensorInput / 1024;              //find percentage of input reading
  temperature = temperature * 3.3;                              //multiply by 3.3V to get voltage
  temperature = temperature * 100;                              //Convert to degrees
  return temperature;
}
