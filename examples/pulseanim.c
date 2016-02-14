/*
  blinkanim.c: Runs a pulsing animation for 5 seconds
*/

#include <apa102.h>
#include <wiringPi.h>

int main() {
  //Initialize strip
  struct APA102* strip = APA102_Init(60);

  //Run animation
  struct APA102_Animation* anim = APA102_PulseAnimation(strip, APA102_CreateFrame(31, 0x00, 0x0, 0xFF), 20);

  //Delay and kill
  delay(5000);
  APA102_KillAnimation(anim);
}