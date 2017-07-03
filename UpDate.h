#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#include <fstream>  
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 1024
class CUpDate
{
public:
	CUpDate();
	~CUpDate();
	bool CheckNewVersion();
	void GetNewVersion();
	
public:
	WSADATA wsaData;
	sockaddr_in sockAddr;
	char *filename;
};

