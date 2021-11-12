#include <FastLED.h>

#define PIN 6
#define NUM_LEDS 10
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

int count = 0;
void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    CHSV hsv(120, 255, 255); // pure blue in HSV Rainbow space
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    //fill_solid(leds, NUM_LEDS, rgb);
   
}
//Snake description
//control the hue of the snake with a pot as the light moves down the strip
//if the hue of the snake matches the hue of the snake when it reaches the head, make the snake longer
//if it doesn't match, lose a life

void loop() {
   int lives =3;
   int snakesize=1;
   int snakehue;

   while (lives > 0){
     int food_hue = random(0,255);
     for(int i=NUM_LEDS;i>(snakesize-1);i--){
        leds[i].setHSV(food_hue, 255, 255);
        leds[i+1].setHSV(0,0,0);
        
        for (int j=0; j<10;j++){
          snakehue = map(analogRead(A1),0,1000,0,255);
       
          fill_solid(leds, snakesize, CHSV(snakehue, 255, 255));
          FastLED.show();
       
          int delaytime = 40;
          FastLED.delay(delaytime);
        //FastLED.show();
        }
        if(i == snakesize){
            if(snakehue < (food_hue+15) && (food_hue-15)<snakehue){
              snakesize+=1;
            }
            else{
              lives--;
              fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
              FastLED.delay(150);
              fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
            }
          }
     }

   }
      fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
   FastLED.delay(550);
   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
   FastLED.delay(550);
   fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
   FastLED.delay(550);
   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
   FastLED.delay(550);
   fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
   FastLED.delay(550);
   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
}
