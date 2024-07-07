#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct packet{
	char data[1024];
}Packet;

typedef struct frame{
	int frame_kind,sq_no,ack;
	Packet packet;
}Frame;

int main(int argc,char ** argv){
	int sockfd;
	socklen_t clilen;
	struct sockaddr_in servaddr,cliaddr;
	Frame frame_send;
	Frame frame_recieve;
	int frameid=0;
	
	if(argc!=2){
		printf("Format:%s <Port Number>",argv[0]);
		exit(EXIT_FAILURE);
	}
	int port=(short)atoi(argv[1]);
	
	//socket creation
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
		printf("Socket Creation failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Socket created\n");
	
	//serveraddress structure defining
	
	memset(&servaddr,'\0',sizeof(servaddr));
	memset(&cliaddr,'\0',sizeof(cliaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(port);
	
	//binding
	if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("Bind failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Bind successfull\n");
	
	//recieving and sending to client
	clilen=sizeof(cliaddr);
	
	while(1){
	
		int frame_recieve_size=recvfrom(sockfd,&frame_recieve,sizeof(Frame),0,(struct sockaddr*)&cliaddr,&clilen);
		if(frame_recieve_size>0 && frame_recieve.frame_kind==1 && frame_recieve.sq_no==frameid){
				printf("[+]Frame recieved:%s\n",frame_recieve.packet.data);
				
				//preparations to send acknowledgment
				
				frame_send.frame_kind=0;
				frame_send.sq_no=0;
				frame_send.ack=frame_recieve.sq_no+1;
				
				if(sendto(sockfd,&frame_send,sizeof(frame_send),0,(struct sockaddr*)&cliaddr,clilen)<0){
					printf("[-]Acknowledgement Not Sent\n");
					exit(EXIT_FAILURE);
				}
				printf("[+]Acknowledgement Sent\n");
		}
		else{
			printf("Frame Not recieved\n");
			exit(EXIT_FAILURE);
		}
	
	frameid++;
	}


close(sockfd);
return 0;
}
