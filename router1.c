#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<netdb.h>

int MTU1= 60;
struct packet{
	int ver;
	int length;
     	int frag;
	int offset;
	int more;
	char data[200];
     };
struct sockaddr_in my,sth,recvp;
struct hostent *he;

int main()
{
int n;
int data_max=MTU1-20;
int m=1;
struct packet p1[10],p2;
int size2,se,sp,re , s ,size, z;
char buf[100],buff[100],temp[1000];



if((sp=socket(AF_INET ,SOCK_STREAM,0))<0)
	{
	printf(" error creating socket \n");
	exit(0);
	}

recvp.sin_family=AF_INET;
recvp.sin_port=htons(2222);
recvp.sin_addr.s_addr =INADDR_ANY;
memset(&(recvp.sin_zero),'\0',8);

if(bind(sp,(struct sockaddr *)&recvp, sizeof(struct sockaddr))==-1)
	{
	printf(" binding error");
	exit(0);
	}
if(listen(sp,10)<0)
	{
	printf(" errorn in backlogging ");
	exit(0);
	}
	
	int ack2;
	size2=sizeof(struct sockaddr);
	if((ack2=accept(sp,(struct sockaddr *)&sth,&size))<0)
	printf("accept error");
	else
	printf(" client accepted\n");


int port,siz;
char buf2[5];
	int ree=recv(ack2,buf2,5,0);
	if(ree<0) 
	{
	printf(" recv port err ");
	exit(1);
	}
	buf2[ree]='\0';
	sscanf(buf2,"%d",&port);
	puts(buf2);
	printf("\t port number recvd %d \n",port);
	close(sp);

int fd,i,j,k,off=0,l,a;


if((s=socket(AF_INET ,SOCK_STREAM,0))<0)
	{
	printf(" error creating socket \n");
	exit(0);
	}
/*
my.sin_family=AF_INET;
my.sin_port=htons(5124);
my.sin_addr.s_addr =INADDR_ANY;
memset(&(my.sin_zero),'\0',8);

if(bind(s,(struct sockaddr *)&my, sizeof(struct sockaddr))==-1)
	{
	printf(" binding error");
	exit(0);
	}
if(listen(s,10)<0)
	{
	printf(" errorn in backlogging ");
	exit(0);
	}
	
	int ack;
	size=sizeof(struct sockaddr);
	if((ack=accept(s,(struct sockaddr *)&sth,&size))<0)
	printf("accept error");
	else
	printf(" client accepted\n");
*/
int s2;
if((s2=socket(AF_INET ,SOCK_STREAM,0))<0)
	{
	printf(" error creating socket \n");
	exit(0);
	}

	
struct sockaddr_in fser;
fser.sin_family=AF_INET;
fser.sin_port=htons(port+10);
fser.sin_addr.s_addr=INADDR_ANY; 
memset(&(fser.sin_zero),'\0',8);

	if((connect(s2,(struct sockaddr *)&fser,sizeof(struct sockaddr)))==-1)
	{
	printf(" error in connection \n");
	exit(0);
	}
	printf("sucess connected\n");
	char data[1000];

	k=recv(s2,data,1000,0);
	printf("total size:%d\n",k);
	strcpy(temp,data);
	printf("max data size of a packet :%d\n",data_max);
	n=(k/data_max)+1;	
		
	printf(" recvd fragments are   \n");
	
		
	

	do
	{	p1[m].ver=4;
		p1[m].offset=off;
		p1[m].frag=m;
			if(m<n)
			{
			p1[m].more=1;
			p1[m].length=data_max;
			/*for(j=off,l=0;j<(off+data_max);j++,l++)
			p1[m].data[l]=temp[j];
			p1[m].data[data_max]='\0';*/
			strncpy(p1[m].data,temp+off,data_max);
	
			/*if((se=send(ack,(char *)&p1[m],siz,0))==-1)
			{
			printf(" error in sending \n");
			exit(0);
			}*/
	
			}
			else
			if(m==n)
			{
			p1[m].more=0;
			a=k-off;
			p1[m].length=a;
			strncpy(p1[m].data,temp+off,a);
			
			}
		printf("packet:%d\n",m);
		printf("offset:%d\n",p1[m].offset);
		printf("length of the packet:%d\n",p1[m].length);
		printf("%s",p1[m].data);
		printf("\n");
		off=off+data_max;
	m++;		
	}while(m<=n);
	// send the packets
	close(s2);
	int la=0;
	char final[1000];
	final[0]='\0';
		for(la=1;la<=n;la++)
	{
	strcat(final,p1[la].data);
	}
	strcpy(p2.data,final);
	


	close(fd);
	//close(s);
	
	return 0;
}
