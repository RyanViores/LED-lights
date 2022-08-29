#include <FastLED.h>

#define PIN 6
#define NUM_LEDS 15
#define BRIGHTNESS 128

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
  int Xval = analogRead(A0);
  int Yval = analogRead(A1);
  int Zval = analogRead(A2);

  Serial.print(Xval);
  Serial.print(", ");
  Serial.print(Yval);
  Serial.print(", ");
  Serial.print(Zval);
  Serial.println("");

  int bandSize = map(Xval,0,1000,1,75);
  int BPM = map(Yval,0,1000,1,40);

  fill_rainbow(leds, NUM_LEDS, beat8(BPM, bandSize));

  FastLED.show();
}
