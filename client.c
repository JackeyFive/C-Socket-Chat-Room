#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>  
#include<errno.h>  
#include<netinet/in.h>
#include<pthread.h>

#define MAX 1024

void* put2client();


int fd; 
int pid; 
char bufin[MAX];
char bufout[MAX];

void main(){

struct sockaddr_in   ad_in;
//struct sockaddr *ad;
//ad=&ad_in;

char *addr="127.0.0.1";
char *server="server:";


memset((void *)&ad_in,0,sizeof(ad_in));

ad_in.sin_family = AF_INET;  
ad_in.sin_port=htons(8000);
 

if(inet_pton(AF_INET,addr,(void *)&(ad_in.sin_addr))!=1){
printf("htn");
}

if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
printf("socket");exit(0);
}

if(connect(fd,(struct sockaddr*)&ad_in,sizeof(ad_in))<0){
printf("connect");exit(0);
}

if(pthread_create(&pid,NULL,put2client,NULL)!=0){
printf("pthread");exit(0);
}

while(1){
	ssize_t len=0;
	len=read(fd,bufin,MAX);

	if(len==0)
	exit(0);

	write(1,server,sizeof(server));
	write(1,bufin,len);

}
//pthread_join(pid,NULL);

close(fd);
exit(0);
}




void* put2client(){

while(1){
	
	ssize_t len=0;
	len=read(0,bufout,MAX);
	write(fd,bufout,len);	

	}

}
