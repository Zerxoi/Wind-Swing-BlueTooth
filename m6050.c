#include <stdio.h>
#include <math.h>
#include "STC15Fxxxx.h"
#include "m6050.h"
#include "i2c.h"

void m6050_init()
{
	i2c_writeadd(SlaveAddress,PWR_MGMT_1,0x00);
	i2c_writeadd(SlaveAddress,SMPLRT_DIV,0x07);
	i2c_writeadd(SlaveAddress,CONFIG,0x06);
	i2c_writeadd(SlaveAddress,GYRO_CONFIG,0x00);		//GYRO Full Scale  +/- 250
	i2c_writeadd(SlaveAddress,ACCEL_CONFIG,0x01);		//ACC Full Scale   +/- 2g
}

void m6050_initstruct(m6050_structdef *m6050_structure)	//Assigned one time
{
	m6050_structure->ax=0;
	m6050_structure->ay=0;
	m6050_structure->az=0;
	m6050_structure->gx=0;								//Can be omitted
	m6050_structure->gy=0;								//Can be omitted
	m6050_structure->angle_x=0.0;
	m6050_structure->angle_y=0.0;
}

int m6050_getvalue(unsigned char dvadd,unsigned char addhigh)
{
	unsigned char h,l;
	h=i2c_readadd(dvadd,addhigh);
	l=i2c_readadd(dvadd,addhigh+1);
	return (h<<8)+l;
}

void m6050_initzerodrift(m6050_zerodriftdef *m6050_zerodrift)
{
	m6050_zerodrift->ax=0;
	m6050_zerodrift->ay=0;
	m6050_zerodrift->az=0;
	m6050_zerodrift->gx=0;
	m6050_zerodrift->gy=0;
}
void m6050_getzerodrift(m6050_zerodriftdef *m6050_zerodrift)			//Initialize zero drift
{
	int n;
	long int sum_ax=0,sum_ay=0,sum_az=0,sum_gx=0,sum_gy=0;
	for (n=2000;n>0;n--)																						//次数加大，去除零点漂移效果稍好
	{
		sum_ax+=m6050_getvalue(SlaveAddress,ACCEL_XOUT_H);
		sum_ay+=m6050_getvalue(SlaveAddress,ACCEL_YOUT_H);
		sum_az+=m6050_getvalue(SlaveAddress,ACCEL_ZOUT_H);
		sum_gx+=m6050_getvalue(SlaveAddress,GYRO_XOUT_H);
		sum_gy+=m6050_getvalue(SlaveAddress,GYRO_YOUT_H);
	}
	m6050_zerodrift->ax=sum_ax/2000;
	m6050_zerodrift->ay=sum_ay/2000;
	m6050_zerodrift->az=sum_az/2000-16384;
	m6050_zerodrift->gx=sum_gx/2000;	
	m6050_zerodrift->gy=sum_gy/2000;
//	printf("ZERO DRIFT IS DONE\n");
//	printf("m6050_zerodrift->ax=%f\n",m6050_zerodrift->ax);
//	printf("m6050_zerodrift->ay=%f\n",m6050_zerodrift->ay);
//	printf("m6050_zerodrift->az=%f\n",m6050_zerodrift->az);
//	printf("m6050_zerodrift->gx=%f\n",m6050_zerodrift->gx);
//	printf("m6050_zerodrift->gy=%f\n",m6050_zerodrift->gy);
}

void m6050_getstructure(m6050_structdef *m6050_structure,m6050_zerodriftdef *m6050_zerodrift)		//Get Clear Zero Drift Structure
{
	m6050_structure->ax=m6050_getvalue(SlaveAddress,ACCEL_XOUT_H)-m6050_zerodrift->ax;
	m6050_structure->ay=m6050_getvalue(SlaveAddress,ACCEL_YOUT_H)-m6050_zerodrift->ay;
	m6050_structure->az=m6050_getvalue(SlaveAddress,ACCEL_ZOUT_H)-m6050_zerodrift->az;
	m6050_structure->gx=m6050_getvalue(SlaveAddress,GYRO_XOUT_H)-m6050_zerodrift->gx;
	m6050_structure->gy=m6050_getvalue(SlaveAddress,GYRO_YOUT_H)-m6050_zerodrift->gy;
}