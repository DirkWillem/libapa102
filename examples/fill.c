/*
  fill.c: Simple example which fills a 60-LED APA102 with red
*/

#include <apa102.h>

int main() {
  struct APA102* strip = APA102_Init(60);
  APA102_Fill(strip, APA102_CreateFrame(31, 0xFF, 0x00, 0x00));
  return 0;
}