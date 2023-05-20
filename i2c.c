#include "STC15Fxxxx.h"
#include "i2c.h"

void delayus()
{;;}
void i2c_init()
{
	P0M0&=0XFC;
	P0M1&=0XFC;
	sda=1;
	scl=1;
}
void i2c_start()
{
	scl=0;
	sda=1;
	scl=1;
	delayus();
	sda=0;
	delayus();
	scl=0;
}
void i2c_stop()
{
	sda=0;
	scl=1;
	delayus();
	sda=1;
	delayus();
	scl=0;
}
void i2c_response()
{
	unsigned char i;
	scl=1;
	while(sda==1&&i<255)i++;
	scl=0;
}
void i2c_write(unsigned char dat)
{
	unsigned char i,temp;
	temp=dat;
	for (i=8;i>0;i--)
	{
		temp<<=1;
		sda=CY;
		scl=1;
		delayus();
		scl=0;
	}
	sda=1;
}
unsigned char i2c_read()
{
	unsigned char i,byte;
	for (i=8;i>0;i--)
	{
		scl=1;
		delayus();
		byte=byte<<1|sda;
		scl=0;
	}
	sda=1;
	return byte;
}
void i2c_writeadd(unsigned char dvadd,unsigned char wdadd,unsigned char dat)	//dvadd:Device Adress wdadd:Word Address
{
	i2c_start();
	i2c_write(dvadd);
	i2c_response();
	i2c_write(wdadd);
	i2c_response();
	i2c_write(dat);
	i2c_response();
	i2c_stop();
}
unsigned char i2c_readadd(unsigned char dvadd,unsigned char wdadd)
{
	unsigned char dat;
	i2c_start();
	i2c_write(dvadd);
	i2c_response();
	i2c_write(wdadd);
	i2c_response();		//以上为写入读取数据的指针
	i2c_start();
	i2c_write(dvadd+1);
	i2c_response();
	dat=i2c_read();
	i2c_stop();
	return dat;
}