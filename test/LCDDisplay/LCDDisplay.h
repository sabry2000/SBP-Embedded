#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal.h>

class LCDDisplay{
    private:
        LiquidCrystal *lcd;
    public:
        LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7);
        void write(String s);
};
#endif
