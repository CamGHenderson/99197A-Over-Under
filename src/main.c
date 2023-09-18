#include "main.h"

#include "Subsystems/Chassis.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Catapult.h"
#include "UI/BrainUI.h"

#include <stdbool.h>

#define LOOP_DELAY 10

void initialize()
{
	// Initialize Subsystems
	initializeChassis();
	initializeIntake();
	initializeCatapult();
	
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
		updateCatapult();
		
		// Update Telemetry / Configuration Tools
		updateBrainUI();
		
		// ensures program doesn't overwork v5 brain
		delay(LOOP_DELAY);		
	}
	
	freeBrainUI();
}
