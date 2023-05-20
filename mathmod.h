#ifndef __MATHMOD_H
#define __MATHMOD_H

#include "bluetooth.h"
#define H 84.0
//#define H 73.9

typedef struct
{
	float sumtime;
	float angle_x;
	float angle_y;
}	mathmod_structdef;

void mathmod_initstruct(mathmod_structdef *mathmod_structure);

void mathmod_getSTILL(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure);

void mathmod_getSHM(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure);

void mathmod_getUCM(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure);

#endif