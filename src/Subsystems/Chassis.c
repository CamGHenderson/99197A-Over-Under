#include "Chassis.h"

#include "api.h"

#include "../Motor.h"
#include <stdlib.h>

#define TEAM_CONFIG 2

Motor leftMotors[DRIVE_ASSEMBLY_MOTOR_COUNT];
Motor rightMotors[DRIVE_ASSEMBLY_MOTOR_COUNT];

void initializeChassis()
{
	if(TEAM_CONFIG == 1)
	{
		rightMotors[0] = initializeMotor(1, BLUE_GEARBOX, false);
		rightMotors[1] = initializeMotor(2, BLUE_GEARBOX, true);
		rightMotors[2] = initializeMotor(3, BLUE_GEARBOX, true);
		
		leftMotors[0] = initializeMotor(7, BLUE_GEARBOX, true);
		leftMotors[1] = initializeMotor(8, BLUE_GEARBOX, false);
		leftMotors[2] = initializeMotor(9, BLUE_GEARBOX, false);
	}
	else if(TEAM_CONFIG == 2) //The motor config for 99197T
	{
		rightMotors[0] = initializeMotor(1, GREEN_GEARBOX, true);
		rightMotors[1] = initializeMotor(2, GREEN_GEARBOX, false);
		rightMotors[2] = initializeMotor(3, GREEN_GEARBOX, true);
		
		leftMotors[0] = initializeMotor(7, GREEN_GEARBOX, false);
		leftMotors[1] = initializeMotor(8, GREEN_GEARBOX, true);
		leftMotors[2] = initializeMotor(9, GREEN_GEARBOX, false);
	}
}

// TODO make chassis control external to allow for autonomous control
void updateChassis()
{
	uint8_t leftInput = (uint8_t)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y);
	uint8_t rightInput = (uint8_t)controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_Y);
	
	driveMotors(leftMotors, DRIVE_ASSEMBLY_MOTOR_COUNT, leftInput);
	driveMotors(rightMotors, DRIVE_ASSEMBLY_MOTOR_COUNT, rightInput);
}
