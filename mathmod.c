#include <stdio.h>
#include <math.h>
#include "mathmod.h"
#include "timer0.h"

//extern float thita_x;
//extern float thita_y;

void mathmod_initstruct(mathmod_structdef *mathmod_structure)
{
	mathmod_structure->sumtime=0;
	mathmod_structure->angle_x=0;
	mathmod_structure->angle_y=0;
}

void mathmod_getSTILL(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure)
{
	mathmod_structure->sumtime+=dt;
	mathmod_structure->angle_x=bluetooth_structure->angle_x;
	mathmod_structure->angle_y=bluetooth_structure->angle_y;
}

void mathmod_getSHM(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure)
{
	mathmod_structure->sumtime+=dt;
	mathmod_structure->angle_x=bluetooth_structure->angle_x*sin(4.0428*mathmod_structure->sumtime);
	//sqrt(g/l)=4.0428
	mathmod_structure->angle_y=bluetooth_structure->angle_y*sin(4.0428*mathmod_structure->sumtime);
}

void mathmod_getUCM(mathmod_structdef *mathmod_structure,bluetooth_structdef *bluetooth_structure)							//uniform circular motion
{
	mathmod_structure->sumtime+=dt;
	mathmod_structure->angle_x=bluetooth_structure->angle_x*sin(4.0428*mathmod_structure->sumtime);
	mathmod_structure->angle_y=bluetooth_structure->angle_x*cos(4.0428*mathmod_structure->sumtime);		// phase = pi/2 逆时针旋转
//	mathmod_structure->thitax=10*sin(4.0428*mathmod_structure->sumtime+4.7124);		// phase = 3*pi/2 顺时针旋转
}