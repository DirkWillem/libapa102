/*
  multistripes.c: example which creates differently colored stripes on the strip
*/

#include <apa102.h>

int main() {
  //Initialize strip
  struct APA102* strip = APA102_Init(60);

  //Create the colors array (must be NULL-terminated)
  struct APA102_LED* colors[5];

  colors[0] = APA102_CreateFrame(31, 0xFF, 0x0, 0x0);
  colors[1] = APA102_CreateFrame(31, 0xFF, 0xFF, 0x0);
  colors[2] = APA102_CreateFrame(31, 0x00, 0xFF, 0x0);
  colors[3] = APA102_CreateFrame(31, 0x00, 0xFF, 0xFF);
  colors[4] = 0;

  //Fill strip
  APA102_MultiStripes(strip, colors, 4, 2, 0, 0);
}