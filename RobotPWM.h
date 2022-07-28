#ifndef ROBOTPWM_H
#define ROBOTPWM_H

/*
The BCM2835 contains 2 independent PWM channels (0 and 1), 
each of which be connnected to a limited subset of GPIO pins.
BCM PIN   PWM Channel    ALT FUN
 12              0            0 
 13              1            0
 18              0            5
 19              1            5
*/

#include <bcm2835.h>
#include <cstdio>
#include <cstdint>

#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1

bool pwmInit(uint8_t channel, uint8_t pin, uint16_t freq);
void setPW(uint8_t channel,uint32_t PW); 

#endif