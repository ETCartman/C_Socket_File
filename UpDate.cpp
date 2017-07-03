#include <UpDate.h>

CUpDate::CUpDate()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("123.206.180.119");
    sockAddr.sin_port = htons(1234);
}
bool CUpDate::CheckNewVersion()
{
	char str[20];
	td::ifstream fin("version.ak47");
	while (fin)
	{
			 		fin >> str;
	}

	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = {0};
    recv(sock, szBuffer, MAXBYTE, NULL);
    //输出接收到的数据
    //printf("Message form server: %s\n", szBuffer);
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
   if(str == szBuffer)
   {
   	return TRUE;
   }
   return FALSE;
}

void CUpDate::GetNewVersion()
{
	FileName = "PlaneGame.exe";
	FILE *fp = fopen(filename, "wb");
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//循环接收数据，直到文件传输完毕
    char buffer[BUF_SIZE] = {0};  //文件缓冲区
    int nCount;
    while( (nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0 ){
        fwrite(buffer, nCount, 1, fp);
    }
   // puts("File transfer success!");
    //文件接收完毕后直接关闭套接字，无需调用shutdown()
    fclose(fp);
    closesocket(sock);
    WSACleanup();
}
CUpDate::~CUpDate()
{}