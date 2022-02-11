#include <Arduino.h>
#include "CurrentSensor.h"

class ControlledCurrentSensor : public CurrentSensor {
  private:
    int controlPinNumber;

   public:
    ControlledCurrentSensor();
    ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage);

    ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage, int controlPinNumber);
    void powerOff();
    void powerOn();
    bool isPoweredOn();
};

ControlledCurrentSensor::ControlledCurrentSensor(): CurrentSensor() {}

ControlledCurrentSensor::ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage) : CurrentSensor(sensorName, measurementPinNumber, voltage) {}

ControlledCurrentSensor::ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage, int controlPinNumber) :  ControlledCurrentSensor(sensorName, measurementPinNumber, voltage) {
  this->controlPinNumber = controlPinNumber;

  pinMode(controlPinNumber, OUTPUT);

  this->powerOff();
}

void ControlledCurrentSensor::powerOff() {
  digitalWrite(this->controlPinNumber, LOW);
}

void ControlledCurrentSensor::powerOn() {
  digitalWrite(this->controlPinNumber, HIGH);
}

bool ControlledCurrentSensor::isPoweredOn(){
  return (this->getCurrent() > 0.5);
}
