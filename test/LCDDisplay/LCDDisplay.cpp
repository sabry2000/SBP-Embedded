#include <HardwareSerial.h>
#include <LiquidCrystal.h>
#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7){
    this->lcd = new LiquidCrystal(rs, enable, d4, d5, d6, d7);
    this->lcd->begin(16,2);
    this->lcd->print("LCD Initialized");
}
void LCDDisplay::write(String s){
    this->lcd->clear();
    this->lcd->setCursor(0, 1);
    this->lcd->print(s);
}
