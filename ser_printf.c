#include "ser_printf.h"
#include "m6050.h"
#include "pid.h"
#include "math.h"
#include <stdio.h>
void ser_printf_init()	//T1 1T 115200bps
{
	P3M0&=0XFC;
	P3M1&=0XFC;
	AUXR1&=0X3F;		//P3.0 RXD    P3.1 TXD
		
	SCON=0X52;			//SM0=0 SM1=1->T1 variable REN=1 TI=1
	AUXR|=0x40;			//T1   1T
	AUXR&=0xFE;			//设定T1为波特率发生器
	TMOD&=0x0F;			//16bit auto reload
	TL1=0xE8;				//设置定时器初值
	TH1=0xFF;				//设置定时器初值
	TR1=1;
}

//void print_m6050data()
//{
//	printf("%d,%d,%d\n",m6050_getvalue(SlaveAddress,ACCEL_XOUT_H),m6050_getvalue(SlaveAddress,ACCEL_YOUT_H),m6050_getvalue(SlaveAddress,ACCEL_ZOUT_H));
//}
void print_x(m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure)
{
	printf("%f,%f,",m6050_structure->angle_x,mathmod_structure->angle_x);
}
void print_y(m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure)
{
	printf("%f,%f\n",m6050_structure->angle_y,mathmod_structure->angle_y);
}
//void print_zerodrift(m6050_zerodriftdef *m6050_zerodrift)
//{
//	printf("%d,%d,%d,",m6050_zerodrift->ax,m6050_zerodrift->ay,m6050_zerodrift->az);
//}
//void print_pid(pid_structdef *pid_structure)												//检查pid输出值
//{
//	printf("%f,%f\n",pid_structure->x_output,pid_structure->y_output);
//}
//void print_axyz(m6050_structdef *m6050_structure)										//验证加速度去除零点漂移效果
//{
//	printf("%d,%d,%d\n",m6050_structure->ax,m6050_structure->ay,m6050_structure->az);
//}
//void print_gxy(m6050_structdef *m6050_structure)										//验证角速度计去除零点漂移效果
//{
//	printf("%d,%d\n",m6050_structure->gx,m6050_structure->gy);
//}