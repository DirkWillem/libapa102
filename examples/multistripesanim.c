/*
  multistripesanim.c: example which animates the strip with differently colored stripes for 5 seconds
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

  //Run animation
  struct APA102_Animation* anim = APA102_MultiStripesAnimation(strip, colors, 50, 4, 2, -1);
  delay(5000);
  APA102_KillAnimation(anim);
}