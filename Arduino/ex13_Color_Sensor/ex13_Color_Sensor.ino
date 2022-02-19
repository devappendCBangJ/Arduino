#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#define PIN            6 // 네오픽셀을 추가하는 방향으로 수정하여보았습니다. 6번핀에 연결
#define NUMPIXELS      100//1개만을 사용하지만 이후 다른 네오픽셀로 응용할 수 있도록 100개로 하였습니다.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

#include <Wire.h>
#include "Adafruit_TCS34725.h"

byte gammatable[256];
void setup() {
  pixels.begin();
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } 
    else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
}





void loop() {
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;

  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 50; g *= 50; b *= 50;//출력값의 총값 50에서 각각의 비율만큼 값을 얻기 위한 코드부분입니다
  
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
  for(int i = 0;i < NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b));
  }

  pixels.show();
