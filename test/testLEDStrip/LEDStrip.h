#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#define FASTLED_RMT_MAX_CHANNELS 2
#define FASTLED_ESP32_FLASH_LOCK 1

#include <FastLED.h>

class LEDStrip {

  private:
    CRGB leds[];
    int gHue;


    void addGlitter( fract8 chanceOfGlitter);
    void changeHue();

  public:
    LEDStrip();
    void rainbow();
    void rainbowWithGlitter();
    void confetti();
    void sinelon();
    void bpm();
    void juggle();
    void displayPattern();
};

#endif
