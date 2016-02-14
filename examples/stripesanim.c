/*
  stripesanim.c: Runs a stripes animation for 5 seconds
*/

#include <apa102.h>
#include <wiringPi.h>

int main() {
  struct APA102* strip = APA102_Init(60);
  struct APA102_Animation* anim = APA102_StripesAnimation(strip, APA102_CreateFrame(31, 0xFF, 0xFF, 0x0), 50, 4, 2, -1);
  delay(5000);
  APA102_KillAnimation(anim);
  return 0;
}