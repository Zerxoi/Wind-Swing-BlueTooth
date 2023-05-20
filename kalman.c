#include "kalman.h"
#include "m6050.h"
#include "timer0.h"
void Kalman_Filter_x(m6050_structdef *m6050_structure,float accanglex,float dpsx)//angleAx 和 gyroGy
{
	static float P[2][2] = {{ 1, 0 },{ 0, 1 }};
	static float Pdot[4] ={ 0,0,0,0};
	static float q_bias=0, angle_err=0, PCt_0=0, PCt_1=0, E=0, K_0=0, K_1=0, t_0=0, t_1=0;
	static float Angle_dot=0;
	m6050_structure->angle_x+=(dpsx-q_bias) * dt;
	angle_err = accanglex - m6050_structure->angle_x;
		
	Pdot[0]=Q_angle - P[0][1] - P[1][0];
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;
	P[0][0] += Pdot[0] * dt;
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;
		
	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];
	E = R_angle + C_0 * PCt_0;
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
		
	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];
	P[0][0] -= K_0 * t_0;
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;
	m6050_structure->angle_x += K_0 * angle_err;				//最优角度
	q_bias += K_1 * angle_err;
	Angle_dot = dpsx-q_bias;				//最优角速度
}

void Kalman_Filter_y(m6050_structdef *m6050_structure,float accangley,float dpsy)//angleAx 和 gyroGy
{
	static float P[2][2] = {{ 1, 0 },{ 0, 1 }};
	static float Pdot[4] ={ 0,0,0,0};
	static float q_bias=0, angle_err=0, PCt_0=0, PCt_1=0, E=0, K_0=0, K_1=0, t_0=0, t_1=0;
	static float Angle_dot=0;
	m6050_structure->angle_y+=(dpsy-q_bias) * dt;
	angle_err = accangley - m6050_structure->angle_y;
		
	Pdot[0]=Q_angle - P[0][1] - P[1][0];
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;
	P[0][0] += Pdot[0] * dt;
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;
		
	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];
	E = R_angle + C_0 * PCt_0;
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
		
	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];
	P[0][0] -= K_0 * t_0;
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;
	m6050_structure->angle_y += K_0 * angle_err;				//最优角度
	q_bias += K_1 * angle_err;
	Angle_dot = dpsy-q_bias;				//最优角速度
}

float acc2anglex(m6050_structdef *m6050_structure)//欧拉角?转角
{
	float anglex;
	anglex=atan2(m6050_structure->ay,m6050_structure->az)*57.295828;		//	180/pi~=57.295828
	return anglex;
}

float acc2angley(m6050_structdef *m6050_structure)
{
	float angley;
	angley=atan2(-1*m6050_structure->ax,m6050_structure->az)*57.295828;		//	180/pi~=57.295828
	return angley;
}

float gyro2dps(int gyro)
{
	float dps;
	dps=gyro/131.072;		//		2^16/500=131.072
	return dps;
}

void angle_calcu(m6050_structdef *m6050_structure)
{
	float accanglex,dpsx;
	float accangley,dpsy;
	accanglex=acc2anglex(m6050_structure);
	accangley=acc2angley(m6050_structure);
	dpsx=gyro2dps(m6050_structure->gx);
	dpsy=gyro2dps(m6050_structure->gy);
	Kalman_Filter_x(m6050_structure,accanglex,dpsx);
	Kalman_Filter_y(m6050_structure,accangley,dpsy);
}