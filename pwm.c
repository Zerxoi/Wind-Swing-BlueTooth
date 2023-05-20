#include "STC15Fxxxx.h"
#include "pid.h"
#include "pwm.h"

void pwm_gpio_config()
{
	//P2.1/P2.2/P2.3 配置为推挽输出
	P2M0&=0xf1;
	P2M0|=0x0e;
	P2M1&=0xf1;
	P2M1|=0x00;
	//P3.7 配置为推挽输出
	P3M0&=0x7f;
	P3M0|=0x80;
	P3M1&=0x7f;
	P3M1|=0x00;
}

void pwm_init()
{
	pwm_gpio_config();
	
	P_SW2|=0x80;//使能访问XSFR
	PWMCFG=0x00;//配置PWM2345初始电平为低电平
	PWMCKS=0x00;//PWM时钟为系统时钟
	
	PWMC=12000L;//PWM周期 12000
	//初始翻转(0%占空比)
	PWM5T1=0x0000;
	PWM5T2=0x0001;
	PWM4T1=0x0000;
	PWM4T2=0x0001;
	PWM3T1=0x0000;
	PWM3T2=0x0001;
	PWM2T1=0x0000;
	PWM2T2=0x0001;
	
	PWM2CR=0x00;//PWM2输出到P3.7,不使能中断
	PWM3CR=0x00;//PWM3输出到P2.1,不使能中断
	PWM4CR=0x00;//PWM4输出到P2.2,不使能中断
	PWM5CR=0x00;//PWM5输出到P2.3,不使能中断
	
	PWMCR=0x0f;//使能PWM2345通道
	PWMCR|=0x80;//使能PWM发生器
}
