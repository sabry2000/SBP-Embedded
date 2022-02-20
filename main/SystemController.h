#pragma once
#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "Sensor.h"
#include <Vector.h>

class SystemController{
    private:
        Vector<Sensor*> sensors;
        bool isOnline;
        
        //void turnOnControlledCurrentSensors(int sensorID);
        //void turnOffControlledCurrentSensors(int sensorID);
        void turnOnAllControlledCurrentSensors();
        void turnOffAllControlledCurrentSensors();
        bool isConnected();
    public:
        
        SystemController(Vector<Sensor*> sensors);
        ~SystemController();

        void monitorSystem();
        void regulateSystem();
};

#endif
