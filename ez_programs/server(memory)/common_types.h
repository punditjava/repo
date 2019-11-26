#include <signal.h>

#define REQUEST 1
#define RESPONSE 2

typedef struct
{
    long mes_type;
    int a, b;
    long result;
    pid_t client;
} mes_t; 
