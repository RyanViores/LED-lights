#include <FastLED.h>

#define PIN 6
#define NUM_LEDS 10
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

void loop() {
  int Xval = analogRead(A1);
  int Yval = analogRead(A2);
  int Zval = analogRead(A3);

  Serial.print(Xval);
  Serial.print(", ");
  Serial.print(Yval);
  Serial.print(", ");
  Serial.print(Zval);
  Serial.println("");

  fill_rainbow(leds, NUM_LEDS, beat8(map(Xval,0,1023,2,75)), map(Yval,0,1023,1,15));

  FastLED.show();
}
