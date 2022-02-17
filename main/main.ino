#include <Arduino.h>
#include <Vector.h>

#include "esp32-mqtt.h"

#include "hardwareconfig.h"

#include "ControlledCurrentSensor.h"
#include "TemperatureSensor.h"
#include "Sensor.h"

TaskHandle_t IOTCommunicationTaskHandle;
TaskHandle_t ActionExecutionTaskHandle;

ControlledCurrentSensor *usb1;
ControlledCurrentSensor *usb2;
ControlledCurrentSensor *usb3;
ControlledCurrentSensor *usbC;
TemperatureSensor *tempSensor;

Sensor* SENSORS[5] = {};

void GCPCommunication( void * pvParameters ){
  // Sending data to server function
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  while (!mqttClient->connected()) {
    connect();
  }

  // ask every current sensor to publish their measurements to the cloud
  for (Sensor* snsr : SENSORS){
    String message = snsr->getMeasurementMessage();
    publishTelemetry(message);
    delay(1000);
  }
}

void ExecuteActions( void * pvParameters ){
    // TODO: discuss with Murad how to get data from server
}

void setup() {
  // initialize all different kinds of sensors using the pins defined in the hardwareconfig file
  usb1 = new ControlledCurrentSensor((char*)"USB1 Current Sensor", CURRENT_SENSOR_USB1, 5, USB1_CTRL);
  usb2 = new ControlledCurrentSensor((char*)"USB2 Current Sensor", CURRENT_SENSOR_USB2, 5, USB2_CTRL);
  usb3 = new ControlledCurrentSensor((char*)"USB3 Current Sensor", CURRENT_SENSOR_USB3, 5, USB3_CTRL);
  usbC = new ControlledCurrentSensor((char*)"USBC Current Sensor", CURRENT_SENSOR_USBC, 5, USBC_CTRL);
  tempSensor = new TemperatureSensor((char*)"Temperature Sensor", TEMPERATURE_SENSOR_PIN);

  // setup the data structures
  SENSORS[0] = usb1;
  SENSORS[1] = usb2;
  SENSORS[2] = usb3;
  SENSORS[3] = usbC;
  SENSORS[4] = tempSensor;

  for (Sensor* snsr : SENSORS){
    if (snsr->isType() == Sensor::SensorType::CONTROLLED_CURRENT_SENSOR){
          ControlledCurrentSensor* temp = (ControlledCurrentSensor*)snsr;
          temp->powerOn();
    }
  }

  analogReadResolution(ADC_RESOLUTION);
  setupCloudIoT();

  xTaskCreatePinnedToCore(
    GCPCommunication,             /* Task function. */
    "IOT Communication",           /* name of task. */
    10000,                        /* Stack size of task */
    NULL,                         /* parameter of the task */
    1,                            /* priority of the task */
    &IOTCommunicationTaskHandle,  /* Task handle to keep track of created task */
    0                             /* pin task to core 0 */
  );

  xTaskCreatePinnedToCore(
    ExecuteActions,                     /* Task function. */
    "Action Execution",                 /* name of task. */
    10000,                              /* Stack size of task */
    NULL,                               /* parameter of the task */
    1,                                  /* priority of the task */
    &ActionExecutionTaskHandle,         /* Task handle to keep track of created task */
    1                                   /* pin task to core 1 */
  );
}

void loop() {}
