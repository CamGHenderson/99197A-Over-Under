#include "ErrorHandler.h"

#include <stdio.h>
#include <stdlib.h>

// FIX: make this give errors to the appropriate data stream
void throwScriptError(const char* msg, uint16_t line)
{
	printf("error on line %i: %s", line + 1, msg);
	exit(-1);	
}
