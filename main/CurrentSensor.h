#include <Arduino.h>

class CurrentSensor {
  protected:
    char *sensorName;
    int measurementPinNumber;
    double voltage;

    CurrentSensor();

  public:
    CurrentSensor(char *sensorName, int measurementPinNumber, double voltage);

    double getCurrent();
    double getVoltage();
    String getMeasurementMessage();
};

CurrentSensor::CurrentSensor() {}

CurrentSensor::CurrentSensor(char *sensorName, int measurementPinNumber, double voltage) {
  this->sensorName = sensorName;
  this->measurementPinNumber = measurementPinNumber;
  this->voltage = voltage;

  pinMode(measurementPinNumber, INPUT);
}

double CurrentSensor::getCurrent() {
  return analogRead(this->measurementPinNumber);
}

double CurrentSensor::getVoltage() {
  return this->voltage;
}

String CurrentSensor::getMeasurementMessage(){
  char message[50];
  sprintf(message, "Current Sensor Name: %s, Current: %f, Voltage: %f", this->sensorName, this->getCurrent(), this->getVoltage());
  return message;
}
