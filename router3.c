#include<stdio.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
struct sockaddr_in infos,cli; 
int siz  =sizeof(struct sockaddr);
int data,i=0,j=0;
int info ; 
int f5=open("clientlog.txt",O_RDWR|O_APPEND,0755);	
info=socket(AF_INET,SOCK_STREAM,0);

if(info<0)
	{
	printf(" socket not created ");
	}
infos.sin_addr.s_addr=INADDR_ANY;
infos.sin_port = htons(5432);
infos.sin_family= AF_INET;
memset(&(infos.sin_zero) , '\0',8);

char buf[100],t[20],cport[10],alias[20];
int port;

if((bind(info , (struct sockaddr *)&infos ,siz))<0)
	{
	printf(" bind err data ");
	exit(1);
	}
int f3=open("pls.txt",O_RDWR|O_TRUNC|O_CREAT,0755);
int f4=open("clientlog.txt",O_RDWR|O_TRUNC|O_CREAT,0755);
char b[1000];
char actsend[1000];
listen(info,10);
/*int w=read(f3,actsend,1000);
if(w<0)

{
printf("error in reading active list\n");
exit(1);
}
printf(" %s",actsend);*/
char aliases[10][20] , type[20];
int ports[10];
int inc=0,con,ty;
while(1)
{
		
	int a=accept(info ,(struct sockaddr*)&cli ,&siz);
	if(a<0)
	{
	printf(" error data connection ");
	exit(1);
	}
//send(a,actsend,strlen(actsend),0);
/*
int re2=recv(a,type,20,0);
	if(re2<0 )
		{
		printf(" recv err ");
		exit(0);
		}
	
	
	type[re2]='\0';
	ty=strcmp(type,"server");
if(ty==0)
{
*/
int re1=recv(a,alias,20,0);


	if(re1<0 )
		{
		printf(" recv err ");
		exit(0);
		}
	
	
	alias[re1]='\0';
	if(strcmp(alias,"client")!=0)
{

	int re=recv(a,cport,10,0);
	if(re<0)
		{
		printf(" recv err ");
		exit(0);
		}

	cport[re]='\0';
	sscanf(cport,"%d",&port);
	
	write(f3,alias,strlen(alias));
	write(f3," connected in ",strlen(" connected in "));
	write(f3,cport,strlen(cport));
	inc++;

	printf(" want to continue [1/0]");
	scanf("%d",&con);
	if(con==0)
	break;
	
}
else
{

 
int w=write(f5,"client ",strlen("client "));
if(w<0)
	{
	printf(" error ");
	exit(1);
	}

}


}


/*
int inn=0;
for(inn=0;inn<inc;inn++)
	{
	printf(" %s connected in %d \n",aliases[inc],ports[inc]);
	}
*/
close(info);
close(f3);
close(f4);


return 0 ;
}
