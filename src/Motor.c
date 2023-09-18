#include "Motor.h"
#include "api.h"

Motor initializeMotor(uint8_t port, MotorGearbox gearbox, bool reversed)
{
	Motor motor;
	motor.port = port;
	motor.gearbox = gearbox;
	motor.reversed = reversed;
	return motor;
}

void driveMotors(Motor* motors, uint8_t count, int8_t speed)
{
	for(uint16_t i = 0; i < count; i++)
		motor_move(abs(motors[i].port), motors[i].reversed ? -speed : speed);
}
