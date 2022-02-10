#include <Arduino.h>

class Sensor{
  public:
    String sensorName;
    int pinNumber;
};

CurrentSensor::CurrentSensor(String sensorName, int pinNumber){
  this->sensorName = sensorName;
  this->pinNumber = pinNumber;

  pinMode(pinNumber, INPUT);
}

double CurrentSensor::getCurrent(){
  return analogRead(pinNumber);
}
