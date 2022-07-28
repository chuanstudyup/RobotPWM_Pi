# RobotPWM_Pi
A flexible PWM output interface based on bcm2835 for RaspberryPi


/*
The BCM2835 contains 2 independent PWM channels (0 and 1), 
each of which be connnected to a limited subset of GPIO pins.
BCM PIN   PWM Channel    ALT FUN
 12              0            0 
 13              1            0
 18              0            5
 19              1            5
*/


/*
 *@param channel PWM_CHANNEL_0 or PWM_CHANNEL_1
 *@param pin outPut PWM signal using BCM Pin. 12 and 18 for PWM_CHANNEL_0; 13 and 19 for PWM_CHANNEL_1.
 *@param freq [Hz]
 *@return true for sucessful, false for failed
 */
bool pwmInit(uint8_t channel, uint8_t pin, uint16_t freq);

/*
 *@param channel PWM_CHANNEL_0 or PWM_CHANNEL_1
 *@param PW [us] 0-
 *@param freq Hz
 *@return true for sucessful, false for failed
 */
void setPW(uint8_t channel,uint32_t PW); 
