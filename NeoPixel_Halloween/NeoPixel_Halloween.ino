#include <Adafruit_NeoPixel.h>

#define PIN 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

int MAX_BRIGHTNESS = 255;

int relay1 = 8;
int relay2 = 9;
int relay3 = 10;
int relay4 = 11;

//int switchRelayTimes[10];

void setup() {

  strip.begin();
  strip.show(); 
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  initialize(); 
  initRelays();
  
}
void loop() {
  int count = 0;

  int someNum = random(10);
  int duration = random(125, 3000);
  if (count % 3 == 0) {
    flickerShow(); 
  }
  
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 128, 0);
    strip.setBrightness(MAX_BRIGHTNESS);
    strip.show(); 
  }
  
  flicker(someNum, duration);
  pulsate(5,10,127); 
  randomPix();
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 128, 0);
    strip.setBrightness(MAX_BRIGHTNESS);
    strip.show(); 
  }
  pulsate(1,2,0); 
  count++;
}
/*
 * Method to turn on the relays one at a time
 */
void initRelays() {
  for (int i = relay1; i <= relay4; i++) { 
    digitalWrite(i, HIGH);
    delay(200);
  }
}

/*
 * Method to switch relays off/on for given duration
 */
void flicker(int relayPins, int duration) {
  if (relayPins < 4) {
    for (int i = relay1; i < relay1 + relayPins; i++) {
      digitalWrite(i, LOW);
      delay(duration);
      digitalWrite(i, HIGH); 
    }
  }
}

/*
 * Method to switch relays off/on for given duration
 */
void flickerShow() {
  
toggleRelays(true);
digitalWrite(relay1, HIGH);
delay(1000);
digitalWrite(relay1, LOW);
delay(1000);
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
delay(1000);
digitalWrite(relay3, HIGH);
delay(1000);
digitalWrite(relay4, HIGH);

toggleRelays(false);
  
}
/*
 * Method to toggle state of all 4 relays.
 * If true => turn off
 * If false => turn on
 */
void toggleRelays(boolean off) {
     for (int i = relay1; i <= relay4; i++) {
       if (off) {
        digitalWrite(i, LOW);
       }
       else {
        digitalWrite(i, HIGH); 
       }
      delay(1000);
    } 
}
/*
 * Sweet initialization setup for the NeoPixel Strip
 */
void initialize() {
  // Fade up slowly to white using MAX_BRIGHTNESS var
  for (int i = 0; i < strip.numPixels(); i++) {
    for (int j = 0; j < MAX_BRIGHTNESS; j++) {
      strip.setPixelColor(i, 255, 255, 255);
      strip.setBrightness(j);
      strip.show();
      delay(.05);
    }
  }

  // Fade out light bar
  for (int i = strip.numPixels(); i >= 0; i--) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    delay(100);
  }
  delay(1000);
}
/*
 * Method to make the NeoPixel strip 'pulse'
 */
void pulsate(int fadeOutDelay, int fadeInDelay, int fadeTo) {
  int k = 0;
  while (k < 25) {
  for (int i = MAX_BRIGHTNESS; i > fadeTo; i--) {
    strip.setBrightness(i);
    strip.show();
    delay(fadeOutDelay);
  }
  for (int j = fadeTo+1; j < MAX_BRIGHTNESS; j++) {
    strip.setBrightness(j);
    strip.show();
    delay(fadeInDelay);
  }  
  k++;
  }
}

/*
 * Method to randomly light the the strip
 */
void randomPix() {
  //for (int j = 0; j < strip.numPixels(); j++) {
   strip.setBrightness(10); 
   strip.show();
   delay(100);
  //}
  int ctr = 0;
  while (ctr < 5) {
   for (int i = 0; i < strip.numPixels(); i++) {
     int randomPixel = random(strip.numPixels());
    strip.setPixelColor(randomPixel, random(0,255), random(0,255), random(0,255));
    strip.setBrightness(MAX_BRIGHTNESS);
    strip.show();
    delay(250);
   } 
   ctr++;
  }
}
