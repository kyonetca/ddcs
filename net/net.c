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
#include <string.h>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../metainfo.h"
#include "../tools.h"

#define SOCKETNOTREADY 0
#define SOCKETISREADY 1

int SocketReady;

void HandleMessage(char *buffer, struct sockaddr_in *endpoint_remote) {
	debug_print(LEVEL_DEVELOPMENT, "buffer");
}

void *InitializeSocket(void * InitializeSocketArgs) {
	struct sockaddr_in endpoint_local;
	int sfd, err, sinlen = sizeof(struct sockaddr_in);
	char netbuffer[NETWORK_BUFFER_SIZE];
	struct sockaddr_in endpoint_remote;

	sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sfd == -1)
		debug_print(LEVEL_FATAL_ERROR, "Error while 'socket'!");
	else
		debug_print(LEVEL_VERBOSE, "Socket succesful opened!");

	memset(&endpoint_local, 0, sizeof(struct sockaddr_in));
	endpoint_local.sin_family = AF_INET;
	endpoint_local.sin_port = UPDPORT;
	endpoint_local.sin_addr.s_addr = htonl(INADDR_ANY);

	err = bind(sfd, (struct sockaddr *) &endpoint_local, sizeof(endpoint_local));

	if (err == -1)
		debug_print(LEVEL_FATAL_ERROR, "Error while 'bind'");
	else
		debug_print(LEVEL_DEBUG, "Bind succesful");

	SocketReady = SOCKETISREADY;
	
	debug_print(LEVEL_DEBUG, "Socket ready");

	err = 0;
	while (1) {

		err = recvfrom(sfd, &netbuffer, NETWORK_BUFFER_SIZE, 0, (struct sockaddr *)&endpoint_remote, &sinlen);
		if (err == -1)
			debug_print(LEVEL_ERROR, "Error while 'recvfrom'");
		else
			debug_print(LEVEL_DEBUG, "Recieved Packet");

		HandleMessage(netbuffer, &endpoint_remote);
	}

	close(sfd);

	return NULL;
}

void *InitializeHostConnection(void *InitializeHostConnection) {




	return NULL;
}

int InitNetwork() {
	
	// Initialize Socket in own thread
	pthread_t SocketInitializeThread, SearchThread;

	SocketReady = SOCKETNOTREADY;
	pthread_create(&SocketInitializeThread, NULL, InitializeSocket, NULL);

	// Connect to other hosts
	pthread_create(&SearchThread, NULL, InitializeHostConnection, NULL);

	while (!SocketReady) { usleep(1); }

	return 0;
}