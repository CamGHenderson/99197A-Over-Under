#pragma once
#include <stdint.h>
#include "Motor.h"

void loadRobotModel();

char* getTeamNumber();
char* getTeamName();
char* getRobotName();
char getTeamLetter();

uint16_t getDriveMotorCount();
uint16_t getDriveAssemblyMotorCount();

Motor* getLeftMotors();
Motor* getRightMotors();


