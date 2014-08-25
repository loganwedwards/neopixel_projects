#include <Adafruit_NeoPixel.h>

#define PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

int MAX_BRIGHTNESS = 255;
boolean readyToStart = true;
int resetButton = 1; //pin p1 for reset button
//int adjustKnob = 0;
boolean resetProgram = false;

void setup() {

  strip.begin();
  strip.show(); 

  pinMode(resetButton, INPUT);
  pinMode(1, INPUT); // pin p2 = analog port 1
  
  //Serial.begin(9600);
}
void loop() {
  if (readyToStart) {
    initialize(); 
  }

  if (digitalRead(resetButton) == 1) {
    readyToStart = true;
  }
  delay(100);
  
  //analog port 1 = pin 2
  int adjustVal = analogRead(1);
  //Serial.print("Raw Value: ");
  //Serial.print(adjustVal);
  //Serial.print("\t");
  //Serial.print("New values: ");
  int val = map(adjustVal, 500, 1023, 0, 7);
  //Serial.print(val);
  //Serial.print("\n");
  adjustBar(val);
  
}

/*
 * Sweet initialization setup
 */
void initialize() {
  // Fade up slowly to white using MAX_BRIGHTNESS var
  for (int i = 0; i < strip.numPixels(); i++) {
    for (int j = 0; j < MAX_BRIGHTNESS; j++) {
      strip.setPixelColor(i, j, j, j);
      strip.setBrightness(128);
      strip.show();
      delay(2);
    }
  }

  // Fade out light bar
  for (int i = strip.numPixels(); i >= 0; i--) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    delay(50);
  }

  delay(1000);

  // Make healthy bar
//  for (int i = 0; i < strip.numPixels(); i++) {
//    strip.setPixelColor(i, 0, 255, 0);
//  }
//
//  strip.setBrightness(20);
//  strip.show();

  readyToStart = false;
  // End sweet initialization
}

void adjustBar(int val) {
 // strip.show();
  int valIn = val;
  uint32_t color = strip.Color(255, 255, 255);
  switch (valIn) {
  case 1:
    color = strip.Color(255, 16, 0);
    break;
  case 2:
    color = strip.Color(255, 64, 0);
    break;
  case 3:
    color = strip.Color(255, 64, 0);
    break;
  case 4:
    color = strip.Color(255, 128, 0);
    break;
  case 5:
    color = strip.Color(128, 255, 0);
    break;
  case 6:
    color = strip.Color(64, 255, 0);
    break;
  case 7:
    color = strip.Color(0, 255, 0);
    break;
  default:
    color = strip.Color(255, 0, 0); 
  }
  
  //clear the pixels to zero
  for (int j = 0; j < strip.numPixels(); j++) {
   strip.setPixelColor(j, 0, 0, 0);
  }
  strip.show();
  
  //show the correct color and num pixels
  for (int i = 0; i <= valIn; i++) {
    strip.setPixelColor(i, color);
  } 
  strip.show();
}

