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
	SOCKET acceptSocket;
	sockaddr_in endPoint;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	endPoint.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &endPoint.sin_addr);
	endPoint.sin_port = htons(1234);
	bind(_socket, (SOCKADDR*)&endPoint, sizeof(endPoint));
	listen(_socket, 1);

	cout << "Server has started." << endl;
	acceptSocket = accept(_socket, NULL, NULL);

	char buf[1024]{};
	int size = recv(acceptSocket, buf, 1024, 0);
	//buf[size] = '\0';
	cout << buf << endl;
	strcpy(buf, "Server has recived the message");
	send(acceptSocket, buf, strlen(buf), 0);
	closesocket(_socket);
	closesocket(acceptSocket);
	WSACleanup();
}

