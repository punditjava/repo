#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "common_types.h"

key_t key;
int msgid;
mes_t data;

void handler(int sig)
{
    if (sig == SIGINT)
    {
        msgctl(msgid, IPC_RMID, NULL);
        exit(0);
    }
    signal(SIGINT, handler);
}

int main()
{
    key = ftok("/bin/ls", '1');
    msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);

    if (msgid == -1)
    {
        printf("msgget failed\n");
        return 1;
    }

    signal(SIGINT, handler);

    while (1)
    {
        msgrcv(msgid, &data, sizeof(mes_t) - sizeof(long), REQUEST, 0);
        data.result = data.a + data.b;
        printf("in process %d + %d = %ld, client = %d\n",
               data.a, data.b, data.result, (int)data.client);
        fflush(stdout);
        data.mes_type = RESPONSE + (long)data.client;
        msgsnd(msgid, &data, sizeof(mes_t) - sizeof(long), 0);
    }
    return 0;
}