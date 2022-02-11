#include "esp32-mqtt.h"
#include <Arduino.h>

#include "ControlledCurrentSensor.h"

#include "hardwareconfig.h"

ControlledCurrentSensor *usb1;
ControlledCurrentSensor *usb2;
ControlledCurrentSensor *usb3;
ControlledCurrentSensor *usbC;

const int NUMBER_OF_CURRENT_SENSORS = 4;
ControlledCurrentSensor CURRENT_SENSORS[NUMBER_OF_CURRENT_SENSORS];

void setup() {
  // initialize 4 controlled current sensors using the pins defined in the hardwareconfig file
  usb1 = new ControlledCurrentSensor((char*)"USB1 Current Sensor", CURRENT_SENSOR_USB1, 5, USB1_CTRL);
  usb2 = new ControlledCurrentSensor((char*)"USB2 Current Sensor", CURRENT_SENSOR_USB2, 5, USB2_CTRL);
  usb3 = new ControlledCurrentSensor((char*)"USB3 Current Sensor", CURRENT_SENSOR_USB3, 5, USB3_CTRL);
  usbC = new ControlledCurrentSensor((char*)"USBC Current Sensor", CURRENT_SENSOR_USBC, 5, USBC_CTRL);

  // setup the data structures
  CURRENT_SENSORS[0] = *usb1;
  CURRENT_SENSORS[1] = *usb2;
  CURRENT_SENSORS[2] = *usb3;
  CURRENT_SENSORS[3] = *usbC;

  for (ControlledCurrentSensor cs : CURRENT_SENSORS){
    cs.powerOn();
  }

  analogReadResolution(ADC_RESOLUTION);
  setupCloudIoT();
}

void loop() {
  //
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
