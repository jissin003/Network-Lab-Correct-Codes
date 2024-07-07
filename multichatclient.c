#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define port 4444
#define buffersize 2000
//multichat using tcp

int main(int argc,char ** argv){

	int sockfd,newsockfd;
	struct sockaddr_in servaddr;
	socklen_t servsize;
	char buffer[buffersize];
	char * ipaddress;
	pid_t childpid;
	
	if(argc<2){
		printf("Format:%s <Ip address>",argv[0]);
		exit(EXIT_FAILURE);
	}
	ipaddress=argv[1];
	
	//socket creation
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Socket creation successfull\n");
	
	//setting address structure using memset
	
	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_addr.s_addr=inet_addr(ipaddress);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=port;//ivide ingane itille kittilla
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("Connection Failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Connection Established\n");
	
	memset(buffer,0,buffersize);
	printf("Enter the message:");
	while(fgets(buffer,buffersize,stdin)!=NULL){
		
		if(send(sockfd,buffer,buffersize,0)<0){
			printf("Sending Failed");
			exit(EXIT_FAILURE);
		}
		memset(buffer,0,buffersize);
		if(recv(sockfd,buffer,buffersize,0)<0){
			printf("Sending Failed");
			exit(EXIT_FAILURE);
		}
		printf("Recieved:");
		fputs(buffer,stdout);
		printf("\n");
		printf("Enter the message:");
		
		
	}
	
	
	

close(sockfd);
return 0;
}
