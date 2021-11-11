//import FastLED library, this is the best LED library for arduino IMO, but adafruits' Neopixel library is good too!
#include <FastLED.h>

//Define which pin is sending data to the lights
#define PIN 6

//Set the number of LEDs in our strip and how bright they will be. 
#define NUM_LEDS 10
#define BRIGHTNESS 128

//This defines our strip as an array of LEDs with size NUM_LEDS
//CRGB is a data type like "int" or "string" 
//CRGB takes three parameters (R, G, B)
//CRGB(255, 0, 0) is pure red!
CRGB leds[NUM_LEDS];


void setup() {
    delay( 3000 ); // power-up safety delay
    //These are initial set up commands for our specific strip, don't worry about them
    FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setTemperature(SodiumVapor);
    Serial.begin(9600);

    //declare our potentiometers as input so we can read from them. 
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
}

void loop() {
  //These variables represent the readings from our potentiometers
  int Xval = analogRead(A0);
  int Yval = analogRead(A1);
  int Zval = analogRead(A2);

  //Serial monitor commands can help us figure out what's going on in real time. 
  Serial.print(Xval);
  Serial.print(", ");
  Serial.print(Yval);
  Serial.print(", ");
  Serial.print(Zval);
  Serial.println("");

  //Our potentiometers give us values from 0 to 1023
  int R = map(Xval, 0, 1023, 0, 255);
  int G = map(Yval, 0, 1023, 0, 255);
  int B = map(Zval, 0, 1023, 0, 255);

  //Fill the LED strip solid with the colors specified by the potentiometers
  fill_solid(leds, NUM_LEDS, CRGB(R,G,B));

  FastLED.show();
}
