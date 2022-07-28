#include "RobotPWM.h"

/*
The BCM2835 contains 2 independent PWM channels (0 and 1), 
each of which be connnected to a limited subset of GPIO pins.
BCM PIN   PWM Channel    ALT FUN
 12              0            0 
 13              1            0
 18              0            5
 19              1            5
*/

static uint32_t Channel_0_Range;
static float Channel_0_LSB;
static uint32_t Channel_0_Period; //us
static uint32_t Channel_1_Range;
static float Channel_1_LSB;
static uint32_t Channel_1_Period; //us

/**
 * Configure PWM channel, frequency and output Pin
 * @param channel PWM_CHANNEL_0 or PWM_CHANNEL_1
 * @param pin outPut PWM signal using BCM Pin. 12 and 18 for PWM_CHANNEL_0; 13 and 19 for PWM_CHANNEL_1.
 * @param freq [Hz]
 * @return true for sucessful, false for failed
 **/
bool pwmInit(uint8_t channel, uint8_t pin, uint16_t freq)
{
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_64);
	if(channel == PWM_CHANNEL_0)
	{
		if(pin != 12 && pin !=18)
		{
			printf("The pin is unsuitable for PWM_CHANNEL_0");
			return false;
		}
		else if(pin == 12)
			bcm2835_gpio_fsel(pin,BCM2835_GPIO_FSEL_ALT0);
		else if(pin == 18)
			bcm2835_gpio_fsel(pin,BCM2835_GPIO_FSEL_ALT5);
		Channel_0_Range = 300000/freq;
		Channel_0_Period = 1000000/freq;
		Channel_0_LSB = static_cast<float>(Channel_0_Period)/Channel_0_Range;
		bcm2835_pwm_set_range(PWM_CHANNEL_0,Channel_0_Range);
	}
	else if(channel == PWM_CHANNEL_1)
	{
		if(pin != 13 && pin !=19)
		{
			printf("The pin is unsuitable for PWM_CHANNEL_0");
			return false;
		}
		else if(pin == 13)
			bcm2835_gpio_fsel(pin,BCM2835_GPIO_FSEL_ALT0);
		else if(pin == 19)
			bcm2835_gpio_fsel(pin,BCM2835_GPIO_FSEL_ALT5);	
		Channel_1_Range = 300000/freq;
		Channel_1_Period = 1000000/freq;
		Channel_1_LSB = static_cast<float>(Channel_1_Period)/Channel_1_Range;
		bcm2835_pwm_set_range(PWM_CHANNEL_1,Channel_1_Range);
	}
	bcm2835_pwm_set_mode(channel,1,1);
	return true;
}

/**
 * Set Pulse width of the specified channel
 * @param channel PWM_CHANNEL_0 or PWM_CHANNEL_1
 * @param PW [us] 0-Channel_x_Period
 **/
void setPW(uint8_t channel,uint32_t PW)
{
	if(channel == PWM_CHANNEL_0)
	{
		if(PW<Channel_0_Period)
			bcm2835_pwm_set_data(channel,static_cast<uint32_t>(PW/Channel_0_LSB));
	}
	else if(channel == PWM_CHANNEL_1)
	{
		if(PW<Channel_1_Period)
			bcm2835_pwm_set_data(channel,static_cast<uint32_t>(PW/Channel_1_LSB));
	}
}
