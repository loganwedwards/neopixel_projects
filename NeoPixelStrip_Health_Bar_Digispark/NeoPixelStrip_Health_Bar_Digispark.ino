#include <Adafruit_NeoPixel.h>

#define PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800); // 8 instead of 30 for stick

int MAX_BRIGHTNESS = 255;
boolean readyToStart = true;
int resetButton = 1; //pin p1 for reset button
int temp = 0;
int val = 1;
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
  delay(250);
  
  //analog port 1 = pin 2
  int adjustVal = analogRead(1);
  
  //Serial.print("Raw Value: ");
  //Serial.print(adjustVal);
  //Serial.print("\t");
  //Serial.print("New values: ");
  temp = val;
  val = map(adjustVal, 511, 1023, 0, 29); //7 instead of 29 for stick
  //Serial.print(val);
  //Serial.print("\n");
  if (temp != val) { // don't update LED if adjustment knob hasn't changed
    adjustBar(val);
  }
  
}

/*
 * Sweet initialization setup
 */
void initialize() {
  // Fade up slowly to white using MAX_BRIGHTNESS var
  for (int i = 0; i < strip.numPixels(); i++) {
    for (int j = 0; j < MAX_BRIGHTNESS; j++) {
      strip.setPixelColor(i, j, j, j);
      strip.setBrightness(240);
      strip.show();
      delay(.1);
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
  // Case statement for use with stick, mapped below to convert back to strip
  switch (valIn) {
  case 1:
  case 2:   
  case 3:  
  case 4:  
  case 5:
    color = strip.Color(255, 16, 0);
    break;
  case 6:   
  case 7:  
  case 8:  
  case 9:
    color = strip.Color(255, 64, 0);
    break;
  case 10:   
  case 11:  
  case 12:  
  case 13:
    color = strip.Color(255, 64, 0);
    break;
  case 14:   
  case 15:  
  case 16:  
  case 17:
    color = strip.Color(255, 128, 0);
    break;   
  case 18:  
  case 19:  
  case 20:
  case 21:
    color = strip.Color(128, 255, 0);
    break;
  case 22:   
  case 23:  
  case 24:  
  case 25:
    color = strip.Color(64, 255, 0);
    break;
  case 26:
  case 27:  
  case 28:
  case 29:
    color = strip.Color(0, 255, 0);
    break;
  default:
    color = strip.Color(255, 0, 0); 
  }
  
 // valIn = map(valIn,0,7,0,29); // Used to convert back to strip
  
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

