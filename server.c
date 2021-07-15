#include"header.h"
#include"declaration.h"
#include"datastructure.h"
int flag;
int main()
{
	int ret;
	init();
	Mque *data;
	data=(Mque*)malloc(sizeof(Mque));
	data=(void*)fptr[1]((void*)data);
	pthread_t id;
	flag=0;
	while(1)
	{
		ret=pthread_create(&id,0,&threadfunc,data);
		if(ret==-1)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		while(flag==0);
		flag=0;
	}
}
