#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	BLUE_GEARBOX = 1,
	GREEN_GEARBOX = 2,
	RED_GEARBOX = 3
} MotorGearbox;

typedef struct
{
	uint8_t port;
	MotorGearbox gearbox; 
	bool reversed;
} Motor;

Motor initializeMotor(uint8_t port, MotorGearbox gearbox, bool reversed);
void driveMotors(Motor* motors, uint8_t count, int8_t speed);
