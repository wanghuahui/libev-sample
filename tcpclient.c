#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define BUF_SIZE    1500

int main()
{
	int conn_fd;
	struct sockaddr_in serv_addr;
	char buf[BUF_SIZE];

	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(9999);
	inet_aton("192.168.25.117", &serv_addr.sin_addr);

	//创建一个tcp套接字
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (conn_fd < 0)
	{
		cout<<"socket error"<<endl;
		exit(1);
	}

	if (connect(conn_fd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr_in)) <0 )
	{
		cout<<"connect error"<<endl;
		close(conn_fd);
		exit(1);
	}

	while (1) 
	{
		cout<<"Input: ";
		fgets(buf, BUF_SIZE, stdin);
		int len = strlen(buf) - 1;
		buf[len] = '\0';
		if (send(conn_fd, buf, strlen(buf), 0) < 0)
		{
			cout<<"send error"<<endl;
			break;
		}
		if (strcmp(buf, "exit") == 0)
		{
			cout<<"client exit"<<endl;
			break;
		}
		memset(buf, 0, sizeof(buf));
		recv(conn_fd, buf, sizeof(buf), 0);
		printf("recv %s\n", buf);
	}
	
	close(conn_fd);
	return 0;
}
