#include "LEDStrip.h"
#include "LEDStripController.h"

const int BUTTON_PIN = 23;
const int LED_PIN = 17;

volatile int buttonState = 0;
int commandIndex = 0;

SemaphoreHandle_t lock;

TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t SystemRegulatorTaskHandle;

LEDStripController* ledStripController;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  LEDStrip ledStrip = LEDStrip();

  ledStripController = new LEDStripController(ledStrip);

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( lock == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    lock = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( lock ) != NULL )
      xSemaphoreGive( ( lock ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

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
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( lock, ( TickType_t ) 10 ) == pdTRUE )
    {
      buttonState = digitalRead(BUTTON_PIN);
      xSemaphoreGive( lock ); // Now free or "Give" the Serial Port for others.
    }
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}

void RegulateSystem( void * pvParameters ) {
  while (1) {
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( lock, ( TickType_t ) 10 ) == pdTRUE )
    {
      Serial.println(buttonState);
      if (buttonState == HIGH) {
        digitalWrite(LED_PIN, HIGH);
        ledStripController->displayPattern(commandIndex++);
      }
      xSemaphoreGive( lock ); // Now free or "Give" the Serial Port for others.
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_PIN, LOW);
  }
}

void loop() {}
