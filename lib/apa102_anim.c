#include "apa102.h"

#include <stdlib.h>
#include <stdint.h>

#include <wiringPi.h>
#include <pthread.h>

int sgn(int a) {
  if(a >= 0)
    return 1;
  return -1;
}

struct APA102_Animation {
  int* kill;
  pthread_t thread;
};

struct BlinkAnimData {
  struct APA102_Animation* anim;
  struct APA102* strip;
  struct APA102_LED* led;

  int interval;
};

struct PulseAnimData {
  struct APA102_Animation* anim;
  struct APA102* strip;
  struct APA102_LED* led;

  int interval;
};

struct StripesAnimData {
  struct APA102_Animation* anim;
  struct APA102* strip;
  struct APA102_LED* led;

  int interval, direction, stripe_size, gap_size;
};

struct MultiStripesAnimData {
  struct APA102_Animation* anim;
  struct APA102* strip;
  struct APA102_LED** leds;

  int interval, direction, stripe_size, gap_size;
};

void* BlinkAnimHandler(void* udata) {
  struct BlinkAnimData* data;

  data = (struct BlinkAnimData*)udata;
  while(1) {
    APA102_Fill(data->strip, data->led);
    delay(data->interval);
    if(*(data->anim->kill)) {
      break;
    }
    APA102_Fill(data->strip, APA102_CreateFrame(0x0, 0x0, 0x0, 0x0));
    delay(data->interval);
    if(*(data->anim->kill)) {
      break;
    }
  }
}

void* PulseAnimHandler(void* udata) {
  struct PulseAnimData* data;
  uint8_t brightness;
  int delta;

  data = (struct PulseAnimData*)udata;
  brightness = 1;
  delta = 1;
  while(1) {
    APA102_Fill(data->strip, APA102_CreateFrame(brightness, data->led->r, data->led->g, data->led->b));
    brightness += delta;
    if(brightness == 0 || brightness == 31) {
      delta = -delta;
    }
    delay(data->interval);
    if(*(data->anim->kill)) {
      break;
    }
  }
}

void* StripesAnimHandler(void* udata) {
  struct StripesAnimData* data;
  int offset;

  data = (struct StripesAnimData*)udata;

  if(data->direction == 1) {
    offset = 0;
  } else {
    offset = data->stripe_size + data->gap_size;
  }

  while(1) {
    APA102_Stripes(data->strip, data->led, data->stripe_size, data->gap_size, offset);
    offset += data->direction;
    if(offset < 0) {
      offset = data->stripe_size + data->gap_size - 1;
    } else if (offset >= data->stripe_size + data->gap_size) {
      offset = 0;
    }

    if(*(data->anim->kill)) {
      break;
    }

    delay(data->interval);
  }
}

void* MultiStripesAnimHandler(void* udata) {
  struct MultiStripesAnimData* data;
  int offset, coffset, clen;
  struct APA102_LED* ref;

  data = (struct MultiStripesAnimData*)udata;

  clen = 0;

  ref = data->leds[0];
  while(1) {
    ref = data->leds[clen];
    if(ref == 0) {
      break;
    }
    clen++;
  }

  if(data->direction == 1) {
    offset = 0;
    coffset = 0;
  } else {
    offset = data->stripe_size + data->gap_size;
    coffset = clen-1;
  }

  while(1) {
    APA102_MultiStripes(data->strip, data->leds, data->stripe_size, data->gap_size, offset, coffset);
    offset += data->direction;
    if(offset < 0) {
      offset = data->stripe_size + data->gap_size - 1;
      coffset--;
      if(coffset < 0) {
        coffset = clen-1;
      }

    } else if (offset >= data->stripe_size + data->gap_size) {
      offset = 0;
      coffset++;
      if(coffset >= clen) {
        coffset = 0;
      }
    }

    if(*(data->anim->kill)) {
      break;
    }

    delay(data->interval);
  }
}

struct APA102_Animation* APA102_BlinkAnimation(struct APA102* strip, struct APA102_LED* led, int interval) {
  struct APA102_Animation* anim;
  struct BlinkAnimData* data;

  anim = (struct APA102_Animation*)malloc(sizeof(struct APA102_Animation));
  data = (struct BlinkAnimData*)malloc(sizeof(struct BlinkAnimData));

  data->anim = anim;
  data->strip = strip;
  data->led = led;
  data->interval = interval;

  anim->kill = (int*)malloc(sizeof(int));
  *(anim->kill) = 0;
  pthread_create(&anim->thread, 0, BlinkAnimHandler, (void*)data);
  return anim;
}

struct APA102_Animation* APA102_PulseAnimation(struct APA102* strip, struct APA102_LED* led, int interval) {
  struct APA102_Animation* anim;
  struct PulseAnimData* data;

  anim = (struct APA102_Animation*)malloc(sizeof(struct APA102_Animation));
  data = (struct PulseAnimData*)malloc(sizeof(struct PulseAnimData));

  data->anim = anim;
  data->strip = strip;
  data->led = led;
  data->interval = interval;

  anim->kill = (int*)malloc(sizeof(int));
  *(anim->kill) = 0;
  pthread_create(&anim->thread, 0, PulseAnimHandler, (void*)data);
  return anim;
}

struct APA102_Animation* APA102_StripesAnimation(struct APA102* strip, struct APA102_LED* led, int interval, int stripe_size, int gap_size, int direction) {
  struct APA102_Animation* anim;
  struct StripesAnimData* data;

  anim = (struct APA102_Animation*)malloc(sizeof(struct APA102_Animation));
  data = (struct StripesAnimData*)malloc(sizeof(struct StripesAnimData));

  data->anim = anim;
  data->strip = strip;
  data->led = led;
  data->interval = interval;
  data->stripe_size = stripe_size;
  data->gap_size = gap_size;
  data->direction = sgn(direction);

  anim->kill = (int*)malloc(sizeof(int));
  *(anim->kill) = 0;
  pthread_create(&anim->thread, 0, StripesAnimHandler, (void*)data);
  return anim;
}

struct APA102_Animation* APA102_MultiStripesAnimation(struct APA102* strip, struct APA102_LED** leds, int interval, int stripe_size, int gap_size, int direction) {
  struct APA102_Animation* anim;
  struct MultiStripesAnimData* data;

  anim = (struct APA102_Animation*)malloc(sizeof(struct APA102_Animation));
  data = (struct MultiStripesAnimData*)malloc(sizeof(struct MultiStripesAnimData));

  data->anim = anim;
  data->strip = strip;
  data->leds = leds;
  data->interval = interval;
  data->stripe_size = stripe_size;
  data->gap_size = gap_size;
  data->direction = sgn(direction);

  anim->kill = (int*)malloc(sizeof(int));
  *(anim->kill) = 0;
  pthread_create(&anim->thread, 0, MultiStripesAnimHandler, (void*)data);
  return anim;
}

void APA102_KillAnimation(struct APA102_Animation* anim) {
  *(anim->kill) = 1;
  pthread_join(anim->thread, 0);
}