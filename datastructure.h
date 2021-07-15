typedef struct Clientreq
{
	long PID;
	char operators;
	int data1;
	int data2;
}Clientreq;
typedef struct Result
{
	long PID;
	int result;
}Result;
typedef struct Mque
{
	int FD;
	//int mkey1;
	int mkey2;
	sem_t sem;
}Mque;
union semun {
        int val;                        /* value for SETVAL */
        struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
        unsigned short *array;  /* array for GETALL & SETALL */
        struct seminfo *__buf;  /* buffer for IPC_INFO */
        void *__pad;
};
union semun unin;
struct sembuf str;
extern int flag;
