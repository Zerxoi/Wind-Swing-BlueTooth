#ifndef __PID_H
#define __PID_H
#include "m6050.h"
#include "mathmod.h"

#define KP1 360
#define KI1 12
#define KD1 14000

#define KP2 1300
#define KI2 2.7
#define KD2 33000

#define KP3 200
#define KI3 2
#define KD3 80000

#define XIntegralMax 1000
#define XIntegralMin -1000
#define YIntegralMax 1000
#define YIntegralMin -1000
#define UnableValue    65536.0			//任意设定x_pre_error,y_pre_error不可能取到的值
typedef struct
{
	float kp;
	float ki;
	float kd;
	float x_integral;
	float x_pre_error;
	float x_output;
	float y_integral;
	float y_pre_error;
	float y_output;
}	pid_structdef;

void pid_initstruct(pid_structdef *pid_structure);

void pid_getstruct(pid_structdef *pid_structure,m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure);

#endif