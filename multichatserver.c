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
#define addrsize 100
//multichat using tcp

void main(){

	int sockfd,newsockfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clisize;
	char buffer[buffersize];
	char ipaddress[addrsize];
	pid_t childpid;
	
	//socket creation
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Socket creation successfull\n");
	
	//setting address structure using memset
	
	memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));
	
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=port;//ivide ingane itille kittilla
	
	//binding
	
	if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("Binding Failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Binding sucessfull\n");
	
	if(listen(sockfd,5)<0){
		printf("Listen Failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Listen successfull\n");
	printf("Waiting for connection\n");
	
	
	clisize=sizeof(cliaddr);
	
	for(;;){
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clisize))<0){
			printf("Connection failed\n");
			exit(EXIT_FAILURE);
		}
		printf("Connection established\n");
		
		inet_ntop(AF_INET,&(cliaddr.sin_addr),ipaddress,addrsize);//for fetching ip address of client
		
		if((childpid=fork())==0){
			close(sockfd);
			
			for(;;){
				memset(buffer,0,buffersize);
				if(recv(newsockfd,buffer,buffersize,0)<0){
					printf("Error in recieving Message\n");
					exit(EXIT_FAILURE);
				}
				printf("Message recieved from %s:%s",ipaddress,buffer);
				
				if(send(newsockfd,buffer,buffersize,0)<0){
					printf("Error in sending Message\n");
					exit(EXIT_FAILURE);
				}
				printf("Message send to %s:%s",ipaddress,buffer);
			}
		}
		
		close(newsockfd);
	}


}
