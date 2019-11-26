#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t w;    // write access
sem_t m;    // mutex
int rc=0;   // readers count

int writersCount;
int readersCount;
pthread_t writersThread[100], readersThread[100];
int writeCount[10], readCount[10];

void *writer(void *i)
{
    int a = *((int *) i);

    sem_wait(&w);   // P(w)
    printf("Writer %d writes to DB.\n",a+1);
    writeCount[a + 1]++;
    sem_post(&w);   // V(w)

    return NULL;
}

void *reader(void *i)
{
    int a = *((int *) i);

    sem_wait(&m);   // P(m)
    rc++;
    if (rc == 1) {
        sem_wait(&w);   // P(w)
    }
    sem_post(&m);   // V (m)

    printf("Reader %d reads from DB.\n", a + 1);
    readCount[a + 1]++;

    sem_wait(&m);   // P(m)
    rc--;
    if (rc == 0) {
        sem_post(&w);   // V(w)
    }
    sem_post(&m);   // V(m)

    return NULL;
}

int randomCount()
{
    return 5.0 * rand() / RAND_MAX;
}

int main()
{
    sem_init(&w,0,1);
    sem_init(&m,0,1);

    int i;

    printf("Enter count of writers:");
    scanf("%d",&writersCount);
    printf("Enter count of readers:");
    scanf("%d",&readersCount);

    int readerIndices[readersCount];
    int writerIndices[writersCount];
    int totalReaders = 0;
    int totalWriters = 0;

    for (i=0; i<readersCount; i++)
    {
        int j;
        int count;

        readerIndices[i] = i;
        count            = randomCount();
        for (j = 0 ; j < count ; ++j)
        {
            pthread_create(&readersThread[totalReaders++], NULL, reader, &readerIndices[i]);
        }
    }

    for (i = 0 ; i < writersCount ; i++)
    {
        int j;
        int count;

        writerIndices[i] = i;
        count            = randomCount();
        for (j = 0 ; j < count ; ++j)
        {
            pthread_create(&writersThread[totalWriters++], NULL, writer, &writerIndices[i]);
        }
    }

    for (i = 0 ; i < totalWriters ; i++)
    {
        pthread_join(writersThread[i], NULL);
    }

    for (i = 0 ; i < totalReaders ; i++)
    {
        pthread_join(readersThread[i], NULL);
    }

    printf("--------------\n");
    for (i = 0 ; i < readersCount ; i++)
    {
        printf("Reader %d read %d times\n", i + 1, readCount[i + 1]);
    }

    for (i = 0 ; i < writersCount ; i++)
    {
        printf("Writer %d wrote %d times\n", i + 1, readCount[i + 1]);
    }

    sem_destroy(&w);
    sem_destroy(&m);
    return 0;
}