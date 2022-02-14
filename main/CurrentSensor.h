#include <Arduino.h>

#include "Sensor.h"

class CurrentSensor : public Sensor {
  protected:
    char *sensorName;
    int measurementPinNumber;
    double voltage;
  public:
    CurrentSensor(char *sensorName, int measurementPinNumber, double voltage);

    double getVoltage();
    String getMeasurementMessage();
};
