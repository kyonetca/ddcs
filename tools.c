/*
    Dynamic Decentralized Cloud System
    Copyright (C) 2013  Jan Peter König

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LEVEL_FATAL_ERROR 10
#define LEVEL_ERROR 11
#define LEVEL_WARNING 12
#define LEVEL_DEPRECATED 13
#define LEVEL_NOTICE 14

#define LEVEL_MESSAGE 1
#define LEVEL_VERBOSE 2
#define LEVEL_DEBUG 3
#define LEVEL_DEVELOPMENT 4

void get_level_string(char *string, int Level) {
	if (Level == LEVEL_FATAL_ERROR)
		sprintf(string, "%s", "Fatal Error");
	else if (Level == LEVEL_ERROR)
		sprintf(string, "%s", "Error");
	else if (Level == LEVEL_WARNING)
		sprintf(string, "%s", "Warning");
	else if (Level == LEVEL_DEPRECATED)
		sprintf(string, "%s", "Deprecated");
	else if (Level == LEVEL_NOTICE)
		sprintf(string, "%s", "Notice");
	else if (Level == LEVEL_MESSAGE)
		sprintf(string, "%s", "Message");
	else if (Level == LEVEL_VERBOSE)
		sprintf(string, "%s", "Verbose");
	else if (Level == LEVEL_DEBUG)
		sprintf(string, "%s", "Debug");
	else if (Level == LEVEL_DEVELOPMENT)
		sprintf(string, "%s", "Development");
	else
		sprintf(string, "%s", "Level not defined");
	return;
}

void debug_print(int Level, char *Message) {
	time_t timestamp;
	char timestring[128], levelstring[128];
	struct tm* tm_info;

    time(&timestamp);
    tm_info = localtime(&timestamp);

    //strftime(timestring, 128, "%a %d.%m.%Y - %H:%M:%S", tm_info);
	strftime(timestring, 128, "%c", tm_info);

	get_level_string(levelstring, Level);

	printf("[%s] [%s] %s\n", timestring, levelstring, Message);
}
