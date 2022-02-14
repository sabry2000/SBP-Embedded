#include <Arduino.h>
#include "Sensor.h"

double Sensor::getMeasurement() {
  return analogRead(this->measurementPinNumber);
}
