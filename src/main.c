#include "main.h"

#include "Subsystems/Chassis.h"
#include "Subsystems/Intake.h"
#include "BrainUI.h"

#include <stdbool.h>

#define LOOP_DELAY 10

void initialize()
{
	// Initialize Subsystems
	initializeChassis();
	initializeIntake();
	
	// Initialize Telemetry / Configuration Tools
	initializeBrainUI();
}

void opcontrol()
{	
	while(true)
	{
		// Update Subsystems
    	updateChassis();
		updateIntake();
		
		// Update Telemetry / Configuration Tools
		updateBrainUI();
		
		// ensure program doesn't overwork v5 brain
		delay(LOOP_DELAY);		
	}
}
