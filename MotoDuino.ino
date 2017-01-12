#include <Adafruit_NeoPixel.h>

int sensorPin = A5;    // select the input pin for the potentiometer
int pixelPin = 6;      // select the pin for the Pixel RBG thing
int sensorValue = 0;  // variable to store the value coming from the sensor
int level = 0;
int pixels = 24;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, pixelPin, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(255, 0, 0);

void setup() {
  strip.begin();
  strip.setBrightness(64);
  pinMode(pixelPin, OUTPUT);
  Serial.begin(9600);
  theaterChaseRainbow(5);
}

void loop() {
  clear();
  sensorValue = analogRead(sensorPin);
  werkit(sensorValue);
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void werkit(int i) {
  level = 1024 / i;
  checkColor(level);
  for ( int i = 0; i < level; i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}
void clear() {
  for (int i = 0; i < pixels; i++) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
}

void checkColor(int level) {
  if (level < 5) {
    color = strip.Color(255, 0, 255);
  }
  else if (5 < level && level < 18) {
    color = strip.Color(255, 255, 0);
  }
  else if (level > 18) {
    color = strip.Color(255, 0, 0);
  }
}

