// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#include "LEDStrip.h"
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    21
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64

#define BRIGHTNESS          96

//#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

LEDStrip::LEDStrip(){
  this->gHue = 0;
  //delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(this->leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(this.leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

//void LEDStrip::nextPattern()
//{
  // add one to the current pattern number, and wrap around at the end
  //gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
//}

void LEDStrip::changeHue(){
  // do some periodic updates
  this->gHue++;// slowly cycle the "base color" through the rainbow
}

void LEDStrip::rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( this->leds, NUM_LEDS, this->gHue, 7);
  this->changeHue();
}

void LEDStrip::rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  this->rainbow();
  this->addGlitter(80);
  this->changeHue();
}

void LEDStrip::addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    this->leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
  this->changeHue();
}

void LEDStrip::confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( this->leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  this->leds[pos] += CHSV( this->gHue + random8(64), 200, 255);
  this->changeHue();
}

void LEDStrip::sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( this->leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  this->leds[pos] += CHSV( this->gHue, 255, 192);
  this->changeHue();
}

void LEDStrip::bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    this->leds[i] = ColorFromPalette(palette, this->gHue+(i*2), beat-this->gHue+(i*10));
  }
  this->changeHue();
}

void LEDStrip::juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( this->leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    //this->leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  this->changeHue();
}
