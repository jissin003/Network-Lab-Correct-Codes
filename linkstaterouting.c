//linkstate routing using dijiskras algorithm
#include<stdio.h>

void findingminimum(int n,int cost[n][n],int src){
int distance[n],last[n],visited[n];
int count,i;
for(i=0;i<n;i++){
	distance[i]=1000;
	visited[i]=0;
	last[i]=src;
}
distance[src]=0;

for(count=0;count<n;count++){
	int min=1000,u=-1;
	//finding the source and it distance source  initially zero so atum indexum kitum
	for(i=0;i<n;i++){
		if(visited[i]==0 && distance[i]<min){
			min=distance[i];
			u=i;
		}
	}
	if(u==-1){
		break;
	}
	visited[u]=1;
	//updating the shortest path
	for(i=0;i<n;i++){
		if(visited[i]==0 && distance[u]+cost[u][i]<distance[i]){
			distance[i]=distance[u]+cost[u][i];
			last[i]=u;
		}
	}
}
printf("Routing table of %d\n",src+1);
printf("DESTINATION\tCOST\tNEXTHOP\n");
for(i=0;i<n;i++){
	if(i==src){
		printf("%d\t\t-\t-\n",src+1);
	}
	else if(last[i]==src){
		printf("%d\t\t%d\t-\n",i+1,distance[i]);
	}
	else{
		printf("%d\t\t%d\t%d\n",i+1,distance[i],last[i]+1);
	}
}
printf("\n");
for(i=0;i<n;i++){
	if(i!=src){
		printf("Shortest distance from %d-->%d : %d\n",src+1,i+1,distance[i]);
	}
}

}


int main(){

int n;
int i,j;
printf("Enter the number of nodes: ");
scanf("%d",&n);
int cost[n][n];
printf("Enter the distance or cost between the Nodes\n");
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		if(i==j){
			cost[i][j]=0;//self loop condition
		}
		else{
			printf("Enter the cost from %d-->%d: ",i+1,j+1);
			scanf("%d",&cost[i][j]);
			//checking if it zero  if it is then make it infinity by 1000
			if(cost[i][j]==0){
				cost[i][j]=1000;
			}
		}
	}
}

int src;
printf("Enter the source node: ");
scanf("%d",&src);
findingminimum(n,cost,src-1);


return 0;
}


