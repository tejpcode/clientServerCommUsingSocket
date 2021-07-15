#include"header.h"
#include"declaration.h"
#include"datastructure.h"
void* infra(void* data)
{
	//printf("%s: START\n",__FILE__);
	int FD;
	int ret;
	socklen_t length;
	sem_t sem;
	//key_t mkey1;
	key_t mkey2;
	Mque* keys;
	keys=(Mque*)data;
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	length=sizeof(addr);
	addr.sin_family=PF_INET;
	addr.sin_port=htons(3300);
	addr.sin_addr.s_addr=INADDR_ANY;
	FD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(FD==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	ret=bind(FD,(struct sockaddr*)&addr,length);
	keys->FD=FD;
	if(ret==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	/*mkey1=msgget((key_t)125,IPC_CREAT|0666);
	printf("MKEY1%d\n",mkey1);
	if(ret==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}*/
	mkey2=msgget((key_t)126,IPC_CREAT|0666);
	if(ret==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	//keys->mkey1=mkey1;
	keys->mkey2=mkey2;
	ret=sem_init(&sem,0,1);
	if(ret==-1)
	{
		perror("sem_init");
		exit(EXIT_FAILURE);
	}
	keys->sem=sem;
	//printf("%s: END\n ",__FILE__);
	return (void*)keys;
}
