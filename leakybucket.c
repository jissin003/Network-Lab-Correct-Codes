#include<stdio.h>

int findminimum(int x,int y){
	if(x>y){
		return y;
	}
	else{
		return x;
	}
}

int main(){

	int seconds,bucketsize,incoming[500],outgoing,filled,drop;
	int i;
	
	printf("Enter the Bucket size: ");
	scanf("%d",&bucketsize);
	printf("Enter the Outgoing Rate: ");
	scanf("%d",&outgoing);
	printf("Enter the Number of Seconds to Stimulate:");
	scanf("%d",&seconds);
	for(i=0;i<seconds;i++){
		printf("Enter the incoming at Sec %d : ",i+1);
		scanf("%d",&incoming[i]);
	}
	
	printf("\nSecond\tIncoming\tOutgoing\tBucketbefore\tBucketafter\tDrop\n");
	for(i=0;i<seconds;i++){
		filled+=incoming[i];
		if(filled>bucketsize){
			drop=filled-bucketsize;
			filled=bucketsize;
		}
		int minimum=findminimum(filled,outgoing);
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,incoming[i],minimum,filled,filled-minimum,drop);
		filled=filled-minimum;
		drop=0;
	}
	
	for(i=seconds;filled!=0;i++){
		if(filled>bucketsize){
			drop=filled-bucketsize;
			filled=bucketsize;
		}
		int minimum=findminimum(filled,outgoing);
		printf("%d\t0\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,minimum,filled,filled-minimum,drop);
		filled=filled-minimum;
		drop=0;
	}


return 0;
}
