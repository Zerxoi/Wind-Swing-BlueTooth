/*-----------------------------------------------------------------------------------------------------
																							  作者：Zerxoi
-------------------------------------------------------------------------------------------------------
--																					重力加速度 g:9.80665 																		 --
--																							杆长 l:0.60m																				 --
--                                         角速度 omega：4.0428																			 --
--																			万向节到地面高度 H:1.06m																		 --
-------------------------------------------------------------------------------------------------------
--																			单片机型号：STC15W4K56S																			 --
--														MAIN_Fosc:11059200			(Define in STC15Fxxx.h)												 --
--																下载串口		RXD1 P3.0   	TXD1	P3.1														   --
--																蓝牙串口		RXD2 P1.0		  TXD2  P1.1															 --
--                                    P0.0 M6050 SCL  P0.1 M6050 SDA                                 --
-------------------------------------------------硬件PWM-----------------------------------------------
--              				P2.3(PWM5)  P0.2(+) P0.3(-) PWM输出控制X轴转角  Motor1    (UP)               --
--                 			P2.2(PWM4)  P0.4(+) P0.5(-) PWM输出控制X轴转角  Motor2   (DOWN)              --
--                 			P2.1(PWM3)  P0.6(+) P0.7(-) PWM输出控制Y轴转角  Motor3    (UP)               --
--                 			P3.7(PWM2)  P2.0(+) P4.4(-) PWM输出控制Y轴转角  Motor4   (DOWN)              --
-----------------------------------------------------------------------------------------------------*/

#include "STC15Fxxxx.h"
#include "timer0.h"
#include "ser_printf.h"
#include "i2c.h"
#include "m6050.h"
#include "kalman.h"
#include "mathmod.h"
#include "pwm.h"
#include "motor.h"
#include "bluetooth.h"
#include <stdio.h>
#include <math.h>
char count;																																//UART1数据打印计数

m6050_structdef m6050_structure;																					//m6050结构体 (unsigned int)ax,ay,az,gx,gy  (float)angle_x,angle_y
m6050_zerodriftdef m6050_zerodrift;																				//m6050零点漂移结构体 (unsigned int)ax,ay,az,gx,gy
pid_structdef pid_structure;																							//pid结构体 (float)kp,ki,kd,x_integral,x_pre_error,x_output,y_integral,y_pre_error,y_output
mathmod_structdef mathmod_structure;																			//math model结构体 (float) sumtime,angle_x,angle_y
bluetooth_structdef bluetooth_structure;

