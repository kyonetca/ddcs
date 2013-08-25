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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "metainfo.h"
#include "net/net.h"

int main(int argc, char **argv) {
	printf("%s%s%s\n%s\n%s\n", 
		"DDCS Version [", VERSION, "] Copyright (C) 2013 Jan Peter Koenig",
		"This is free software, and you are welcome to redistribute it under", "certain conditions."
	);

	InitNetwork();

	// Hold Application in Stand-By
	while (1) { usleep(1); }

	return 0;
}