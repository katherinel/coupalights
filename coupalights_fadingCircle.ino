#include <Adafruit_WS2801.h>

#include "SPI.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

int numPollen = 8;

int pollenPixels[] = {1,6,22,33,36,47,52,61};
// 1-4 represents the lightest blue to the darkest blue
int blue1Pixels[] = {14,17,64};
int blue2Pixels[] = {2,3,7,15,16,21,25,27,29,30,34,37,40,45,48,49,56,57,62,63};
int blue3Pixels[] = {10,13,18,19,24,26,28,31,32,35,39,41,42,46,51,53,65};
int blue4Pixels[] = {4,5,8,9,11,12,20,23,38,43,44,50,54,55,58,59,60};
int pixelGrid[12][12] = {
  {0 ,0 ,0 ,35,0 ,34,31,30,29,0 ,28,0 },
  {0 ,36,37,38,39,0 ,32,0 ,27,26,0 ,0 },
  {0 ,0 ,40,0 ,0 ,0 ,33,0 ,23,24,25,0 },
  {44,43,42,41,0 ,0 ,0 ,0 ,0 ,22,21,0 },
  {0 ,45,0 ,0 ,0 ,0 ,0 ,0 ,0 ,18,19,20},
  {49,48,47,46,0 ,0, 0 ,0 ,0 ,0 ,17,0 },
  {0 ,0 ,50,51,52,0 ,0 ,0 ,13,14,15,16},
  {0 ,55,54,53,0 ,0 ,12,0 ,11,10,0 ,0 },
  {0 ,0 ,0 ,56,57,58,5 ,6 ,7 ,8 ,9 ,0 },
  {64,0 ,63,62,0 ,59,4 ,3 ,2 ,0 ,0 ,0 },
  {0 ,0 ,0 ,61,0 ,60,0 ,0 ,0 ,1 ,0 ,0 },
  {0 ,65,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 }
};

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(65, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

int *pollenCyclesOn;
int *pollenCyclesOff;

int *pollenColorR;
int *pollenColorG;
int *pollenColorB;

void setup() {
  
  //pollenCyclesOn = (int*)malloc(numPollen * sizeof(int));
  //pollenCyclesOff = (int*)malloc(numPollen * sizeof(int));

  pollenColorR = (int*)malloc(numPollen * sizeof(int));
  pollenColorG = (int*)malloc(numPollen * sizeof(int));
  pollenColorB = (int*)malloc(numPollen * sizeof(int));

/*
  for (int i = 0; i < numPollen; i++) {
    pollenCyclesOn[i] = 0; 
    pollenCyclesOff[i] = 1;
  }
  */
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels
  
  for (int i = 0; i < numPollen; i++) {
    int whichRGB = random(0, 3);
    if (whichRGB == 0) {
      pollenColorR[i] = 255;
      pollenColorG[i] = random(0,100);
      pollenColorB[i] = random(0,100);
    } else if (whichRGB == 1) {
      pollenColorR[i] = random(0,100);
      pollenColorG[i] = 255;
      pollenColorB[i] = random(0,100);
    } else {
      pollenColorR[i] = random(0,100);
      pollenColorG[i] = random(0,100);
      pollenColorB[i] = 255;
    }
  }
  
  for(float radius = 1; radius < 11; radius += 0.05) {
    lightCircle(5, 6, radius, 1);
    
    /*
    for (int i = 0; i < numPollen; i++) {
      if (pollenCyclesOff[i] > 0) {
        pollenCyclesOff[i]++;  
      }
      if (pollenCyclesOn[i] > 0) {
        pollenCyclesOn[i]++; 
      }
      
      if ((pollenCyclesOff[i] > 10) && (random(0, 100) < 20)) {
        strip.setPixelColor(pollenPixels[i] - 1, randomBrightColor());
        pollenCyclesOff[i] = 0;
        pollenCyclesOn[i] = 1;
      }
      
      if ((pollenCyclesOn[i] > 30) && (random(0, 100) < 20)) {
        strip.setPixelColor(pollenPixels[i] - 1, Color(0,0,0));
        pollenCyclesOn[i] = 0;
        pollenCyclesOff[i] = 1;
      }
      
      pollenPixels[i];
    }
    */
    strip.show();
    delay(5);
  }
  
  /*
  cyclePetals(Color(255,255,255), 750);
  cyclePetals(Color(0,0,0), 750);
  */
  
  
//  colorWipe(Color(255, 0, 0), 50);
//  colorWipe(Color(0, 255, 0), 50);
//  colorWipe(Color(0, 0, 255), 50);
//  rainbow(20);
//  rainbowCycle(20);
}

void lightCircle(float centerX, float centerY, float radius, float radiusWidth) {

  for (int x = 0; x < 12; x++) {
    for (int y = 0; y < 12; y++) {
      
      if(pixelGrid[x][y] != 0) {
        
        float distance = sqrt(pow((centerX - x), 2) + (pow((centerY - y), 2)));
        if ((distance > (radius - radiusWidth)) && (distance < (radius + radiusWidth))) {
          float distanceToRadius = abs(distance - radius);
          float intensity = (radiusWidth - distanceToRadius) / radiusWidth;
          
          int pollenInd = pollenIndex(pixelGrid[x][y]);
          if (pollenInd != -1) {
            int intensityR = (int)(pollenColorR[pollenInd] * intensity);
            int intensityG = (int)(pollenColorG[pollenInd] * intensity);
            int intensityB = (int)(pollenColorB[pollenInd] * intensity);
            
            strip.setPixelColor(pixelGrid[x][y] - 1, Color(intensityR, intensityG, intensityB));
          } else {
            int intensity255 = (int)(255 * intensity);
            strip.setPixelColor(pixelGrid[x][y] - 1, Color(intensity255, intensity255, intensity255));
          }
          
        } else {
          strip.setPixelColor(pixelGrid[x][y] - 1, Color(0, 0, 0));
        }
      
      }
      
    }
  }

}


uint32_t randomBrightColor() {
  int whichRGB = random(0, 3);
  if (whichRGB == 0) {
    return Color(255, random(0,100), random(0,100));
  } else if (whichRGB == 1) {
    return Color(random(0,100), 255, random(0,100));
  } else {
        return Color(random(0,100), random(0,100), 255);
  } 
}


boolean isPollen(int lightNum) {
  
  for (int i = 0; i < numPollen; i++) {
    if (lightNum == pollenPixels[i]) {
      return true;
    } 
  }
 
  return false;
}

int pollenIndex(int lightNum) {
  for (int i = 0; i < numPollen; i++) {
    if (lightNum == pollenPixels[i]) {
      return i;
    } 
  }
  return -1;
}



void cyclePetals(uint32_t c, uint8_t wait) {
  setArrayColor(blue1Pixels, sizeof(blue1Pixels) / sizeof(blue1Pixels[0]), c);
  strip.show();
  delay(wait);
  setArrayColor(blue2Pixels, sizeof(blue2Pixels) / sizeof(blue2Pixels[0]), c);
  strip.show();
  delay(wait);
  setArrayColor(blue3Pixels, sizeof(blue3Pixels) / sizeof(blue3Pixels[0]), c);
  strip.show();
  delay(wait);  
  setArrayColor(blue4Pixels, sizeof(blue4Pixels) / sizeof(blue4Pixels[0]), c);
  strip.show();
  delay(wait);
  setArrayColor(pollenPixels, sizeof(pollenPixels) / sizeof(pollenPixels[0]), c);
  strip.show();
  delay(wait);
}

void setArrayColor(int pixelArray[],int arraySize,uint32_t c) {
  for (int i=0; i < arraySize; i++) {
    strip.setPixelColor(pixelArray[i]-1,c);
  }
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// set the color based on x,y coordinates in the 12x12 grid, 
// 0-based with origin in the upper left
void setPixelColorXY(uint8_t x, uint8_t y, uint32_t c)
{
  int idx = pixelGrid[x][y];
  if (idx > 0) {
    strip.setPixelColor(idx,c);
  }
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
