#include "STC15Fxxxx.h"
#include "bluetooth.h"

extern bit busy;

void bluetooth_init()		//T2 1T 9600bps
{
	P1M0&=0XFC;
	P1M1&=0XFC;
	P_SW2&=0xFE;			//P10RXD2  P11TXD2
	
	S2CON = 0x50;			//8bit REN=1
	AUXR|=0x04;		//T2  1T
//	IP2=0X01;
	T2L=0xE0;				//设置定时器初值
	T2H=0xFe;				//设置定时器初值
	AUXR |= 0x10;			//Run T2
	IE2=0X01;
	EA=1;
}

void bluetooth_initstruct(bluetooth_structdef *bluetooth_structure)
{
	bluetooth_structure->mode=1;
	bluetooth_structure->r=0;
	bluetooth_structure->angle=0;
	bluetooth_structure->angle_x=0;
	bluetooth_structure->angle_y=0;
}
