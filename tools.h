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

#define LEVEL_FATAL_ERROR 10
#define LEVEL_ERROR 11
#define LEVEL_WARNING 12
#define LEVEL_DEPRECATED 13
#define LEVEL_NOTICE 14

#define LEVEL_MESSAGE 1
#define LEVEL_VERBOSE 2
#define LEVEL_DEBUG 3
#define LEVEL_DEVELOPMENT 4

void debug_print(int Level, char *Message);
