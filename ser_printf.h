#ifndef __SER_PRINTF_H
#define __SER_PRINTF_H

#include "STC15Fxxxx.h"
#include "m6050.h"
#include "mathmod.h"
#include "pid.h"
#include <stdio.h>

void ser_printf_init();

//void print_m6050data();

void print_x(m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure);

void print_y(m6050_structdef *m6050_structure,mathmod_structdef *mathmod_structure);

//void print_pid(pid_structdef *pid_structure);

//void print_axyz(m6050_structdef *m6050_structure);

//void print_gxy(m6050_structdef *m6050_structure);

//void print_zerodrift(m6050_zerodriftdef *m6050_zerodrift);

#endif