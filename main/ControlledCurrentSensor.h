#include <Arduino.h>
#include "CurrentSensor.h"

class ControlledCurrentSensor : public CurrentSensor {
  private:
    int controlPinNumber;

   public:
    ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage, int controlPinNumber);
    void powerOff();
    void powerOn();
    bool isPoweredOn();
};

ControlledCurrentSensor::ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage, int controlPinNumber) :  CurrentSensor(sensorName, measurementPinNumber, voltage) {
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
  return (this->getMeasurement() > 0.5);
}
