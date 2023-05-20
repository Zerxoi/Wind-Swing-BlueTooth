#include "motor.h"
#include "pwm.h"
void motor_gpio_config()
{
	//P02-P07����Ϊ�������ģʽ
	P0M0&=0x03;
	P0M0|=0xfc;
	P0M1&=0x03;
	P0M1|=0x00;
	
	//P20����Ϊ�������ģʽ
	P2M0&=0xfe;
	P2M0|=0x01;
	P2M1&=0xfe;
	P2M1|=0x00;
	
	//P44����Ϊ�������ģʽ
	P4M0&=0xef;
	P4M0|=0x10;
	P4M1&=0xef;
	P4M1|=0x00;
}

void motor1_forward()
{
	motor1p=1;
	motor1n=0;
}

void motor1_stop()
{
	motor1p=0;
	motor1n=0;
}

void motor2_forward()
{
	motor2p=1;
	motor2n=0;
}

void motor2_stop()
{
	motor2p=0;
	motor2n=0;
}

void motor3_forward()
{
	motor3p=1;
	motor3n=0;
}

void motor3_stop()
{
	motor3p=0;
	motor3n=0;
}

void motor4_forward()
{
	motor4p=1;
	motor4n=0;
}

void motor4_stop()
{
	motor4p=0;
	motor4n=0;
}

void motor_contrl(pid_structdef *pid_structure)
{
	if (pid_structure->x_output<0)//x��ʵ��ֵ>�趨ֵ ��ת
	{
		motor1_stop();		//motor1 ֹͣ
		motor2_forward();	//motor2 ��ת
		if (pid_structure->x_output<-6000)//PWM�������ֵ(�����ѹ��Ҫ����6v)
			PWM4T2=6000;
		else if (pid_structure->x_output>-1)
			PWM4T2=1;
		else
			PWM4T2=(long int)(-1*pid_structure->x_output);//motor2 PWM
	}
	else//x�� ʵ��ֵ<�趨ֵ
	{
		motor1_forward();	//motor1 ��ת
		motor2_stop();		//motor2 ֹͣ
		if (pid_structure->x_output>6000)//PWM�������ֵ(�����ѹ��Ҫ����6v)
			PWM5T2=6000;
		else if (pid_structure->x_output<1)
			PWM5T2=1;
		else
			PWM5T2=(long int)(pid_structure->x_output);//motor1 PWM
	}
	
	if (pid_structure->y_output<0)//y�� ʵ��ֵ>�趨ֵ ��ת
	{
		motor3_stop();		//motor3 ֹͣ
		motor4_forward();	//motor4 ��ת
		if (pid_structure->y_output<-6000)//PWM�������ֵ(�����ѹ��Ҫ����6v)
			PWM2T2=6000;
		else if (pid_structure->y_output>-1)
			PWM2T2=1;
		else
			PWM2T2=(int)(-1*pid_structure->y_output);//motor4 PWM���
	}
	else//y�� ʵ��ֵ<�趨ֵ ��ת
	{
		motor3_forward(); //motor3 ��ת
		motor4_stop();		//motor4 ֹͣ
		if (pid_structure->y_output>6000)//PWM�������ֵ(�����ѹ��Ҫ����6v)
			PWM3T2=6000;
		else if (pid_structure->y_output<1)
			PWM3T2=1;
		else
			PWM3T2=(long int)(pid_structure->y_output);//motor3 PWM���
	}
}