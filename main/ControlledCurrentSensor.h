#include "CurrentSensor.h"

class ControlledCurrentSensor : public CurrentSensor {
  private:
    int controlPinNumber;

   public:
    ControlledCurrentSensor(char *sensorName, int measurementPinNumber, double voltage, int controlPinNumber);
    void powerOff();
    void powerOn();
    bool isPoweredOn();
};
