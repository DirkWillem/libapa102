#ifndef APA102_H
#define APA102_H

#include <stdint.h>

struct APA102;
struct APA102_LED {
  uint8_t r, g, b, brightness;
};
struct APA102_Animation;

//APA102_MakeLED(uint8_t brightness, uint8_t r, uint8_t g, uint8_t b): Creates a LED-frame
struct APA102_LED* APA102_CreateFrame(uint8_t, uint8_t, uint8_t, uint8_t);

//APA102_Init(int n_leds): Initializes a LED-strip with the given number of LEDS
struct APA102* APA102_Init(int);

/*
  Base API functions for controlling single LEDs
*/
//APA102_Begin(): Begin a write
void APA102_Begin();
//APA102_End(): End a write
void APA102_End();
//APA102_WriteLED(APA102_LED): Write a single LED frame
void APA102_WriteLED(struct APA102_LED*);

/*
  'high-level' functions for controlling the entire strip
*/
//APA102_Fill(APA102* strip, APA102_LED led): Fill the entire strip with a single color
void APA102_Fill(struct APA102*, struct APA102_LED*);
//APA102_Stripes(APA102* strip, APA102_LED led, int stripe_size, int gap_size, int offset): Fill the entire strip with stripes and holes in them
void APA102_Stripes(struct APA102*, struct APA102_LED*, int, int, int);
//APA102_MultiStripes(APA102* strip, APA102_LED* leds, int stripe_size, int gap_size, int offset, int color_offset): Fill the intire strip with multi-colored stripes and holes in them. Colors are contained in a NULL-terminated array
void APA102_MultiStripes(struct APA102*, struct APA102_LED**, int, int, int, int);

/*
  Animation functions
*/
//APA102_KillAnimation(struct APA102_Animation* anim): Kills a running animation
void APA102_KillAnimation(struct APA102_Animation*);
//APA102_BlinkAnimation(APA102* strip, APA102_LED* led, int interval): A blinking animation using the given color and interval
struct APA102_Animation* APA102_BlinkAnimation(struct APA102*, struct APA102_LED*, int);
//APA102_PulseAnimation(APA102* strip, APA102_LED* led, int interval): A pulsing animation using the given color and interval
struct APA102_Animation* APA102_PulseAnimation(struct APA102*, struct APA102_LED*, int);
//APA102_StripesAnimation(APA102* strip, APA102_LED* led, int interval, int stripe_size, int gap_size, int direction)
struct APA102_Animation* APA102_StripesAnimation(struct APA102*, struct APA102_LED*, int, int, int, int);
//APA102_MultiStripesAnimation(APA102* strip, APA102_LED** led, int interval, int stripe_size, int gap_size, int direction)
struct APA102_Animation* APA102_MultiStripesAnimation(struct APA102*, struct APA102_LED**, int, int, int, int);

#endif