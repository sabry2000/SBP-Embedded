#pragma once
#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

class TemperatureSensor : public Sensor{

    public:
        TemperatureSensor(char *sensorName, int measurementPinNumber);
        virtual ~TemperatureSensor();
        
        String getMeasurementMessage();
        SensorType isType();
        double getMeasurement();
};

#endif
