#include "LCDDisplayController.h"
#include "LCDDisplay.h"

LCDDisplayController::LCDDisplayController(LCDDisplay lcd){
    this->lcd = &lcd;
}
void LCDDisplayController::displayNumber(int num){
    String numString = String(num);
    (this->lcd)->write(numString);
}
