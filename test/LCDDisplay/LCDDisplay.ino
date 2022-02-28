#include "LCDDisplay.h"
#include "LCDDisplayController.h"

const int BUTTON_PIN = 23;
const int LED_PIN = 22;

const int D7 = 21;
const int D6 = 19;
const int D5 = 18;
const int D4 = 5;

const int E = 17;
const int RS = 16;

volatile int buttonState = 0;
int command = 0;

TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t SystemRegulatorTaskHandle;

LCDDisplayController* lcdDisplayController;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  LCDDisplay lcdDisplay = LCDDisplay(RS, E, D4, D5, D6, D7);

  lcdDisplayController = new LCDDisplayController(lcdDisplay);

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

void MonitorSystem( void * pvParameters ) {
  while (1) {
    buttonState = digitalRead(BUTTON_PIN);
    delay(1);
  }
}

void RegulateSystem( void * pvParameters ) {
  while (1) {
    Serial.println(buttonState);
    if (buttonState == HIGH) {
      delay(1000);
      digitalWrite(LED_PIN, HIGH);
      lcdDisplayController->displayNumber(command++);
      delay(1000);
    }
    digitalWrite(LED_PIN, LOW);
    delay(1);
  }
}

void loop() {}
