#pragma once
#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

class TemperatureSensor : public Sensor{

    public:
        TemperatureSensor(int sensorID, int measurementPinNumber);
        virtual ~TemperatureSensor();
        
        String getMeasurementMessage();
        SensorType isType();
        double getMeasurement();
};

#endif
