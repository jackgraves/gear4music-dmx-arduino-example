#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>

const int universeSize = 101;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // initialize the DMX library with the universe size
  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait for ever
  }
}

// leds are 0 - 7
void setLeftLight(int led, int red, int green, int blue) {
  DMX.beginTransmission();
  int offset = 1;
  offset = offset + (led * 6);
  // Red = 0-255
  DMX.write(offset + 2, red);
  // Green = 0-255
  DMX.write(offset + 3, green);
  // Blue = 0-255
  DMX.write(offset + 4, blue);
  // Brightness = 0-255
  DMX.write(offset, 100);
  // Strobe = 0-255
  DMX.write(offset + 1, 0);
  DMX.endTransmission();
}

void setRightLight(int led, int red, int green, int blue) {
  DMX.beginTransmission();
  int offset = 51;
  offset = offset + (led * 6);
  // Red = 0-255
  DMX.write(offset + 2, red);
  // Green = 0-255
  DMX.write(offset + 3, green);
  // Blue = 0-255
  DMX.write(offset + 4, blue);
  // Brightness = 0-255
  DMX.write(offset, 100);
  // Strobe = 0-255
  DMX.write(offset + 1, 0);
  DMX.endTransmission();
}

void loop() {
  int light;
  for(light = 0; light <= 7; light++) {
    // Lights ON
    setLeftLight(7 - light, 255, 255, 255);
    setRightLight(light, 255, 255, 255);
    delay(100);
    // Lights OFF
    setLeftLight(7 - light,0,0,0);
    setRightLight(light,0,0,0);
  }
  for(light = 1; light <= 6; light++) {
    // Lights ON
    setLeftLight(light, 255, 255, 255);
    setRightLight(7 - light, 255, 255, 255);
    delay(100);
    // Lights OFF
    setLeftLight(light,0,0,0);
    setRightLight(7 - light,0,0,0);
    // red = (red + 10) % 255;
  }
}
