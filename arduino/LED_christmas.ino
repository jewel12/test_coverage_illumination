#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  int cov = getCoverage();
  if (cov >= 0) {
    clearPixels();
    showCoverage(cov);
  }
}

int getCoverage() {
  int cov = 0;
  cov = Serial.read();
  if(cov > 100) { return 0; }
  return cov;
}

void clearPixels() {
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t offColor = strip.Color(0, 0, 0);

  for(uint16_t i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, blue);
    strip.show();
    delay(10);
    strip.setPixelColor(i, offColor);
  }
}

void showCoverage(int cov) {
  int numGreenPixels = numGreenPixelsFromCoverage(cov);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t red = strip.Color(255, 0, 0);

  for(uint16_t i=0; i < strip.numPixels(); i++) {
    if(i < numGreenPixels) {
      strip.setPixelColor(i, green);
    } else {
      strip.setPixelColor(i, red);
    }
    strip.show();
    delay(50);
  }
}

int numGreenPixelsFromCoverage(int cov) {
  return (int)(strip.numPixels() * ((float)cov / 100));
}
