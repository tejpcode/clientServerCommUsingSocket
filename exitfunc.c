#include"header.h"
#include"declaration.h"
void* exitfunc(void* a)
{
	printf("%s: START\n",__FILE__);
	printf("%s: END\n",__FILE__);
	return 0;
}
