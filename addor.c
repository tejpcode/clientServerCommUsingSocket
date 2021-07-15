#include"header.h"
#include"declaration.h"
#include"datastructure.h"
int main(int argc , char* argv[])
{
	//printf("%s:BEGIN\n",__FILE__);
	int key;
	int pid;
	int mkey1,ret;
	struct Result res;
	//printf("PID: %d\n",getpid());
	pid=atoi(argv[1]);
	int data1=atoi(argv[2]);
	int data2=atoi(argv[3]);
        
	key=semget((key_t)123,1,0666|IPC_CREAT);
	if(key==-1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	unin.val=1;
	ret=semctl(key,0,SETVAL,unin);
	//mkey=msgget((key_t)125,0666|IPC_CREAT);
	mkey1=msgget((key_t)126,0666|IPC_CREAT);
	//ret=msgrcv((key_t)mkey,(void*)&req,(size_t)sizeof(req),atoi(argv[1]),(int)0);
	if(ret==-1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	res.result=data1+data2;
	res.PID=pid;
	str.sem_num=0;
	str.sem_op=-1;
	str.sem_flg=SEM_UNDO;
	semop(key,&str,1);
	ret=msgsnd(mkey1,(void*)&res,(size_t)sizeof(res),0);
	if(ret==-1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	str.sem_num=0;
	str.sem_op=1;
	str.sem_flg=SEM_UNDO;
	semop(key,&str,1);
	//printf(">>>>>>>>>>>>>>>>Vendor result %d	PID:%ld\n",res.result,res.PID);
	//printf("%s:END\n",__FILE__);
        return 0;
}
