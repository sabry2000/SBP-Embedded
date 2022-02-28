#include <FastLED.h>
#include "LEDStripController.h"
#include "LEDStrip.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


LEDStripController::LEDStripController(LEDStrip ledStrip){
    // List of patterns to cycle through.  Each is defined as a separate function below.
    this->gCurrentPatternNumber = 0; // Index number of which pattern is current
    this->ledStrip = ledStrip;

    //void LEDStrip (*foo)();
    //foo = &((this->ledStrip).rainbow);
    
    //this->gPatterns[0] = foo;
}

void LEDStripController::displayPattern(int commandIndex){
  commandIndex = commandIndex % 6;
  
  switch(commandIndex) {
    case 0:
      (this->ledStrip).rainbow();break;
    case 1:
      (this->ledStrip).rainbowWithGlitter();break;
    case 2:
      (this->ledStrip).confetti();break;
    case 3:
      (this->ledStrip).sinelon();break;
    case 4:
      (this->ledStrip).bpm();break;
    case 5:
      (this->ledStrip).juggle();break;
  }
      
  FastLED.show();  
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 
  
  //this->gCurrentPatternNumber = (this->gCurrentPatternNumber + 1) % ARRAY_SIZE( this->gPatterns);
  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}
