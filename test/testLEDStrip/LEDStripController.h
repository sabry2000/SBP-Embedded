#ifndef LEDSTRIPCCONTROLLER_H
#define LEDSTRIPCCONTROLLER_H

#include "LEDStrip.h"

class LEDStripController {
    private:
        uint8_t gCurrentPatternNumber;
        LEDStrip ledStrip;
    public:
        LEDStripController(LEDStrip ledStrip);
        void displayPattern(int commandIndex);
};

#endif
