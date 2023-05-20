#include "STC15Fxxxx.h"

void Timer0Init(void)		//12毫秒@11.0592MHz
{
	AUXR&=0x7F;		//T0时钟12T模式
	TMOD&=0xF0;		//设置定时器模式
	TMOD|=0x01;		//设置定时器模式
	TL0=0xCD;			//设置定时初值
	TH0=0xD4;			//设置定时初值
	TF0=0;				//清除TF0标志
	ET0=1;				//T0定时器中断使能
	EA=1;					//全体中断使能
	TR0=1;				//定时器0开始计时
}
