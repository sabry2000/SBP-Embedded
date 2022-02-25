#include <Arduino.h>
#include <Vector.h>

#include "hardware_config.h"
#include "sensor_config.h"

#include "Sensor.h"
#include "TemperatureSensor.h"
#include "CurrentSensor.h"
#include "ControlledCurrentSensor.h"

#include "SystemController.h"

TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t SystemRegulatorTaskHandle;

SystemController *sysController;

void MonitorSystem( void * pvParameters ){
  while(1){
    sysController->monitorSystem();
  }
}

void RegulateSystem( void * pvParameters ){
  while(1){
    sysController->regulateSystem();
  }
}

void setup() {
  analogReadResolution(ADC_RESOLUTION);

  // initialize all different kinds of sensors using the pins defined in the hardware_config and sensor_config file
  CurrentSensor cc = CurrentSensor(CHARGE_CONTROLLER_CURRENT_SENSOR_ID, CHARGE_CONTROLLER_CURRRENT_SENSOR_PIN, 5);
  ControlledCurrentSensor usb1 = ControlledCurrentSensor(USB1_CURRENT_SENSOR_ID, USB1_CURRENT_SENSOR_PIN, 5, USB1_CTRL_PIN);
  ControlledCurrentSensor usb2 = ControlledCurrentSensor(USB2_CURRENT_SENSOR_ID, USB2_CURRENT_SENSOR_PIN, 5, USB2_CTRL_PIN);
  ControlledCurrentSensor usb3 = ControlledCurrentSensor(USB3_CURRENT_SENSOR_ID, USB3_CURRENT_SENSOR_PIN, 5, USB3_CTRL_PIN);
  ControlledCurrentSensor usbC = ControlledCurrentSensor(USB4_CURRENT_SENSOR_ID, USBC_CURRENT_SENSOR_PIN, 5, USBC_CTRL_PIN);
  TemperatureSensor tempSensor = TemperatureSensor(TEMPERATURE_SENSOR_ID, TEMPERATURE_SENSOR_PIN);

  // setup the data structures
  Vector<Sensor*> SENSORS;
  SENSORS.push_back(&cc);
  SENSORS.push_back(&usb1);
  SENSORS.push_back(&usb2);
  SENSORS.push_back(&usb3);
  SENSORS.push_back(&usbC);
  SENSORS.push_back(&tempSensor);

  sysController = new SystemController(SENSORS);

  xTaskCreatePinnedToCore(
    MonitorSystem,                      /* Task function. */
    "System Monitoring Task",           /* name of task. */
    10000,                              /* Stack size of task */
    NULL,                               /* parameter of the task */
    1,                                  /* priority of the task */
    &SystemMonitorTaskHandle,           /* Task handle to keep track of created task */
    0                                   /* pin task to core 0 */
  );

  xTaskCreatePinnedToCore(
    RegulateSystem,                     /* Task function. */
    "System Regulating Task",           /* name of task. */
    10000,                              /* Stack size of task */
    NULL,                               /* parameter of the task */
    1,                                  /* priority of the task */
    &SystemRegulatorTaskHandle,         /* Task handle to keep track of created task */
    1                                   /* pin task to core 1 */
  );
}

void loop() {}
