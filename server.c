#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>  
#include<errno.h>  
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<pthread.h>

#define MAX 1024


void* put2client();

int fd_n,newfd;
int pid;
char bufin[MAX];
char bufout[MAX];

void main(){

struct sockaddr_in ad_in;
struct sockaddr_in conad_in;

char *addr="127.0.0.1";
char *client="client:";


memset(&ad_in,0,sizeof(ad_in));
memset(&conad_in,0,sizeof(conad_in));

if(inet_pton(AF_INET,(char *)addr,(void *)&(ad_in.sin_addr))<1){
printf("htn");exit(0);
}	
		
if((fd_n=socket(AF_INET,SOCK_STREAM,0))<0){
	printf("socket");exit(0);}

ad_in.sin_family = AF_INET;
//ad_in.sin_addr.s_addr = htonl(INADDR_ANY);
ad_in.sin_port=htons(8000);
conad_in.sin_family = AF_INET;



if( bind(fd_n, (struct sockaddr*)&ad_in, sizeof(ad_in)) <0){
printf("bind");exit(0);
}

if( listen(fd_n, 10) == -1){
printf("listen");exit(0);
}


ssize_t len=sizeof(conad_in);

//	biggest leession:if(newfd=accept(fd_n, (struct sockaddr*)NULL, NULL)<0)
if((newfd = accept(fd_n, (struct sockaddr*)&conad_in, (socklen_t*)&len))<0){
			printf("accept");exit(0);}


if(pthread_create(&pid,NULL,put2client,NULL)!=0){
printf("pthread");exit(0);
}

while(1){
	ssize_t len=0;
	len=read(newfd,bufin,MAX);
	
	if(len==0)
	exit(0);
	

	write(1,client,sizeof(client));
	write(1,bufin,len);
	
}

//printf("%d",newfd);
//pthread_join(pid,NULL);

close(newfd);
close(fd_n);
exit(0);
}


void* put2client(){



while(1){
	
	ssize_t len=0;
	len=read(0,bufout,MAX);

	write(newfd,bufout,len);	
	
	}

}

