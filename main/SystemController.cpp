#include <Arduino.h>
#include <Vector.h>

#include "Sensor.h"
#include "SystemController.h"
#include "ControlledCurrentSensor.h"
#include "esp32-mqtt.h"

SystemController::SystemController(Vector<Sensor*> sensors){
    this->sensors = sensors;
    this->isOnline = false;

    setupCloudIoT();
}

//TODO
void SystemController::regulateSystem(){
    this->turnOffAllControlledCurrentSensors();
    this->turnOnAllControlledCurrentSensors();
    
    if(this->isConnected()){

    }else{

    }

}

void SystemController::monitorSystem(){

    mqtt->loop();   // Checks if the JWT expired and disconnects
    delay(10);      // <- fixes some issues with WiFi stability

    if (!mqttClient->connected()) {
        this->isOnline = false;
        connect();
    }
    this->isOnline = true;
    
    // ask every current sensor to publish their measurements to the cloud
    for (Sensor* snsr : this->sensors){
        String message = snsr->getMeasurementMessage();
        publishTelemetry(message);
        delay(1000);
    }

    String commandIndex = "";
}

void SystemController::turnOffAllControlledCurrentSensors(){
    for (Sensor* snsr : this->sensors){
        if (snsr->isType() == Sensor::SensorType::CONTROLLED_CURRENT_SENSOR){
            ((ControlledCurrentSensor*)snsr)->powerOff();
        }
    }
}

void SystemController::turnOnAllControlledCurrentSensors(){
    for (Sensor* snsr : this->sensors){
        if (snsr->isType() == Sensor::SensorType::CONTROLLED_CURRENT_SENSOR){
            ((ControlledCurrentSensor*)snsr)->powerOn();
        }
    }
}

bool SystemController::isConnected(){
    return isOnline;
}