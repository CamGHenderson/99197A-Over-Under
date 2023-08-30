#include "BrainUI.h"
#include "api.h"

#include "string.h"

#include "DefaultUIScript.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 272

#define CENTER_X DISPLAY_WIDTH / 2
#define CENTER_Y DISPLAY_HEIGHT / 2

// TODO: add support for custom styles or just make less default terrible style
// TODO: add support for button callbacks
// TODO: create better abstactions for each UI component type
// TODO: implement a data io system from UI

typedef struct
{
	uint16_t x;
	uint16_t y;
} Vec2u;

bool initialized = false;

lv_obj_t** objects = NULL;

lv_obj_t* parent = NULL;
lv_obj_t** tabs = NULL;
int16_t currentTab;

Vec2u pos;
Vec2u size;
bool centerModelSpace;

void setPosition(uint16_t x, uint16_t y)
{
	pos.x = x;
	pos.y = y;
}

void setSize(uint16_t x, uint16_t y)
{
	size.x = x;
	size.y = y;
}

lv_obj_t* getTarget()
{
	if(currentTab < 0)
		return parent;
	
	return tabs[currentTab];
}

uint16_t addObject(lv_obj_t* object)
{
	static uint16_t count = 0;

	uint16_t finalX = pos.x;
	uint16_t finalY = pos.y;
	
	if(centerModelSpace)
	{
		finalX -= (lv_obj_get_width(object) / 2);
		finalY -= (lv_obj_get_height(object) / 2);
	}
	
	lv_obj_align(object, NULL, LV_ALIGN_IN_TOP_LEFT, finalX, finalY);

	if(objects == NULL)
		objects = (lv_obj_t**)malloc(sizeof(lv_obj_t*));
	else
		objects = (lv_obj_t**)realloc(objects, (count + 1) * sizeof(lv_obj_t*));
	
	uint16_t index = count;
	objects[index] = object;
	count++;
	
	return index;
}

uint16_t createButton(const char* string)
{
	lv_obj_t* btn = lv_btn_create(getTarget(), NULL);
	lv_obj_set_size(btn, size.x, size.y);
	
	lv_obj_t* label = lv_label_create(btn, NULL);
	lv_label_set_text(label, string);
	
	uint16_t id = addObject(btn);
	addObject(label);
	return id;
}

uint16_t createLabel(const char* string)
{
	lv_obj_t* obj = lv_label_create(getTarget(), NULL);
	lv_label_set_text(obj, string);
	lv_label_set_align(obj, LV_LABEL_ALIGN_CENTER);
	return addObject(obj);
}

void initializeStyle()
{
	
}

void initializeTabs()
{
	parent = lv_tabview_create(lv_scr_act(), NULL);
	currentTab = -1;
}

uint16_t createTab(const char* name)
{
	static uint16_t count = 0;
	
	if(tabs == NULL)
		tabs = (lv_obj_t**)malloc(sizeof(lv_obj_t*));
	else
		tabs = (lv_obj_t**)realloc(tabs, (count + 1) * sizeof(lv_obj_t*));
		
	uint16_t index = count; 
	tabs[index] = lv_tabview_add_tab(parent, name);
	count++;
	
	return index;
}

void setTab(int16_t tabIndex)
{
	currentTab = tabIndex;
}

void initializeTransform()
{
	pos.x = 0;
	pos.y = 0;
	
	size.x = 0;
	size.y = 0;

	centerModelSpace = true;
}

void constructUI(const char* sourceScript)
{
	char* scriptCopy = (char*)malloc(sizeof(char) * strlen(sourceScript));
	strcpy(scriptCopy, sourceScript);

	char** lines = NULL;
	
	char* seperators = "\n";
	char* line = strtok(scriptCopy, seperators);
	uint16_t lineCount = 0;
	uint16_t stringSize = 0;
	while(line != NULL)
	{
		lineCount++;
		stringSize += (strlen(line) * sizeof(char));
		if(lines == NULL)
		{
			lines = malloc(stringSize);
		}
		else
		{
			lines = realloc(lines, stringSize); 
		}
		
		//printf("%s\n", line);
		strcpy(lines[(lineCount - 1)], line);
		
		line = strtok(NULL, seperators);
	}

	for(uint16_t i = 0; i < lineCount; i++)
		printf("%s", lines[i]);
	
	free(line);
	free(lines);
	free(scriptCopy);
}

void initializeBrainUI()
{
	initializeStyle();
	initializeTabs();
	initializeTransform();	
	
	//constructUI(script);
	
	// construct UI
	uint16_t tab1 = createTab("Tab 1");
	uint16_t tab2 = createTab("Tab 2");
	uint16_t tab3 = createTab("Funny");
	
	setTab(tab1);
	setPosition(DISPLAY_WIDTH / 2, 100);
	setSize(200, 50);
	createButton("Test Button");

	setTab(tab2);
	setPosition(DISPLAY_WIDTH / 2, 30);
	createLabel("Test Label");
	
	setTab(tab3);
	
	LV_IMG_DECLARE(testImage);
	lv_obj_t* img = lv_img_create(getTarget(), NULL);
	lv_obj_align(img, NULL, LV_ALIGN_IN_TOP_LEFT, CENTER_X - 75, 25);
	lv_img_set_src(img, &testImage);

	// indicate that the UI is initialized
	initialized = true;
}

void updateBrainUI()
{
	// TODO: make error handler
	if(!initialized)
	{
		
	}
}

// TODO: ensure this actually cleans everything up
void freeBrainUI()
{
	free(parent);
}
