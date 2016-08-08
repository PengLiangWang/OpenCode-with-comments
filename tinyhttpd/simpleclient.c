#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 int sockfd;
 socklen_t len;
 struct sockaddr_in address;
 int result;
 char buf[32] = "GET /index.html HTTP/1.1\n\n\n";
 char get[2048]={0};

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("127.0.0.1");
 address.sin_port = htons(11000);
 len = sizeof(address);
 result = connect(sockfd, (struct sockaddr *)&address, len);

 if (result == -1)
 {
  perror("oops: client1");
  return 1;
 }
 write(sockfd, buf, sizeof(buf));   /*发送请求*/
 read(sockfd, get, sizeof(get));   /*接收返回请求*/
 /*打印返回数据*/
 printf("---------------------------------------------------\n");
 printf("recv from server:\n%s\n", get);
 printf("---------------------------------------------------\n");
 close(sockfd);
 return 0;
}
