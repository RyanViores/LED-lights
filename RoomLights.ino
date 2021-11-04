#include <FastLED.h>

#define PIN 6
#define NUM_LEDS 300
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
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
}

void loop() {
  int mode = analogRead(A0);
  mode = map(mode, 0, 1023, 0, 10);
  
  int Xval = analogRead(A1);
  int Yval = analogRead(A2);
  int Zval = analogRead(A3);

  Serial.print(mode);
  Serial.print(", ");
  Serial.print(Xval);
  Serial.print(", ");
  Serial.print(Yval);
  Serial.print(", ");
  Serial.print(Zval);
  Serial.println("");

  delay(10);

  //RGB Mode 
  if(mode == 0){
       RGBmode(Xval, Yval, Zval);
  }
  //Rainbow Pulse, control fade time and change
  else if(mode == 1){
       //rainbowPulse(Xval, Yval);
       //paint(Xval, Yval, Zval, Wval, mode);
       fill_solid(leds,150,CRGB(0,0,0));
  }
  //Pulse, control Hue and fade time
  else if(mode == 2){
      pulse(Xval, Yval);
  }
  //Rainbow 
  else if(mode == 3){ 
    fill_rainbow(leds, NUM_LEDS, beat8(map(Xval,0,1023,2,75)), map(Yval,0,1023,1,15));
  }
  //Fireworks control saturation, time, number
  else if(mode == 4){
    fireworks(Xval, Yval, Zval);
  }
  //Twinkle
  else if(mode == 5){
    rainbowWalk();
  }
  //Theater Chase Control Hue1, Hue2, block size, number of blocks
  else if(mode == 6){
    TheaterChase(Xval, Yval, Zval);
  }
  //Snake, try to match hue
  else{
      //fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      //snake(Xval, mode);
      fill_solid(leds,150,CRGB(0,0,0));
  }


  FastLED.show();
}

//Set strip to solid RGB color, Pots control color
void RGBmode(int Xval, int Yval, int Zval){
  int R = map(Xval, 0, 1023, 0, 255);
  int G = map(Yval, 0, 1023, 0, 255);
  int B = map(Zval, 0, 1023, 0, 255);
  
  fill_solid(leds, NUM_LEDS, CRGB(R,G,B));
}



//set a color, determine how quickly it fades to black
//might need a delay
void pulse(int hue, int BPM){
    hue = map(hue, 0, 1023, 0, 255);
    BPM = map(BPM, 0, 1023, 40, 40);
    int pause = 60000/BPM;
    CHSV hsv(hue, 255, 255); // pure blue in HSV Rainbow space
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
//
//    int faderate = 128;
//    fadeToBlackBy(leds, NUM_LEDS, faderate);
//   pause = map(pause, 0, 1023, 0, 50);
    fill_solid(leds, NUM_LEDS, rgb);
    FastLED.delay(pause/2);
    FastLED.show();
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.delay(pause/2);
    FastLED.show();
    
    
    CRGB lastcolor = leds[1];
    
//    if (lastcolor == CRGB(0,0,0)){
//      fill_solid(leds, NUM_LEDS, rgb);
//    } 
}

void rainbowPulse(int change, int pause){
    change = map(change, 0, 1023, 0, 16);
    CHSV HSVchange(change, 255, 255);
    CRGB RGBchange;

    hsv2rgb_rainbow(HSVchange, RGBchange);
    
    CRGB rgb;

    int faderate = 20;
    fadeToBlackBy(leds, NUM_LEDS, faderate);
    pause = map(pause, 0, 1023, 0, 50);
    FastLED.delay(pause);
    FastLED.show();
    
    CRGB lastcolor = leds[1];
    
    if (lastcolor == CRGB(0,0,0)){
      FastLED.delay(100);
      rgb += RGBchange;
      fill_solid(leds, NUM_LEDS, rgb);
    } 
}

void fireworks(int pixels, int sat, int faderate){
   sat = map(sat, 0, 1023, 0, 255);
   faderate = map(faderate, 0, 1023, 0, 100);
   pixels = map(pixels, 0, 1023, 1, 150);
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
   //FastLED.show();
   FastLED.delay(faderate);
}

