#include "stdafx.h"
#include "tcp_server.h"
#include <functional>


static void 
insertClient(SOCKET sClient)
{

}


static void
delClient(SOCKET sClient)
{
	

	

}


#define MSGSIZE    1024
void 
TcpServer::Run()
{
	SOCKET  sClient;
	SOCKADDR_IN client;
	int	iaddrSize = sizeof(SOCKADDR_IN);
	fd_set         fdread;

	while (TRUE)
	{
		FD_ZERO(&fdread);
		struct timeval tv = { 1, 0 };
		int ret;
		char           szMessage[MSGSIZE];
		FD_SET(sListen, &fdread);
		for (auto it = clients.begin(); it != clients.end(); it++)
		{
			FD_SET(it->clientSocket, &fdread);
		}
		// We only care read event    
		ret = select(0, &fdread, NULL, NULL, &tv);

		if (ret == 0)
		{
			// Time expired   
			continue;
		}

		if (FD_ISSET(sListen, &fdread))
		{
			// Accept a connection   
			sClient = accept(sListen, (struct sockaddr *)&client, &iaddrSize);
			printf("Accepted client:%s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
			// Add socket to fdTotal   
			//insertClient(sClient);
			TcpClient client(sClient);
			clients.push_back(client);
		}
		for (auto it = clients.begin(); it != clients.end(); )
		{
			if (FD_ISSET(it->clientSocket, &fdread))
			{
				// A read event happened on pfdTotal->fd_array[i]    
				ret = recv(it->clientSocket, szMessage, MSGSIZE, 0);
				if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
				{
					// Client socket closed        
					printf("Client socket %d closed.\n", it->clientSocket);
					closesocket(it->clientSocket);
					it = clients.erase(it);
					continue;
				}
				else
				{       // We received a message from client  
					szMessage[ret] = '\0';
					it->parseData(szMessage);
					send(it->clientSocket, szMessage, strlen(szMessage), 0);
				}
			}
			it++;
		}
	}

}

