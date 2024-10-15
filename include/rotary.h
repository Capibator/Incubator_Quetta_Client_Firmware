#ifndef ROTARY_H
#define ROTARY_H

#include "pinouts.h"
#include "AiEsp32RotaryEncoder.h"

// constants
#define ROTARY_ENCODER_STEPS 2
#define IDLE 0
#define UP 1
#define DOWN 2
#define ENTER 3
#define BACK 4
#define longPressAfterMiliseconds 500 // how long long press should be.

//vars
extern int dir,val;
extern AiEsp32RotaryEncoder rotaryEncoder;

void initEncoder(); 
void handle_rotary_button();
void IRAM_ATTR readEncoderISR();
bool on_button_long_click();
void updateEncoder();

#endif // ROTARY_H
