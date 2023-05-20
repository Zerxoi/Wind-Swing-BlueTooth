#include "motor.h"
#include "pwm.h"
void motor_gpio_config()
{
	//P02-P07配置为推挽输出模式
	P0M0&=0x03;
	P0M0|=0xfc;
	P0M1&=0x03;
	P0M1|=0x00;
	
	//P20配置为推挽输出模式
	P2M0&=0xfe;
	P2M0|=0x01;
	P2M1&=0xfe;
	P2M1|=0x00;
	
	//P44配置为推挽输出模式
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
	if (pid_structure->x_output<0)//x轴实际值>设定值 反转
	{
		motor1_stop();		//motor1 停止
		motor2_forward();	//motor2 正转
		if (pid_structure->x_output<-6000)//PWM超出最大值(电机电压不要超出6v)
			PWM4T2=6000;
		else if (pid_structure->x_output>-1)
			PWM4T2=1;
		else
			PWM4T2=(long int)(-1*pid_structure->x_output);//motor2 PWM
	}
	else//x轴 实际值<设定值
	{
		motor1_forward();	//motor1 正转
		motor2_stop();		//motor2 停止
		if (pid_structure->x_output>6000)//PWM超出最大值(电机电压不要超出6v)
			PWM5T2=6000;
		else if (pid_structure->x_output<1)
			PWM5T2=1;
		else
			PWM5T2=(long int)(pid_structure->x_output);//motor1 PWM
	}
	
	if (pid_structure->y_output<0)//y轴 实际值>设定值 反转
	{
		motor3_stop();		//motor3 停止
		motor4_forward();	//motor4 正转
		if (pid_structure->y_output<-6000)//PWM超出最大值(电机电压不要超出6v)
			PWM2T2=6000;
		else if (pid_structure->y_output>-1)
			PWM2T2=1;
		else
			PWM2T2=(int)(-1*pid_structure->y_output);//motor4 PWM输出
	}
	else//y轴 实际值<设定值 正转
	{
		motor3_forward(); //motor3 正转
		motor4_stop();		//motor4 停止
		if (pid_structure->y_output>6000)//PWM超出最大值(电机电压不要超出6v)
			PWM3T2=6000;
		else if (pid_structure->y_output<1)
			PWM3T2=1;
		else
			PWM3T2=(long int)(pid_structure->y_output);//motor3 PWM输出
	}
}