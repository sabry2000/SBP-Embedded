#ifndef LEDSTRIP_H
#define LEDSTRIP_H

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
};

#endif
