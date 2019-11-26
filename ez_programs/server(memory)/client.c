 
#include<string.h>
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
	data client_struct;
	data* client_data_ptr;
	data* shm;
	char* i;
	client_data_ptr =&client_struct;
	
	key = 555;

    //create shared memory
    schmid = shmget(key, SMSIZE, 0666);

	if (schmid < 0) {
		perror ("schmget error");
		exit (-1);
	}

	//attach calling process to shared memory
	shm = (data*) shmat (schmid, NULL,0);


	printf("Enter two numbers:");
        if (scanf("%d %d", &(shm->a), &(shm->b)) < 2)
        {
            printf("Ctrl+D received, exiting\n");
            return 0;
        }

        shm->B = "1";

	if (shm == (char*) -1)
	{
		perror("shmat error");
	}

	//read data into shared-memory
	printf("Sum of them: %ld\n", shm->sum);
	
	printf("\n");
	
	//clear memory by writing # at first location
	shm->B = "0";

        return 0;
}