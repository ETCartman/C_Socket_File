#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <fstream>

#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
//using  namespace std;
int main(){
    //��ʼ�� DLL
   // while(1)
//    {

while(true)
{


    FILE *fp;
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    //�����׽���
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //���׽���
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("0.0.0.0");  //�����IP��ַ
    sockAddr.sin_port = htons(1234);  //�˿�
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //�������״̬

    listen(servSock, 20);
    //���տͻ�������
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    //��ͻ��˷�������

    char str[20];
    fp = fopen("game.version", "r");
    fscanf(fp, "%s", str);
    printf("%s\n",str);
    fclose(fp);
    send(clntSock, str, strlen(str)+sizeof(char), NULL);
    //�ر��׽���
    closesocket(clntSock);
    closesocket(servSock);
    //��ֹ DLL ��ʹ��
}

    WSACleanup();

   // }

    return 0;
}
