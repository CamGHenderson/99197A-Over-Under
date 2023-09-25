#include "wings.h"

#include "api.h"

void wings_Pneumatics_Initialize()
{
    adi_pin_mode('A', OUTPUT);
    adi_digital_write('A', LOW);
}

void wings_Pneumatics_Trigger()
{
    if(controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_A))
		adi_digital_write('A', HIGH);
    else
        adi_digital_write('A', LOW);
}