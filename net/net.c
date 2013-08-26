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

void HandleMessage(char *buffer, int length, struct sockaddr_in *endpoint_remote) {
	debug_print(LEVEL_DEVELOPMENT, buffer);
}

void *InitializeSocket(void * InitializeSocketArgs) {
	struct sockaddr_in endpoint_local;
	int sfd, err, length;
	char netbuffer[NETWORK_BUFFER_SIZE];
	struct sockaddr_in endpoint_remote;
#if defined __CYGWIN__	
	int sinlen = sizeof(struct sockaddr);
#else
	unsigned int sinlen = sizeof(struct sockaddr);
#endif

	sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sfd == -1)
		debug_print(LEVEL_FATAL_ERROR, "Error while 'socket'!");
	else
		debug_print(LEVEL_VERBOSE, "Socket succesful opened!");

	memset(&endpoint_local, 0, sizeof(struct sockaddr_in));
	endpoint_local.sin_family = AF_INET;
	endpoint_local.sin_port = htons(UDPPORT);
	endpoint_local.sin_addr.s_addr = htonl(INADDR_ANY);

	err = bind(sfd, (struct sockaddr *) &endpoint_local, sizeof(struct sockaddr_in));
	
	if (err == -1)
		debug_print(LEVEL_FATAL_ERROR, "Error while 'bind'");
	else
		debug_print(LEVEL_DEBUG, "Bind succesful");

	SocketReady = SOCKETISREADY;
	
	debug_print(LEVEL_DEBUG, "Socket ready");

	err = 0;
	while (1) {
		debug_print(LEVEL_DEBUG, "Waiting for Incomming Packet");
		memset(&netbuffer, 0, NETWORK_BUFFER_SIZE);

		length = recvfrom(sfd, &netbuffer, NETWORK_BUFFER_SIZE - 1, 0, (struct sockaddr *)&endpoint_remote, &sinlen);
		if (length == -1)
			debug_print(LEVEL_ERROR, "Error while 'recvfrom'");
		else
			debug_print(LEVEL_DEBUG, "Recieved Packet");

		HandleMessage(netbuffer, length, &endpoint_remote);
	}
	
	close(sfd);

	return NULL;
}

void *InitializeHostConnection(void *InitializeHostConnection) {
	// Send Ping Packets every time to keep connection up2date

	struct sockaddr_in endpoint_remote;
	int sfd, err, keepaliveid, sinlen = sizeof(struct sockaddr_in);
	char buffer[NETWORK_BUFFER_MAX_LENGTH];

	sfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sfd == -1)
		debug_print(LEVEL_FATAL_ERROR, "Error while 'socket'!");
	else
		debug_print(LEVEL_VERBOSE, "Socket succesful opened!");

	memset(&endpoint_remote, 0, sizeof(struct sockaddr_in));
	endpoint_remote.sin_family = AF_INET;
	endpoint_remote.sin_port = htons(UDPPORT);
	
	err = inet_aton(REMOTE_HOST, &endpoint_remote.sin_addr);

	if (err == 0)
		debug_print(LEVEL_FATAL_ERROR, "inet_aton failed");

	keepaliveid = 0;

	while (1) {
		sprintf(buffer, "Hello World! KAID: %d", keepaliveid++);
		err = sendto(sfd, buffer, strlen(buffer), 0, (struct sockaddr *)&endpoint_remote, sinlen);
		if (err == -1)
			debug_print(LEVEL_ERROR, "Error while 'sendto'");
		else
			debug_print(LEVEL_DEBUG, "Sent Packet");
			
		sleep(1);
	}

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