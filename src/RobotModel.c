#include "RobotModel.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ErrorHandler.h"

#define DEBUG_MODE 0

typedef struct
{
	char* data;
	size_t length;
} String;

typedef struct
{
	String* lines;
	uint16_t count;
} StringArray;

typedef enum
{
	NONE = 0,
	ROBOT_DETAILS = 1,
	CHASSIS = 2,
	SUBSYSTEM = 3
} ComponentType;

// robot model data
char* teamNumber = NULL;
char* teamName = NULL;
char* robotName = NULL;
char teamLetter = ' ';

uint16_t driveMotorCount;
Motor* leftMotors = NULL;
Motor* rightMotors = NULL;

char* getTeamNumber()
{
	return teamNumber;
}

char* getTeamName()
{
	return teamName;
}

char* getRobotName()
{
	return robotName;
}

char getTeamLetter()
{
	return teamLetter;
}

uint16_t getDriveMotorCount()
{
	return driveMotorCount;
}

uint16_t getDriveAssemblyMotorCount()
{
	return driveMotorCount / 2;
}

Motor* getLeftMotors()
{
	return leftMotors;
}

Motor* getRightMotors()
{
	return rightMotors;
}

int32_t getFileLineCount(const char* fileName)
{
	FILE* file = fopen(fileName, "r");

	if(file)
	{
		int32_t count = 0;
		char ch;
	
		while(!feof(file))
		{
			ch = fgetc(file);
			if(ch == '\n')
			{
				count++;
			}
		}
		
		return count;
	}
	
	return 0;
}

StringArray loadFileContents()
{
	StringArray fc;
	fc.lines = NULL;

	const char* fileName = "Model.rmsl";
	FILE* file = fopen(fileName, "r");

	if(file)
	{	
		char* buffer = NULL;
    	size_t len = 0;
    	ssize_t read;	
		
		uint16_t currentIndex = 0;
		fc.count = getFileLineCount(fileName);
		
		fc.lines = (String*)malloc(sizeof(String) * fc.count);
		
		while ((read = getline(&fc.lines[currentIndex].data, &fc.lines[currentIndex].length, file)) != -1)
			currentIndex++;
		
		fclose(file);
	}
	
	return fc;
}

void printStringArray(StringArray sa)
{
	for(uint16_t i = 0; i < sa.count; i++)
		printf("%s\n", sa.lines[i].data);
}

// fuck you!
void printFileContents(StringArray sa)
{
	for(uint16_t i = 0; i < sa.count; i++)
		printf("%s", sa.lines[i].data);
}

bool isVaildCharacter(char c)
{
	if((c >= '0' && c <= '~') || (c == '+') || (c == '-'))
		return true;
		
	return false;
}

uint16_t getWordCount(String string)
{
	bool onWord = false;
	uint16_t count = 0;
		
	for(uint16_t i = 0; i < string.length; i++)
	{
		char c = string.data[i];
		if(isVaildCharacter(c))
		{
			if(!onWord)
				count++;
			
			onWord = true;
		}
		else if(onWord)
			onWord = false;
	}
	
	return count;
}

// i'm a bad person
StringArray parseWords(String string)
{
	StringArray sa;
	sa.count = getWordCount(string);
	sa.lines = (String*)malloc(sizeof(String) * sa.count);
	
	int16_t startIndex = -1;
	uint16_t currentWordIndex = 0;

	bool onWord = false;
	for(uint16_t i = 0; i < string.length; i++)
	{
		char c = string.data[i];
		if(isVaildCharacter(c))
		{
			if(!onWord)
				startIndex = i;
			
			onWord = true;
		}
		else if(onWord)
		{
			uint16_t length = (i - startIndex);
						
			onWord = false;
			sa.lines[currentWordIndex].data = malloc(sizeof(char) * (length)); 
			sa.lines[currentWordIndex].data[length] = '\0';
			sa.lines[currentWordIndex].length = length;
			
			for(uint16_t j = 0; j < length; j++)
			{
				char c = string.data[j + startIndex];
				sa.lines[currentWordIndex].data[j] = c;
			}
						
			startIndex = -1;
			currentWordIndex++;
		}		
	}
	
	return sa;
}

bool isSameString(String s1, char* s2)
{
	if(strcmp(s1.data, s2) == 0)
		return true;
	
	return false;
}

ComponentType getComponentType(StringArray sa, uint16_t lineIndex)
{
	// component type specification process
	if(isSameString(sa.lines[0], "ComponentType:"))
	{
		if(isSameString(sa.lines[1], "RobotDetails"))
		{	
			if(DEBUG_MODE)
				printf("%s\n", "DEBUG: Component type set to ROBOT_DETAILS");
			
			return ROBOT_DETAILS;
		}
		else if(isSameString(sa.lines[1], "Chassis"))
		{
			if(DEBUG_MODE)
				printf("%s\n", "DEBUG: Component type set to CHASSIS");
				
			return CHASSIS;
		}
		else if(isSameString(sa.lines[1], "Subsystem"))
		{	
			if(DEBUG_MODE)
				printf("%s\n", "DEBUG: Component type set to SUBSYSTEM");
				
			return SUBSYSTEM;
		}
		else
		{
			throwScriptError("invalid component type specification", lineIndex);
		}
	}
	else
	{
		throwScriptError("component type specification is required before attributes can be defined", lineIndex);
	}
	
	return NONE;
}