void TheaterChase(int hue1,int hue2,int blocksize ) {
    blocksize = 10;
    
    hue2 = map(hue2,0,1023,0,255);
    hue1 = map(hue1,0,1023,0,255);
    for(int j = 0; j < blocksize; j++){
      
      for (int i=0; i<NUM_LEDS; i+=blocksize){
        
        leds[i+j].setHSV(hue1,255,255);
      }
      int mode = map(analogRead(A0), 0, 1023, 0, 10);
      if (mode != 6){
        return;
      }
      FastLED.delay(300);
      FastLED.show();
      for (int i=0;i<NUM_LEDS; i+=blocksize){
        leds[i+j].setHSV(0,0,0);
      }
      fill_solid(leds, NUM_LEDS, CHSV(hue2, 255, 255));
    }
    
//    for (int q=0; q < blocksize; q++) {
//      for (int i=0; i < NUM_LEDS; i=i+blocksize) {
//        leds[i+q].setHSV(hue1,255,255);    //turn every "blocksize" pixel on
//        Serial.println(i+q);
//      }
//      int mode = map(analogRead(A0), 0, 1023, 0, 10);
//      if (mode != 6){
//        return;
//      }
//
//      //FastLED.delay();
//      FastLED.show();
//      for (int i=6; i < NUM_LEDS; i=i+blocksize) {
//        //strip.setPixelColor(i+q-(blocksize-3), color2);        //turn every third pixel off
//        leds[i+q-(blocksize-3)].setHSV(hue2,255,255);
//        Serial.println(i+q-(blocksize-3));
//      }
//    }
}

void rainbowWalk() {
  //size of each rainbow
  //between 10 and 50 is best
  int blocksize = 10;
  for(int j=0; j<NUM_LEDS; j++){
    for(int i=0; i<NUM_LEDS; i++) {
      //selector checker
      int selector = map(analogRead(A0),0,1023,0,10);
      if(selector != 5){
        return;
      }
      
      // 255 / (strips/block * px/strip)
      int hue = (255/blocksize) * (i+j+1);
      hue = hue % 255;
      leds[i].setHSV(hue, 255, 255);
      //only write to pixels 10+
      
    }
    FastLED.delay(200);
    FastLED.show();
  }
}

//Paint the strip using the pots, use the first pot to select the pixel, second to select the hue 
//the last pot is an eraser/fill, must be off to paint in a non solid color

//void paint(int pos, int hue, int brushSize, int eraser, int mode){
//    if(mode == 1){
//      pos = map(pos, 0, 1023, 0, NUM_LEDS);
//      hue = map(hue, 0, 1023, 0, 255);
//      brushSize = map(brushSize, 0, 1023, 0, 15);
//      eraser = map(eraser, 0, 1023, 0, 2);
//    
//      if (eraser==2){
//        fill_solid(leds, NUM_LEDS, (0,0,0));
//      }
//      else if (eraser==1){
//        CHSV hsv(hue, 255, 255); // pure blue in HSV Rainbow space
//        CRGB rgb;
//        hsv2rgb_rainbow(hsv, rgb);
//        fill_solid(leds, NUM_LEDS, rgb);
//      }
//      else if (eraser==0){
//        for (int i=0; i<NUM_LEDS; i++){
//          if(i = pos){
//            leds[i].setHSV(hue, 255, BRIGHTNESS);
//          }
//        }
//      }
//    }
//  }


//void snake(int snakehue, int mode){
//   int lives =3;
//   int snakesize=1;
//
//   while (lives > 0 && mode == 7){
//     int food_hue = random(0,255);
//     for(int i=NUM_LEDS;i>(snakesize-1);i--){
//        leds[i].setHSV(food_hue, 255, 255);
//        leds[i+1].setHSV(0,0,0);
//        snakehue = map(analogRead(A1),0,1000,0,255);
//        if(i == snakesize){
//          if(snakehue < (food_hue+10) && (food_hue-10)<snakehue){
//            snakesize+=3;
//          }
//          else{
//            lives--;
//            fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
//            FastLED.delay(150);
//            fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
//          }
//        }
//        fill_solid(leds, snakesize+1, CHSV(snakehue, 255, 255));
//        FastLED.show();
//     
//        int delaytime = 50 - (snakesize);
//        FastLED.delay(delaytime);
//        //FastLED.show();
//     }
//
//   }
//      fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
//   FastLED.delay(550);
//   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
//   FastLED.delay(550);
//   fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
//   FastLED.delay(550);
//   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
//   FastLED.delay(550);
//   fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
//   FastLED.delay(550);
//   fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
//}

//void pulse(int hue, int pause){
//    hue = map(hue, 0, 1023, 0, 255);
//    CHSV hsv(hue, 255, 255); // pure blue in HSV Rainbow space
//    CRGB rgb;
//    hsv2rgb_rainbow(hsv, rgb);
//
//    int faderate = 20;
//    fadeToBlackBy(leds, NUM_LEDS, faderate);
//    pause = map(pause, 0, 1023, 0, 50);
//    FastLED.delay(pause);
//    FastLED.show();
//    
//    CRGB lastcolor = leds[1];
//    
//    if (lastcolor == CRGB(0,0,0)){
//      FastLED.delay(100);
//      fill_solid(leds, NUM_LEDS, rgb);
//    } 
//}
  