int main()
{
	i2c_init();																															//i2c初始化	scl=1 sda=1
	pwm_init();																															//pwm初始化 推挽输出 0%占空比
	motor_gpio_config();																										//motor 引脚配置
	m6050_init();																														//GYRO Full Scale  +/- 250,ACC Full Scale   +/- 2g
	m6050_initstruct(& m6050_structure);																		//m6050结构体初始化 成员置零
	m6050_initzerodrift(& m6050_zerodrift);																	//m6050零点漂移初始化
	m6050_getzerodrift(& m6050_zerodrift);																	//取100次ax,ay,gx,gy取平均值,赋值给m6050_zerodrift
	mathmod_initstruct(& mathmod_structure);																//math model结构体初始化 成员置零 
	pid_initstruct(& pid_structure);																				//pid结构体初始化 成员置零
	ser_printf_init();																											//T2 1T 115200bps
	bluetooth_init();
	bluetooth_initstruct(& bluetooth_structure);
	Timer0Init();																														//T0中断设置 12ms
	while(1)
	{
		if (count==5)
		{
			//串口打印时间 3.5ms
			count=0;

			print_x(& m6050_structure,& mathmod_structure);											//串口打印 AngleX  测定角度 设定角度
			print_y(& m6050_structure,& mathmod_structure);											//串口打印 AngleY  测定角度 设定角度
//			print_pid(& pid_structure);
//			print_gxy(& m6050_structure);
//			print_m6050data();																										//打印从m6050读取的加速度值
//			print_zerodrift(& m6050_zerodrift);																		//打印零点漂移
//			print_axyz(& m6050_structure);																				//打印消除零点漂移的从m6050读取的加速度值 
		}
	}
}
void t0_int() interrupt 1																									//12ms 进入中断
{
	//中断执行时间 6ms
	EA=0;
	TL0=0xCD;																																//设置定时初值
	TH0=0xD4;																																//设置定时初值
	count++;
	m6050_getstructure(& m6050_structure,& m6050_zerodrift);								//获取去除零点漂移m6050结构体
	angle_calcu(& m6050_structure);																					//将m6050读取出来的整数转化成实际值，并进行kalman滤波
	switch (bluetooth_structure.mode)																				//数学模型选择
	{
		case (1):
		{
			mathmod_getSTILL(& mathmod_structure,& bluetooth_structure);
			pid_structure.kp=KP1;
			pid_structure.ki=KI1;
			pid_structure.kd=KD1;
			break;
		}
		case (2):
		{
			mathmod_getSHM(& mathmod_structure,& bluetooth_structure);
			pid_structure.kp=KP2;
			pid_structure.ki=KI2;
			pid_structure.kd=KD2;
			break;
		}
		case (3):
		{
			mathmod_getUCM(& mathmod_structure,& bluetooth_structure);
			pid_structure.kp=KP2;
			pid_structure.ki=KI2;
			pid_structure.kd=KD2;
			break;
		}
	}
	pid_getstruct(& pid_structure,& m6050_structure,& mathmod_structure);		//经数学模型与m6050数据比较进行pid得到pid值
	motor_contrl(& pid_structure);																					//将pid值传给pwm,并对电机进行控制
	EA=1;
}

void bluetooth() interrupt 8
{
	char temp;
	EA=0;
	if (S2CON&0x01)
	{
		S2CON&=0xFE;
		temp=S2BUF;
		switch (temp)
		{
			case '1':					//定点
			{
				bluetooth_structure.mode=1;
				break;
			}
			case '2':					//R+5
			{
				bluetooth_structure.r+=5;
				if (bluetooth_structure.r>30)
					bluetooth_structure.r=30;
				bluetooth_structure.angle_x=atan(cos(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				bluetooth_structure.angle_y=atan(sin(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				break;
			}
			case '3':					//R-5
			{
				bluetooth_structure.r-=5;
				if (bluetooth_structure.r<-30)
					bluetooth_structure.r=-30;
				bluetooth_structure.angle_x=atan(cos(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				bluetooth_structure.angle_y=atan(sin(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				break;
			}
			case '4':					//单摆
			{
				bluetooth_structure.mode=2;
				break;
			}
			case '5':					//Angle+30
			{
				bluetooth_structure.angle+=0.5235;
				if (bluetooth_structure.angle>3.14159)
					bluetooth_structure.angle=3.14159;
				bluetooth_structure.angle_x=atan(cos(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				bluetooth_structure.angle_y=atan(sin(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				break;
			}
			case '6':					//Angle-30
			{
				bluetooth_structure.angle-=0.5235;
				if (bluetooth_structure.angle<-3.14159)
					bluetooth_structure.angle=-3.14159;
				bluetooth_structure.angle_x=atan(cos(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				bluetooth_structure.angle_y=atan(sin(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				break;
			}
			case '7':					//恢复
			{
				bluetooth_structure.angle_x=atan(cos(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				bluetooth_structure.angle_y=atan(sin(bluetooth_structure.angle)*bluetooth_structure.r/H)*57.295828;
				break;
			}
			case '8':					//圆周
			{
				bluetooth_structure.mode=3;
				break;
			}
			case '9':					//静止
			{
				pid_structure.kp=KP3;
				pid_structure.ki=KI3;
				pid_structure.kd=KD3;
				bluetooth_structure.angle_x=0;
				bluetooth_structure.angle_y=0;
				break;
			}
		}
	}
	if (S2CON&0x20)
	{
		S2CON&=0xFD;
	}
	EA=1;
}