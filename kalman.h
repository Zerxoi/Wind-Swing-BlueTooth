#ifndef __KALMAN_H
#define __KALMAN_H

#include "m6050.h"
#include <math.h>
//dt ����ʱ��
//Kalman Fliter Args
//#define dt 0.01				//Kalman Fliter ����ʱ��
#define Q_angle 0.001 //�Ƕ��������Ŷ�
#define Q_gyro 0.005	//���ٶ��������Ŷ�
#define R_angle 0.5
#define C_0 1

void Kalman_Filter_x(m6050_structdef *m6050_structure,float accanglex,float dpsx);

//void Kalman_Filter_y(m6050_structdef *m6050_structure,float accangley,float dpsy);

float acc2anglex(m6050_structdef *m6050_structure);

//float acc2angley(m6050_structdef *m6050_structure);

float gyro2dps(int gyro);

void angle_calcu(m6050_structdef *m6050_structure);

#endif