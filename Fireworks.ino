#include <FastLED.h>

#define PIN 6
#define NUM_LEDS 15
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setTemperature(SodiumVapor);
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
}

void loop(){
  int Xval = analogRead(A1);
  int Yval = analogRead(A2);
  int Zval = analogRead(A3);

  Serial.print(Xval);
  Serial.print(", ");
  Serial.print(Yval);
  Serial.print(", ");
  Serial.print(Zval);
  Serial.println("");

  int sat = map(Xval, 0, 1023, 0, 255);
  int faderate = map(Yval, 0, 1023, 0, 100);
  int pixels = map(Zval, 0, 1023, 1, 8);
   int pxs_to_light[pixels];
   int litcount = 0;
   
   for(int i=0;i<NUM_LEDS;i++){
      if(leds[i] != CRGB(0,0,0)){
        litcount++;
      }
   }
   
   for (int i = 0; i<(pixels-litcount); i++){ 
      pxs_to_light[i]=random(0,(NUM_LEDS-1));
      leds[pxs_to_light[i]].setHSV(random(0,255), sat, 255);
      FastLED.delay(faderate/4);
   }
   
   fadeToBlackBy(leds, NUM_LEDS, 15);
   FastLED.delay(faderate);
   FastLED.show();
}
