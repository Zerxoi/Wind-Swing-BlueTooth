#include "STC15Fxxxx.h"
#include "pid.h"
#include "pwm.h"

void pwm_gpio_config()
{
	//P2.1/P2.2/P2.3 ����Ϊ�������
	P2M0&=0xf1;
	P2M0|=0x0e;
	P2M1&=0xf1;
	P2M1|=0x00;
	//P3.7 ����Ϊ�������
	P3M0&=0x7f;
	P3M0|=0x80;
	P3M1&=0x7f;
	P3M1|=0x00;
}

void pwm_init()
{
	pwm_gpio_config();
	
	P_SW2|=0x80;//ʹ�ܷ���XSFR
	PWMCFG=0x00;//����PWM2345��ʼ��ƽΪ�͵�ƽ
	PWMCKS=0x00;//PWMʱ��Ϊϵͳʱ��
	
	PWMC=12000L;//PWM���� 12000
	//��ʼ��ת(0%ռ�ձ�)
	PWM5T1=0x0000;
	PWM5T2=0x0001;
	PWM4T1=0x0000;
	PWM4T2=0x0001;
	PWM3T1=0x0000;
	PWM3T2=0x0001;
	PWM2T1=0x0000;
	PWM2T2=0x0001;
	
	PWM2CR=0x00;//PWM2�����P3.7,��ʹ���ж�
	PWM3CR=0x00;//PWM3�����P2.1,��ʹ���ж�
	PWM4CR=0x00;//PWM4�����P2.2,��ʹ���ж�
	PWM5CR=0x00;//PWM5�����P2.3,��ʹ���ж�
	
	PWMCR=0x0f;//ʹ��PWM2345ͨ��
	PWMCR|=0x80;//ʹ��PWM������
}
