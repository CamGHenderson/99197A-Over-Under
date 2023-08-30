#include "Chassis.h"

#include "api.h"

#include "../Motor.h"
#include <stdlib.h>

Motor leftMotors[DRIVE_ASSEMBLY_MOTOR_COUNT];
Motor rightMotors[DRIVE_ASSEMBLY_MOTOR_COUNT];

void initializeChassis()
{
	leftMotors[0] = initializeMotor(1, BLUE_GEARBOX, false);
	leftMotors[1] = initializeMotor(2, BLUE_GEARBOX, true);
	leftMotors[2] = initializeMotor(3, BLUE_GEARBOX, true);
	
	rightMotors[0] = initializeMotor(8, BLUE_GEARBOX, true);
	rightMotors[1] = initializeMotor(9, BLUE_GEARBOX, false);
	rightMotors[2] = initializeMotor(10, BLUE_GEARBOX, false);
}

void updateChassis()
{
	uint8_t leftInput = (uint8_t)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y);
	uint8_t rightInput = (uint8_t)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_Y);
	
	driveMotors(leftMotors, DRIVE_ASSEMBLY_MOTOR_COUNT, leftInput);
	driveMotors(rightMotors, DRIVE_ASSEMBLY_MOTOR_COUNT, rightInput);
}
