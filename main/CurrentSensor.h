#pragma once
#ifndef CURRENTSENSOR_H
#define CURRENTSENSOR_H

#include "Sensor.h"

class CurrentSensor : public Sensor {
  private:
    double voltage;
  public:
    CurrentSensor(char *sensorName, int measurementPinNumber, double voltage);
    virtual ~CurrentSensor();

    String getMeasurementMessage();
    SensorType isType();
    double getMeasurement();
    double getVoltage();
};

#endif
