#ifndef LEDSTRIPCCONTROLLER_H
#define LEDSTRIPCCONTROLLER_H

#include "LEDStrip.h"

#define FRAMES_PER_SECOND  120


class LEDStripController {
    private:
        uint8_t gCurrentPatternNumber;
        LEDStrip ledStrip;
    public:
        LEDStripController(LEDStrip ledStrip);
        void displayPattern(int commandIndex);
};

#endif
