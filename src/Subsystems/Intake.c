#include "Intake.h"

#include "api.h"

#define INTAKE_MOTOR_PORT 6

void initializeIntake()
{
	motor_set_brake_mode(INTAKE_MOTOR_PORT, E_MOTOR_BRAKE_COAST);
}

void updateIntake()
{
	if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R1))
		motor_move(INTAKE_MOTOR_PORT, 255);
	else if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R2))
		motor_move(INTAKE_MOTOR_PORT, -255);
	else
		motor_move(INTAKE_MOTOR_PORT, 0);
}
