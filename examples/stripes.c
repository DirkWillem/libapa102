/*
  stripes.c: Simple example which creates mono-colored stripes on the strip
*/

#include <apa102.h>

int main() {
  struct APA102* strip = APA102_Init(60);
  APA102_Stripes(strip, APA102_CreateFrame(31, 0x00, 0xFF, 0x00), 6, 2, 0);
  return 0;
}