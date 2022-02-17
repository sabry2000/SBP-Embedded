#pragma once
#ifndef SENSORMONITOR_H
#define SENSORMONITOR_H

#include <Vector.h>
#include "Sensor.h"

class SensorMonitor{
    public:
        Sensor* sensors;
        
        SensorMonitor(Sensor* sensors);
        ~SensorMonitor();

        void monitor();
};

#endif
