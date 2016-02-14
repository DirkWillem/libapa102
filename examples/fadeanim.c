/*
  fadeanim.c: Example demonstrating fade animations
*/

#include <apa102.h>

int main() {
  //Initialize strip
  struct APA102* strip = APA102_Init(60);

  //Create the colors array (must be NULL-terminated)
  struct APA102_Frame* colors[5];

  colors[0] = APA102_CreateFrame(31, 0xFF, 0x0, 0x0);
  colors[1] = APA102_CreateFrame(31, 0xFF, 0xFF, 0x0);
  colors[2] = APA102_CreateFrame(31, 0x00, 0xFF, 0x0);
  colors[3] = APA102_CreateFrame(31, 0x00, 0xFF, 0xFF);
  colors[4] = 0;

  //Run animation
  struct APA102_Animation* anim = APA102_FadeAnimation(strip, colors, 500);
  delay(10000);
  APA102_KillAnimation(anim);
}