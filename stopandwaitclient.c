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
	socklen_t servlen;
	struct sockaddr_in servaddr;
	Frame frame_send;
	Frame frame_recieve;
	int frameid=0,ack_recieved=1;
	char buffer[1024];
	
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
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(port);
	
	
	
	//recieving and sending to client
	servlen=sizeof(servaddr);
	
	while(1){
		if(ack_recieved==1){
			frame_send.frame_kind=1;
			frame_send.sq_no=frameid;
			frame_send.ack=0;
			memset(buffer,0,1024);
			printf("Enter the Frame:");
			scanf("%s",buffer);
			strcpy(frame_send.packet.data,buffer);
			
			int sendreturn=sendto(sockfd,&frame_send,sizeof(Frame),0,(struct sockaddr*)&servaddr,servlen);
			if(sendreturn<0){
				printf("Sending failed\n");
				exit(EXIT_FAILURE);
			}
		}
		
		int recvreturn=recvfrom(sockfd,&frame_recieve,sizeof(frame_recieve),0,(struct sockaddr*)&servaddr,&servlen);
		
		if(recvreturn>0 && frame_recieve.sq_no==0 && frame_recieve.ack==frameid+1){
			printf("Acknowlegement recieved\n");
			ack_recieved=1;
		}
		else{
			printf("Ack not recieved\n");
			ack_recieved=0;
		}
	
	frameid++;
	}


close(sockfd);
return 0;
}
