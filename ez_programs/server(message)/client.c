#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <err.h>
#include "common_types.h"

key_t key;
int msgid;
mes_t data;
pid_t my_pid;

int main()
{
    key = ftok("/bin/ls", '1');
    if ( (msgid = msgget(key, 0)) == -1)
    {
        err(1, "msgid failed");
    }
    my_pid = getpid();

    while (1)
    {
        printf("Enter two numbers:");
        if (scanf("%d %d", &(data.a), &(data.b)) < 2)
        {
            printf("Ctrl+D received, exiting\n");
            return 0;
        }

        data.client = my_pid;
        data.mes_type = REQUEST;

        msgsnd(msgid, &data, sizeof(mes_t) - sizeof(long), 0);
        msgrcv(msgid, &data, sizeof(mes_t) - sizeof(long), RESPONSE + my_pid, 0);

        printf("Sum of them: %ld\n", data.result);
    }

    return 0;
}