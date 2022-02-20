#pragma once
#ifndef SENSOR_H
#define Sensor_H

// abstract sensor class
class Sensor{
  public:
    enum SensorType{
      CONTROLLED_CURRENT_SENSOR,
      CURRENT_SENSOR,
      TEMPERATURE_SENSOR
    };

    virtual String getMeasurementMessage() = 0;
    virtual SensorType isType() = 0;
    double getMeasurement();
    virtual ~Sensor() = 0;
  
  protected:
    int sensorID;
    int measurementPinNumber;

    Sensor(int sensorID, int measurementPinNumber);
};

#endif
