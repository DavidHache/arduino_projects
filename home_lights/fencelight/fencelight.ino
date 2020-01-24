#include <FastLED.h>

#define NUM_LEDS 50
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define DATA_PIN    3
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120


uint8_t hue_lower = 0 ;
uint8_t hue_upper = 255 ;
int hue_up = 1;
int hue_loop_duration = 5;
int hue_delay_time;
uint8_t hue;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

CRGB leds[NUM_LEDS];

uint8_t intensity_lower = 100;
uint8_t intensity_upper = 230;
int intensity_up = 1;
int intensity_loop_duration = 2;
int intensity_delay_time;
uint8_t intensity;





void setup() { 
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  hue_delay_time = hue_loop_duration * (hue_upper - hue_lower);
  hue = hue_lower;
  intensity_delay_time = intensity_loop_duration * (intensity_upper - intensity_lower);
  intensity = intensity_upper;
  
  }




void loop() {

  //Setup fill color
  EVERY_N_MILLISECONDS(hue_delay_time) {
    if (hue_up == 1) {
      hue++;
      if (hue >= hue_upper) hue_up = 0;
    }
    else {
      hue--;
      if (hue <= hue_lower) hue_up = 1;
    }
  }
  EVERY_N_MILLISECONDS(intensity_delay_time) {
    if (intensity_up == 1) {
      intensity++;
      if (intensity >= intensity_upper) intensity_up = 0;
    }
    else {
      intensity--;
      if (intensity <= intensity_lower) intensity_up = 1;
    }
  }
  // Apply fill color.
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, intensity));

  // sinelon();
  
  addGlitter(10);
  

  
    
   
  
  
  FastLED.show();
}


void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  //fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 2, 0, NUM_LEDS-1 );
  leds[pos].fadeLightBy( 100 );
  leds[pos -1 ].fadeLightBy( 50 );
  leds[pos -2 ].fadeLightBy( 75 );
  leds[pos -3 ].fadeLightBy( 100 );
}


void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
