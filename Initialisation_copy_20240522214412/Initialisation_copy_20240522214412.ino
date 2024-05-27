#define LED_PIN D8    // пин ленты
#define NUMLEDS 60      // кол-во светодиодов
//#define BRIGHTNESS 50
#include "FastLED.h" 
#include "pitches.h"


CRGB leds[NUMLEDS];

uint8_t current_brightness = 50;
