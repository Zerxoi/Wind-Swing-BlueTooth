#include "pid.h"
#include "m6050.h"
#include "mathmod.h"
//Tip: KP,KI,KD set in "pid.h"

void pid_initstruct(pid_structdef *pid_structure)
{
	pid_structure->kp=0;
	pid_structure->ki=0;
	pid_structure->kd=0;
	pid_structure->x_integral=0;
	pid_structure->x_pre_error=UnableValue;
	pid_structure->x_output=0;
	pid_structure->y_integral=0;
	pid_structure->y_pre_error=UnableValue;
	pid_structure->y_output=0;
	
}

void pid_getstruct(pid_structdef *pid_structure,m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure)
{
	float x_error,x_derivative;
	float y_error,y_derivative;
	x_error=mathmod_structure->angle_x-m6050_structure->angle_x;
	pid_structure->x_integral+=x_error;
	if (pid_structure->x_integral>XIntegralMax)
		pid_structure->x_integral=XIntegralMax;
	else if (pid_structure->x_integral<XIntegralMin)
		pid_structure->x_integral=XIntegralMin;
	if (pid_structure->x_pre_error==UnableValue)		//如果x_pre_error取到不可能值，则说明暂时没有x_pre_error，即没有微分项
		x_derivative=0;
	else
		x_derivative=x_error-pid_structure->x_pre_error;
	pid_structure->x_pre_error=x_error;
	pid_structure->x_output=pid_structure->kp*x_error+pid_structure->ki*pid_structure->x_integral+pid_structure->kd*x_derivative;
	
	y_error=mathmod_structure->angle_y-m6050_structure->angle_y;
	pid_structure->y_integral+=y_error;
	if (pid_structure->y_integral>YIntegralMax)
		pid_structure->y_integral=YIntegralMax;
	else if (pid_structure->y_integral<YIntegralMin)
		pid_structure->y_integral=YIntegralMin;
	if (pid_structure->y_pre_error==UnableValue)		//如果y_pre_error取到不可能值，则说明暂时没有y_pre_error，即没有微分项
		y_derivative=0;
	else
		y_derivative=y_error-pid_structure->y_pre_error;
	pid_structure->y_pre_error=y_error;
	pid_structure->y_output=pid_structure->kp*y_error+pid_structure->ki*pid_structure->y_integral+pid_structure->kd*y_derivative;
}
