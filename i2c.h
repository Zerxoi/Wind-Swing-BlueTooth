#ifndef __I2C_H__
#define __I2C_H__  

sbit scl=P0^0;
sbit sda=P0^1;

void delayus();

void i2c_init();

void i2c_start();

void i2c_stop();

void i2c_response();

void i2c_write(unsigned char dat);

unsigned char i2c_read();

void i2c_writeadd(unsigned char dvadd,unsigned char wdadd,unsigned char dat);	//dvadd:Device Adress wdadd:Word Address

unsigned char i2c_readadd(unsigned char dvadd,unsigned char wdadd);

#endif