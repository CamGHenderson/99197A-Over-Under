#include "BrainUI.h"
#include "api.h"

#include "string.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 272

bool initialized = false;
lv_obj_t** objects = NULL;

void addObject(lv_obj_t* object)
{
	if(objects == NULL)
		objects = (lv_obj_t**)malloc(sizeof(lv_obj_t*));
	else
		objects = (lv_obj_t**)realloc(objects, sizeof(objects) + sizeof(lv_obj_t*));
		
	objects[(sizeof(objects) / sizeof(lv_obj_t*)) - 1] = object;
}

void createLabel(const char* string)
{
	//lv_obj_t* object = 	
}

void initializeBrainUI()
{	
	createLabel("Test");
	createLabel("And another test");
	
	initialized = true;
}

void updateBrainUI()
{
	// make error handler
	if(!initialized)
	{
		
	}
}
