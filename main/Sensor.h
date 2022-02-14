#include <Arduino.h>

class Sensor{
  public:
    virtual String getMeasurementMessage() = 0;
    double getMeasurement();
  protected:
    char *sensorName;
    int measurementPinNumber;
};
