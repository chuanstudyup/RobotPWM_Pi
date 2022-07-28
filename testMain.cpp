#include "RobotPWM.h"

int main()
{
	bcm2835_init();
	if(!pwmInit(PWM_CHANNEL_0,18,50))
	{
		printf("pwmInit init failed\n");
		exit(-1);
	}
	else
		printf("PWM_CHANNEL_0 init OK\n");
	
	if(!pwmInit(PWM_CHANNEL_1,19,50))
	{
		printf("pwmInit init failed\n");
		exit(-1);
	}
	else
		printf("PWM_CHANNEL_1 init OK\n");
	
	while(1)
	{
		setPW(PWM_CHANNEL_0,1500);
		
		setPW(PWM_CHANNEL_1,2000);
		
		bcm2835_delay(1000);
	}
	
	bcm2835_close();
	return 0;
}

// g++ -o testMain testMain.cpp RobotPWM.cpp -lbcm2835
