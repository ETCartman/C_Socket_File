#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 1024
#define VERSION 1
int main() {
    double num = 1;
    while(true)
    {
        printf("%d\n",num);
       char *filename = "PlaneGame.exe";  //
	FILE *fp = fopen(filename, "rb");  //以二进制方式打开文件
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	  WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	sockAddr.sin_port = htons(5656);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

        //先检查文件是否存在


    listen(servSock, 20);
        SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//循环发送数据，直到文件结尾
	char buffer[BUF_SIZE] = { 0 };  //缓冲区
	int nCount;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		send(clntSock, buffer, nCount, 0);
	}
	shutdown(clntSock, SD_SEND);  //文件读取完毕，断开输出流，向客户端发送FIN包
	recv(clntSock, buffer, BUF_SIZE, 0);  //阻塞，等待客户端接收完毕
	closesocket(clntSock);
    closesocket(servSock);
    fclose(fp);
    printf("You have get one \n");
    num++;
    }






	WSACleanup();

    exit(0);
	return 0;
}