void handleRobotDetailsComponent(StringArray sa, uint16_t lineIndex)
{
	if(sa.count > 2)
		throwScriptError("invalid additional attribute specification", lineIndex);

	// TODO fix sketch attribute system without soild error handling
	if(isSameString(sa.lines[0], "TeamNumber:"))
	{
		// TODO remove underscores	
		teamNumber = sa.lines[1].data;
	}
	else if(isSameString(sa.lines[0], "TeamName:"))
	{
		teamName = sa.lines[1].data;
	}
	else if(isSameString(sa.lines[0], "RobotName:"))
	{
		robotName = sa.lines[1].data;
	}
	else if(isSameString(sa.lines[0], "TeamLetter:"))
	{
		teamLetter = sa.lines[1].data[0];
	}
	else
		throwScriptError("attribute type invalid", lineIndex);
}

Motor* parseMotorData(StringArray sa, uint16_t lineIndex)
{
	Motor* motorsPtr = (Motor*)malloc(sizeof(Motor) * getDriveAssemblyMotorCount());
	for(uint16_t i = 1; i < getDriveAssemblyMotorCount() + 1; i++)
	{		
		bool reversed;
		if(sa.lines[i].data[0] == '+')
			reversed = false;
		else if(sa.lines[i].data[0] == '-')
			reversed = true;
		else
			throwScriptError("reverse specifier symbol invaild must be +/-", lineIndex);
		
		motorsPtr[i - 1].reversed = reversed;
		
		uint16_t sublen = (sa.lines[i].length - 1);
		char* portStr = (char*)malloc(sizeof(char) * (sa.lines[i].length - 2));
		strncpy(portStr, &sa.lines[i].data[1], sublen);
		portStr[sublen - 1] = '\0';
		
		motorsPtr[i - 1].port = atoi(portStr);
		
		switch(sa.lines[i].data[sa.lines[i].length])
		{
			case 'b':
			{
				motorsPtr[i - 1].gearbox = BLUE_GEARBOX;
				break;
			}
			case 'r':
			{
				motorsPtr[i - 1].gearbox = RED_GEARBOX;
				break;
			}
			case 'g':
			{
				motorsPtr[i - 1].gearbox = GREEN_GEARBOX;
				break;
			}
		}
	}
	
	return motorsPtr;
}

void handleChassisComponent(StringArray sa, uint16_t lineIndex)
{
	// TODO: make sure to get drive motor count first before motor data
	if(isSameString(sa.lines[0], "DriveMotorCount:"))
		driveMotorCount = atoi(sa.lines[1].data);
	else if(isSameString(sa.lines[0], "LeftMotors:"))
	{
		leftMotors = parseMotorData(sa, lineIndex);
	}
	else if(isSameString(sa.lines[0], "RightMotors:"))
	{
		rightMotors = parseMotorData(sa, lineIndex);
	}
}

void parseLine(String line, uint16_t lineIndex)
{
	static bool inComponent = false;
	static ComponentType type = NONE;
	
	StringArray sa = parseWords(line);		
	
	// make sure there is text on the line
	if(sa.count > 0)
	{
		if(inComponent)
		{
			if(sa.lines[0].data[0] == '}')
			{
				inComponent = false;
				type = NONE;
				
				if(DEBUG_MODE)
					printf("%s\n\n", "DEBUG: End Component");
			}
			else if(type == NONE)
			{		
				type = getComponentType(sa, lineIndex);
			}
			else if(type == ROBOT_DETAILS)
			{
				handleRobotDetailsComponent(sa, lineIndex);
			}
			else if(type == CHASSIS)
			{
				handleChassisComponent(sa, lineIndex);
			}
			else if(type == SUBSYSTEM)
			{
				
			}
		}
		else
		{
			if(sa.count > 1)
				throwScriptError("incorrect component scope initializer", lineIndex);
			else if(sa.lines[0].data[0] == '{')
			{
				inComponent = true;
				
				if(DEBUG_MODE)
					printf("%s\n", "DEBUG: Start Component");
			}
		}
	}
}

void parseScript(StringArray fc)
{
	for(uint16_t i = 0; i < fc.count; i++)
		parseLine(fc.lines[i], i);
}

void loadRobotModel()
{
	// TODO: fix potential memory leak(s)
	StringArray fc = loadFileContents();
	parseScript(fc);
}
