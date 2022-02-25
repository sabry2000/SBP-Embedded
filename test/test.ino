const int BUTTON_PIN = 23;
const int LED_PIN = 22;
int buttonState = 0;
unsigned long previousTime = 0;

TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t SystemRegulatorTaskHandle;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  //Serial.begin(9600);

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

void MonitorSystem( void * pvParameters ){
  while(1){
      buttonState = digitalRead(BUTTON_PIN);
  }
}

void RegulateSystem( void * pvParameters ){
  while(1){
    if (buttonState == HIGH) {
      delay(1000);     
      digitalWrite(LED_PIN,HIGH);
      delay(1000);
    }else{
      digitalWrite(LED_PIN,LOW);
    }
  }
  //Serial.println(buttonState);
}

void loop() {}
