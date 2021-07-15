#include"header.h"
#include"declaration.h"
#include"datastructure.h"
int flag;
void* threadfunc(void* rvalue)
{
	//printf("%s: START\n",__FILE__);
	Mque* mkeys;
	int ret,fret;
	sem_t sem;
	socklen_t len;
	char pid[6];
	char data1[10] = {'\0'};
	char data2[10] = {'\0'};
	mkeys=(Mque*)rvalue;
	struct Clientreq cdata;
	struct Clientreq cldata;
	struct Result rdata;
	struct sockaddr_in addr;
	memset(&addr,'\0',sizeof(struct sockaddr_in));
	addr.sin_family=PF_INET;
	addr.sin_port=htons(3300);
	addr.sin_addr.s_addr=INADDR_ANY;
	len=sizeof(addr);
	sem=mkeys->sem;
        printf("Waiting....... \n");
	recvfrom(mkeys->FD,(void*)&cdata,sizeof(cdata),0,(struct sockaddr*)&addr,&len);
	if(ret==-1)
	{
	    perror("connect");
	    exit(EXIT_FAILURE);
	}
	printf("IPaddress:%s\tData1:%d\tData2:%d\tOperator:%c\n",inet_ntoa(addr.sin_addr), cdata.data1, cdata.data2, cdata.operators);
	//printf("DATA1 RECEICED FROM CLIENT :%d\n",cdata.data1);
	//printf("DATA2 RECEIVED FROM CLIENT :%d\n",cdata.data2);
	//printf("Operator received from client:%c\n",cdata.operators);
	//printf("Client PID:%d\n",cdata.PID);
	ret=sprintf(pid,"%ld",cdata.PID);
	ret=sprintf(data1,"%d",cdata.data1);
	ret=sprintf(data2,"%d",cdata.data2);
	if(ret==-1)
	{
	    perror("sprintf");
	    exit(EXIT_FAILURE);
	}
	signal(SIGCHLD,SIG_IGN);
	flag=1;
	fret=fork();
	switch(fret)
	{
	    case -1:
	        perror("fork");
		exit(EXIT_FAILURE);
	    case 0:
		ret=sem_wait(&sem);
		if(ret==-1)
		{
		    perror("sem_wait");
		    exit(EXIT_FAILURE);
		}
		//ret=msgsnd((key_t)mkeys->mkey1,(void*)&cdata,(size_t)(sizeof(cdata)),(int)0);
		//printf("data send with client pid %d operator: %c\n", cdata.PID, cdata.operators);
		if(ret==-1)
		{
		    perror("msgsnd");
		    exit(EXIT_FAILURE);
		}
		ret=sem_post(&sem);
		if(ret==-1)
		{
		    perror("sem_post");
		    exit(EXIT_FAILURE);
		}
		switch(cdata.operators)
		{
		    case '+':
			execl("./addor","addor",pid, data1, data2, NULL);
			break;
		    case '-':
			execl("./substractor","substractor",pid, data1, data2, NULL);
			break;
    		    case '*':
                	execl("./mul","mul",pid, data1, data2, NULL); 
		        break;
		    case '/':
			execl("./div","div",pid, data1, data2, NULL);
			break;
		    default:
			printf("we dont deal with this operator\n");
			break;
		}
	    default:
		ret=msgrcv((key_t)mkeys->mkey2,(void*)&rdata,(size_t)sizeof(struct Result),cdata.PID,0);
		if(ret==-1)
		{
		    perror("msgrcv");
		    exit(EXIT_FAILURE);
		}
		//printf(">>>>>>>>>>>>>>>>>>>>>>>>>RESULT Received: %d   %d\n",rdata.result,rdata.PID);
		ret=sendto(mkeys->FD,(void*)&rdata,sizeof(rdata),0,(struct sockaddr*)&addr,len);
                //printf("After send\n");
		if(ret==-1)
		{
		    perror("sendto");
		    exit(EXIT_FAILURE);
		}
				
		
	}
	//printf("%s: END\n",__FILE__);

}
