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

typedef struct
{
	Motor* motors;
	uint16_t count;
} MotorGroup;

Motor initializeMotor(uint8_t port, MotorGearbox gearbox, bool reversed);
MotorGroup initializeMotorGroup(uint16_t count);
void driveMotors(Motor* motors, uint8_t count, int8_t speed);
