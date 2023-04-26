#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

using namespace std;

int main()
{
	WSADATA wsaData;
	SOCKET _socket;
	sockaddr_in endPoint;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	endPoint.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &endPoint.sin_addr);
	endPoint.sin_port = htons(1234);
	connect(_socket, (SOCKADDR*)&endPoint, sizeof(endPoint));


	char buf[1024]{};
	cout << "Enter the message->";
	cin.getline(buf, 1024);
	send(_socket, buf, strlen(buf), 0);


	int size = recv(_socket, buf, 1024, 0);
	buf[size] = '\0';

	cout << buf << endl;	
	closesocket(_socket);
	WSACleanup();
}

