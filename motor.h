#ifndef __MOTOR_H
#define __MOTOR_H

#include "STC15Fxxxx.h"
#include "pid.h"

sbit motor1p=P0^2;
sbit motor1n=P0^3;
sbit motor2p=P0^4;
sbit motor2n=P0^5;
sbit motor3p=P0^6;
sbit motor3n=P0^7;
sbit motor4p=P2^0;
sbit motor4n=P4^4;

void motor_gpio_config();

void motor_contrl(pid_structdef *pid_structure);

#endif