#pragma once

#include <winsock.h>
#include <string>
#include <iostream>

class TcpClient {

public:
	TcpClient(SOCKET client) : clientSocket(client)
	{
		
	}

	~TcpClient()
	{

	}

	SOCKET clientSocket;

	void parseData(std::string str);

private:
	

};




