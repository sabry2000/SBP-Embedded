#pragma once
#ifndef CONTROLLEDCURRENTSENSOR_H
#define CONTROLLEDCURRENTSENSOR_H

#include "CurrentSensor.h"

class ControlledCurrentSensor : public CurrentSensor {
  private:
    int controlPinNumber;

   public:
    ControlledCurrentSensor(int sensorID, int measurementPinNumber, double voltage, int controlPinNumber);
    virtual ~ControlledCurrentSensor();

    SensorType isType();
    
    void powerOff();
    void powerOn();
    bool isPoweredOn();
};

#endif
