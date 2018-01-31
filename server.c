/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8000
int main(void)
{
struct sockaddr_in servaddr, cliaddr;
socklen_t cliaddr_len;
int listenfd, connfd;
char buf[MAXLINE];
char str[INET_ADDRSTRLEN];
int i, n;
listenfd = socket(AF_INET, SOCK_STREAM, 0); //IPV4 tcp 0
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);

bind(listenfd, (struct sockaddr *)&servaddr,sizeof(servaddr));

listen(listenfd, 20);
printf("Accepting connections ...\n");
 while (1) 
 {
  cliaddr_len = sizeof(cliaddr);
  connfd = accept(listenfd,(struct sockaddr *)&
        cliaddr,&cliaddr_len);
  n = read(connfd, buf, MAXLINE);
  
  printf("received from %s at PORT %d\n",
      inet_ntop(AF_INET, &cliaddr.sin_addr, str,sizeof(str)),
	  ntohs(cliaddr.sin_port));

  /*const char *inet_ntop(int family, const void *addrptr, 
  char *strptr, size_t len); 
  inet_ntop进行相反的转换，从数值格式（addrptr）转换到表达格式（strptr）。
  len参数是目标存储单元的大小，以免该函数溢出其调用者的缓冲区。为有助于指定
  这个大小，在<netinet/in.h>头文件中有如下定义：*/
 
  for (i = 0; i < n; i++)
  buf[i] = toupper(buf[i]);
  write(connfd, buf, n);
  close(connfd);
 }
}