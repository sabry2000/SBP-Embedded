#ifndef LCDDISPLAYCONTROLLER_H
#define LCDDISPLAYCONTROLLER_H

#include "LCDDisplay.h"

class LCDDisplayController{
    private:
        LCDDisplay* lcd;
    public:
        LCDDisplayController(LCDDisplay lcd);
        void displayNumber(int num);
};
#endif
