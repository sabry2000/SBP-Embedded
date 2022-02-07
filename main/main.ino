#include "esp32-mqtt.h"
#include <Arduino.h>

const int USB1_CTRL = 16;
const int USB2_CTRL = 17;
const int USB3_CTRL = 5;
const int USBC_CTRL = 18;

const int CURRENT_SENSE_X = 36;
const int CURRENT_SENSE_Y = 39;
const int CURRENT_SENSE_W = 34;
const int CURRENT_SENSE_Z = 35;

int[4] USB_CTRLS;
int[4] CURRENT_SENSORS;

const int ADC_RESOLUTION = 12; // The bit resolution of the ADC

int NUMBER_OF_SENSORS;

void getCurrentMeasurements(){
  int measurements[NUMBER_OF_CURRENT_SENSORS];

  for (int i = 0; i < NUMBER_OF_CURRENT_SENSORS; i++){
    measurements[i] = analogRead(CURRENT_SENSORS[i]);
  }
}

void setup() {
  // put your setup code here, to run once:
  USB_CTRLS = [USB1_CTRL, USB2_CTRL, USB3_CTRL, USBC_CTRL];
  CURRENT_SENSORS = [CURRENT_SENSE_X, CURRENT_SENSE_Y, CURRENT_SENSE_W, CURRENT_SENSE_Z];

  NUMBER_OF_CURRENT_SENSORS = sizeof CURRENT_SENSORS/ sizeof CURRENT_SENSORS[0];

  for (int usb_ctrl : USB_CTRLS)
  {
    pinMode(usb_ctrl, OUTPUT);
  }
  
  for (int current_sensor : CURRENT_SENSORS)
  {
    pinMode(current_sensor, INPUT);
  }

  analogReadResolution(ADC_RESOLUTION)
  setupCloudIoT();
}

void loop() {
  // put your main code here, to run repeatedly:
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!mqttClient->connected()) {
    connect();
  }

  delay(1000);
  getCurrentMeasurements();
}
