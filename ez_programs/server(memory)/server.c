 
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define SMSIZE 100

typedef struct mystruct{
	int a;
	int b;
	int sum;
	char* B;
}data;

int main(){

        int schmid;
        key_t key;
        char* addr;
	data* stct_ptr;
	data* shm;
	char* m;

	key = 555;

        
    schmid = shmget(key,SMSIZE,IPC_CREAT | 0666);

	if (schmid < 0){
		perror ("schmget error");
		exit (-1);
	}

	shm = (data*) shmat (schmid, NULL,0);
	
	if(shm == (data*) -1){
		perror("shmat error");
		exit(1);
	}
	
	
	
		shm->sum = shm->a + shm->b;
        printf("in process %d + %d = %ld",
               shm->a, shm->b, shm->sum );
        

	

        return 0;
}