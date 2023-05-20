#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

typedef struct
{
	int mode;
	float r;
	float angle;
	float angle_x;
	float angle_y;
}	bluetooth_structdef;

void bluetooth_init();

void bluetooth_initstruct(bluetooth_structdef *bluetooth_structure);

#endif