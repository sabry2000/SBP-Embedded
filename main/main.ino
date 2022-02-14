#include "esp32-mqtt.h"
#include <Arduino.h>

#include "ControlledCurrentSensor.h"

#include "hardwareconfig.h"
#include <Vector.h>

TaskHandle_t SendToServerTaskHandle;
TaskHandle_t ReceiveFromServerTaskHandle;

ControlledCurrentSensor *usb1;
ControlledCurrentSensor *usb2;
ControlledCurrentSensor *usb3;
ControlledCurrentSensor *usbC;

Vector<ControlledCurrentSensor> CURRENT_SENSORS;

void SendToServer( void * pvParameters ){
  // Sending data to server function
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  while (!mqttClient->connected()) {
    connect();
  }

  // ask every current sensor to publish their measurements to the cloud
  for (ControlledCurrentSensor cs : CURRENT_SENSORS){
    String message = cs.getMeasurementMessage();
    publishTelemetry(message);
    delay(1000);
  }
}

void ReceiveFromServer( void * pvParameters ){
    // TODO: discuss with Murad how to get data from server
}

void setup() {
  // initialize 4 controlled current sensors using the pins defined in the hardwareconfig file
  usb1 = new ControlledCurrentSensor((char*)"USB1 Current Sensor", CURRENT_SENSOR_USB1, 5, USB1_CTRL);
  usb2 = new ControlledCurrentSensor((char*)"USB2 Current Sensor", CURRENT_SENSOR_USB2, 5, USB2_CTRL);
  usb3 = new ControlledCurrentSensor((char*)"USB3 Current Sensor", CURRENT_SENSOR_USB3, 5, USB3_CTRL);
  usbC = new ControlledCurrentSensor((char*)"USBC Current Sensor", CURRENT_SENSOR_USBC, 5, USBC_CTRL);

  // setup the data structures
  CURRENT_SENSORS.push_back(*usb1);
  CURRENT_SENSORS.push_back(*usb2);
  CURRENT_SENSORS.push_back(*usb3);
  CURRENT_SENSORS.push_back(*usbC);

  for (ControlledCurrentSensor cs : CURRENT_SENSORS){
    cs.powerOn();
  }

  analogReadResolution(ADC_RESOLUTION);
  setupCloudIoT();

  xTaskCreatePinnedToCore(
    SendToServer,                 /* Task function. */
    "Send To Server",             /* name of task. */
    10000,                        /* Stack size of task */
    NULL,                         /* parameter of the task */
    1,                            /* priority of the task */
    &SendToServerTaskHandle,      /* Task handle to keep track of created task */
    0                             /* pin task to core 0 */
  );

  xTaskCreatePinnedToCore(
    ReceiveFromServer,                  /* Task function. */
    "Receive From Server",              /* name of task. */
    10000,                              /* Stack size of task */
    NULL,                               /* parameter of the task */
    1,                                  /* priority of the task */
    &ReceiveFromServerTaskHandle,       /* Task handle to keep track of created task */
    1                                   /* pin task to core 1 */
  );
}

void loop() {}
