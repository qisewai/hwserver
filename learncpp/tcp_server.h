#pragma once

#include <winsock.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "tcp_client.h"

#pragma comment(lib, "ws2_32.lib")

class TcpServer
{
public:
	TcpServer(int port = 7734)
	{
		// init and listen tcp server

		SOCKADDR_IN local;

		// Initialize Windows socket library 
		WSAStartup(0x0202, &wsaData);
		// Create listening socket
		sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Bind 
		local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		bind(sListen, (struct sockaddr *)&local, sizeof(SOCKADDR_IN));
		// Listen
		listen(sListen, 3);

	}
	~TcpServer() {}


	void Run();

	std::vector<TcpClient> clients;

private:
	WSADATA wsaData;
	SOCKET  sListen;


};



