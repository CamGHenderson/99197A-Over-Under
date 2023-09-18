#include "Catapult.h"

#include "api.h"
#include "../Motor.h"

#define MOTOR_PORT 11
#define LIMIT_SWITCH_PORT 'A'

Motor motor;

void initializeCatapult()
{
	motor = initializeMotor(MOTOR_PORT, RED_GEARBOX, true);
}

void updateCatapult()
{
	/*if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_A))
		motor_move(MOTOR_PORT, 255);*/
	if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_B))
		motor_move(MOTOR_PORT, -255);
	else
		motor_move(MOTOR_PORT, 0);
}
