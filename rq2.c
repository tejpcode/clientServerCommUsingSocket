#include"header.h"
#include"declaration.h"
#include"datastructure.h"
int main()
{
	int FD,ret;
	socklen_t length;
	struct sockaddr_in addr;
	struct sockaddr_in raddr;

	struct Clientreq req;
	struct Result res;
	addr.sin_family=PF_INET;
	addr.sin_port=htons(3300);
	inet_aton("127.0.0.1",&addr.sin_addr);
//	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	FD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	length=sizeof(struct sockaddr_in);
	req.PID=getpid();
	req.data1=3;
	req.data2=1;
	req.operators='*';
//	ret=connect(FD,(struct sockaddr*)&addr,length);
	ret=sendto(FD,(void*)&req,sizeof(req),0,(struct sockaddr*)&addr,sizeof(raddr));
	if(ret==-1)
	{
		perror("sendto");
		exit(EXIT_FAILURE);
	}
	ret=recvfrom(FD,(void*)&res,sizeof(res),0,(struct sockaddr*)&raddr,&length);
	if(ret==-1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	printf("%s\t:Client result:%d\tPID:%d\n",__FILE__,res.result,req.PID);
}
